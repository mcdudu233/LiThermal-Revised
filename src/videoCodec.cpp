#include "videoCodec.h"
#include <stdio.h>
AVFormatContext *input_ctx = NULL;
AVFormatContext *output_ctx = NULL;
AVCodecContext *encoder_ctx = NULL;
AVCodecContext *decoder_ctx = NULL;
AVStream *in_stream = NULL;
AVStream *out_stream = NULL;
struct SwsContext *sws_ctx = NULL;
struct SwsContext *sws_ctx_yuv = NULL;
AVPacket *encoded_packet = NULL;
AVPacket *packet = NULL;
AVFrame *frame = NULL;
int video_stream_index = -1;
bool packet_dumping = false;

bool isFirstPTS = true;
int64_t firstPTS = 0;

#include "pthread.h"
pthread_mutex_t recorder_mutex;
#define LOCKRECORDER() pthread_mutex_lock(&recorder_mutex)
#define UNLOCKRECORDER() pthread_mutex_unlock(&recorder_mutex)

// 打开RSTP流（URL -> MJPEG）
int openInputStream(const char *input_url) {
  if (avformat_open_input(&input_ctx, input_url, NULL, NULL) < 0) {
    fprintf(stderr, "Could not open input stream.\n");
    return -1;
  }

  // Retrieve stream information
  if (avformat_find_stream_info(input_ctx, NULL) < 0) {
    fprintf(stderr, "Could not find stream information.\n");
    return -1;
  }

  // Find the video stream
  for (int i = 0; i < input_ctx->nb_streams; i++) {
    if (input_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream_index = i;
      break;
    }
  }

  if (video_stream_index == -1) {
    fprintf(stderr, "Could not find a video stream.\n");
    return -1;
  }

  in_stream = input_ctx->streams[video_stream_index];

  return 0;
}

// 初始化输入流MJPEG的解码器（MJPEG -> BGRA）
int openInputDecoder() {
  AVCodec *decoder = avcodec_find_decoder(in_stream->codecpar->codec_id);
  if (!decoder) {
    fprintf(stderr, "Failed to find MJPEG codec.\n");
    return -1;
  }

  decoder_ctx = avcodec_alloc_context3(decoder);
  avcodec_parameters_to_context(decoder_ctx, in_stream->codecpar);

  decoder_ctx->time_base = {1, 90000};
  decoder_ctx->framerate = {90000, 1};

  if (avcodec_open2(decoder_ctx, decoder, NULL) < 0) {
    fprintf(stderr, "Failed to open decoder.\n");
    return -1;
  }
  return 0;
}

// 初始化输出流MPEG4编码器（MJPEG -> MPEG4）
int openOutputEncoder() {
  AVCodec *encoder = avcodec_find_encoder_by_name("mpeg4");
  if (!encoder) {
    fprintf(stderr, "MPEG4 encoder not found.\n");
    return -1;
  }

  encoder_ctx = avcodec_alloc_context3(encoder);
  if (!encoder_ctx) {
    fprintf(stderr, "Could not allocate encoder context.\n");
    return -1;
  }

  // 设置编码器参数
  encoder_ctx->codec_id = AV_CODEC_ID_MPEG4;
  encoder_ctx->codec_type = AVMEDIA_TYPE_VIDEO;
  encoder_ctx->width = decoder_ctx->width;
  encoder_ctx->height = decoder_ctx->height;
  encoder_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
  // 设置帧率
  encoder_ctx->time_base = {1, 25};
  encoder_ctx->framerate = {25, 1};
  // 设置码率
  encoder_ctx->bit_rate = 4 * 1000 * 1000; // 4mbps
  encoder_ctx->rc_max_rate = 4 * 1000 * 1000;
  encoder_ctx->rc_buffer_size = 8 * 1000 * 1000;
  encoder_ctx->mb_decision = FF_MB_DECISION_SIMPLE;
  encoder_ctx->qmin = 2;
  encoder_ctx->qmax = 31;
  encoder_ctx->max_qdiff = 4;
  encoder_ctx->gop_size = 12;    // 关键帧间隔
  encoder_ctx->max_b_frames = 1; // B帧数量
  // MPEG-4高级设置 - 修复VOL头问题
  encoder_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
  // 设置MPEG-4私有选项
  // av_opt_set(encoder_ctx->priv_data, "mpeg_quant", "1", 0);
  av_opt_set(encoder_ctx->priv_data, "mbd", "2", 0);
  av_opt_set(encoder_ctx->priv_data, "flags", "+mv0+cbp+mv4", 0);
  // av_opt_set(encoder_ctx->priv_data, "cmp", "2", 0);
  // av_opt_set(encoder_ctx->priv_data, "subcmp", "2", 0);
  // 强制生成VOL头
  // av_opt_set(encoder_ctx->priv_data, "packed_bistream", "1", 0);

  int ret = avcodec_open2(encoder_ctx, encoder, NULL);
  if (ret < 0) {
    char error_buf[256];
    av_strerror(ret, error_buf, sizeof(error_buf));
    fprintf(stderr, "Cannot open MPEG4 encoder: %s (error %d)\n", error_buf,
            ret);
    return -1;
  }

  return 0;
}

