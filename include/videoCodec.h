#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>

#ifdef __cplusplus
}
#endif

extern bool packet_dumping;

bool codec_openStream(const char *url);

void codec_closeEverything();
/**
 * @brief 使能或禁用数据包转储
 * @param en 使能或禁用
 * @param dump_target 转储目标文件
 * @example codec_enablePacketDumping(true, "dump.mjpeg");
 * @example codec_enablePacketDumping(false, NULL);
 * @note
 * 在getFrame时会自动转储获取到的MJPEG数据包，结束录制时调用codec_enablePacketDumping(false,
 * NULL)关闭转储
 */
void codec_enablePacketDumping(bool en, const char *dump_target,
                               bool saveMp4 = true, bool saveMjpeg = true);
/**
 * @brief 获取解码后的帧
 * @return AVFrame* 解码后的帧
 * @note 该函数会阻塞直到获取到一帧解码后的图像
 */
AVFrame *codec_getFrame();

/**
 * @brief 将带OSD的BGRA帧编码写入MP4（仅在录制OSD模式下使用）
 * @param bgra_data ARGB8888格式的帧数据（来自lv_snapshot_take）
 */
void codec_encodeOSDFrame(const uint8_t *bgra_data);