int openMisc() {
  // 帧缓冲区
  frame = av_frame_alloc();
  if (!frame) {
    fprintf(stderr, "Could not allocate frame.\n");
    return -1;
  }
  encoded_packet = av_packet_alloc();
  packet = av_packet_alloc();
  sws_ctx = sws_getContext(decoder_ctx->width, decoder_ctx->height,
                           decoder_ctx->pix_fmt, decoder_ctx->width,
                           decoder_ctx->height, AV_PIX_FMT_BGRA, SWS_POINT,
                           NULL, NULL, NULL);
  return 0;
}

bool codec_openStream(const char *url) {
  if (openInputStream(url) < 0)
    return false;
  if (openInputDecoder() < 0)
    return false;
  if (openMisc() < 0)
    return false;
  return true;
}

void codec_closeEverything() {
  if (packet_dumping) {
    codec_enablePacketDumping(false, NULL);
  }
  if (input_ctx != NULL)
    avformat_close_input(&input_ctx);
  if (encoder_ctx != NULL)
    avcodec_free_context(&encoder_ctx);
  if (decoder_ctx != NULL)
    avcodec_free_context(&decoder_ctx);
  if (encoded_packet != NULL)
    av_packet_free(&encoded_packet);
  if (frame != NULL)
    av_frame_free(&frame);
  if (sws_ctx != NULL) {
    sws_freeContext(sws_ctx);
    sws_ctx = NULL;
  }
  if (sws_ctx_yuv != NULL) {
    sws_freeContext(sws_ctx_yuv);
    sws_ctx_yuv = NULL;
  }
}

int openOutputFile(const char *output_file) {
  openOutputEncoder();

  if (in_stream == NULL || decoder_ctx == NULL) {
    fprintf(stderr, "No input stream.\n");
    return -1;
  }
  avformat_alloc_output_context2(&output_ctx, NULL, "mp4", output_file);
  if (!output_ctx) {
    fprintf(stderr, "Could not create output context.\n");
    return -1;
  }

  out_stream = avformat_new_stream(output_ctx, NULL);
  if (!out_stream) {
    fprintf(stderr, "Failed to allocate output stream.\n");
    return -1;
  }

  // 使用MPEG4编码器
  avcodec_parameters_from_context(out_stream->codecpar, encoder_ctx);
  out_stream->time_base = encoder_ctx->time_base;
  out_stream->r_frame_rate = encoder_ctx->framerate;
  out_stream->avg_frame_rate = encoder_ctx->framerate;
  out_stream->codecpar->bit_rate = encoder_ctx->bit_rate;

  // 设置流的编解码器标签
  if (output_ctx->oformat->flags & AVFMT_GLOBALHEADER) {
    encoder_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
  }
  av_dict_set(&out_stream->metadata, "handler_name", "VideoHandler", 0);

  // 打开输出文件并写入文件头
  if (!(output_ctx->oformat->flags & AVFMT_NOFILE)) {
    if (avio_open(&output_ctx->pb, output_file, AVIO_FLAG_WRITE) < 0) {
      fprintf(stderr, "Could not open output file: %s\n", output_file);
      return -1;
    }
  }
  if (avformat_write_header(output_ctx, NULL) < 0) {
    fprintf(stderr, "Error occurred when writing header.\n");
    return -1;
  }

  return 0;
}

void codec_enablePacketDumping(bool en, const char *dump_target) {
  if (packet_dumping != en) {
    LOCKRECORDER();
    packet_dumping = en;
    UNLOCKRECORDER();
    if (packet_dumping == true) // 打开
    {
      openOutputFile(dump_target);
      isFirstPTS = true;
    } else {
      if (output_ctx != NULL) {
        int ret;

        if (encoder_ctx != NULL) {
          ret = avcodec_send_frame(encoder_ctx, NULL);
          if (ret < 0) {
            fprintf(stderr, "Error sending flush frame: %d\n", ret);
          }

          // 接收所有剩余包
          while (1) {
            ret = avcodec_receive_packet(encoder_ctx, encoded_packet);
            if (ret == AVERROR_EOF) {
              break;
            } else if (ret == AVERROR(EAGAIN)) {
              continue;
            } else if (ret < 0) {
              fprintf(stderr,
                      "Error receiving packet during flush: (code %d)\n", ret);
              break;
            }

            // 写入剩余包
            if (encoded_packet->size > 0) {
              av_packet_rescale_ts(encoded_packet, decoder_ctx->time_base,
                                   out_stream->time_base);
              encoded_packet->stream_index = out_stream->index;

              encoded_packet->pos = -1;
              av_interleaved_write_frame(output_ctx, encoded_packet);
            }
            av_packet_unref(encoded_packet);
          }
        }

        // 关闭文件
        if (!(output_ctx->oformat->flags & AVFMT_NOFILE)) {
          ret = av_write_trailer(output_ctx);
          if (ret < 0) {
            fprintf(stderr, "Error writing trailer: %d\n", ret);
          }
          avio_closep(&output_ctx->pb);
        }

        avcodec_free_context(&encoder_ctx);
        avformat_free_context(output_ctx);
        encoder_ctx = NULL;
        output_ctx = NULL;
        out_stream = NULL;
      }
    }
  }
}

AVFrame *codec_getFrame() {
  int ret;
  while (av_read_frame(input_ctx, packet) >= 0) {
    if (packet->stream_index == video_stream_index) {
      // 输入到MJPEG解码器
      ret = avcodec_send_packet(decoder_ctx, packet);
      if (ret < 0) {
        fprintf(stderr, "Error sending packet for decoding.\n");
        return NULL;
      }
      while (ret >= 0) {
        // 读取解码器输出
        ret = avcodec_receive_frame(decoder_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
          break;
        else if (ret < 0) {
          fprintf(stderr, "Error during decoding.\n");
          return NULL;
        }

        // 进行MPEG4编码
        LOCKRECORDER();
        if (packet_dumping && output_ctx != NULL && encoder_ctx != NULL) {
          // 转换到YUV420P格式（MPEG4编码需要）
          if (!sws_ctx_yuv) {
            sws_ctx_yuv = sws_getContext(
                frame->width, frame->height, (enum AVPixelFormat)frame->format,
                frame->width, frame->height, AV_PIX_FMT_YUV420P, SWS_BILINEAR,
                NULL, NULL, NULL);
            if (!sws_ctx_yuv) {
              fprintf(stderr, "Could not create YUV scale context.\n");
            }
          }

          AVFrame *yuv_frame = av_frame_alloc();
          yuv_frame->format = AV_PIX_FMT_YUV420P;
          yuv_frame->width = frame->width;
          yuv_frame->height = frame->height;
          av_frame_get_buffer(yuv_frame, 0);
          sws_scale(sws_ctx_yuv, (const uint8_t *const *)frame->data,
                    frame->linesize, 0, frame->height, yuv_frame->data,
                    yuv_frame->linesize);
          if (isFirstPTS) {
            isFirstPTS = false;
            firstPTS = frame->pts;
            yuv_frame->pts = 0;
          } else {
            yuv_frame->pts = frame->pts - firstPTS;
          }

          // 编码帧
          ret = avcodec_send_frame(encoder_ctx, yuv_frame);
          if (ret < 0) {
            fprintf(stderr, "Error sending frame to encoder. (code %d)\n", ret);
          } else {
            while (ret >= 0) {
              ret = avcodec_receive_packet(encoder_ctx, encoded_packet);
              if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                break;
              else if (ret < 0) {
                fprintf(stderr, "Error during encoding.\n");
                break;
              }

              // 写入编码后的数据包
              av_packet_rescale_ts(encoded_packet, decoder_ctx->time_base,
                                   out_stream->time_base);
              encoded_packet->stream_index = out_stream->index;
              encoded_packet->pos = -1;
              av_interleaved_write_frame(output_ctx, encoded_packet);
              av_packet_unref(encoded_packet);
            }
          }

          av_frame_free(&yuv_frame);
        }
        UNLOCKRECORDER();

        // 转换到BGRA可显示格式
        AVFrame *scaled_frame = av_frame_alloc();
        scaled_frame->format = AV_PIX_FMT_BGRA;
        scaled_frame->width = decoder_ctx->width;
        scaled_frame->height = decoder_ctx->height;
        av_frame_get_buffer(scaled_frame, 0);
        sws_scale(sws_ctx, (const uint8_t *const *)frame->data, frame->linesize,
                  0, frame->height, scaled_frame->data, scaled_frame->linesize);
        scaled_frame->pts = frame->pts;
        // 不考虑出现需解码多个帧的情况，直接返回
        av_packet_unref(packet);
        return scaled_frame;
      }
    }
    av_packet_unref(packet);
  }
  printf("got nothing\n");
  return NULL;
}
