#include "httplib.h"
#include "cameraUtils.h"

httplib::Client cli(CAMERA_HOST_URL);
CameraUtils cameraUtils;

#define IF_CHECK_FILENAME "/proc/net/dev"
#define IF_CHECK_NAME "usb0"
#define IF_CHECK_MAX_SIZE 2048

bool CameraUtils::checkCameraConnection()
{
    static char if_check_buffer[IF_CHECK_MAX_SIZE];
    FILE *f = fopen(IF_CHECK_FILENAME, "r");
    if (f == NULL)
        return false;
    fread(if_check_buffer, IF_CHECK_MAX_SIZE, 1, f);
    fclose(f);
    if (strstr(if_check_buffer, IF_CHECK_NAME) != NULL)
    {
        return true;
    }
    return false;
}

void CameraUtils::setCameraIP()
{
    system("ifconfig usb0 up");
    system("ifconfig usb0 192.168.64.32");
}

void CameraUtils::initHTTPClient()
{
    cli.set_basic_auth("admin", "Ab123456");
}
#include <cJSON.h>
static std::string extract_boundary(const std::string &contentType);
void CameraUtils::getTemperature()
{
    auto res = cli.Get("/ISAPI/Thermal/channels/1/thermometry/1/rulesTemperatureInfo?format=json");
    if (res && res->status == 200)
    {
        /*
         {
        "ThermometryRulesTemperatureInfoList":  {
                "ThermometryRulesTemperatureInfo":      [{
                                "maxTemperature":       28.7,
                                "minTemperature":       27.7,
                                "averageTemperature":   28.3,
                                "MaxTemperaturePoint":  {
                                        "positionX":    1.000,
                                        "positionY":    0.983
                                },
                                "MinTemperaturePoint":  {
                                        "positionX":    0.918,
                                        "positionY":    0.008
                                },
                                "isFreezedata": false
                        }]
        }
}
         */

        cJSON *root = cJSON_Parse(res->body.c_str());
        cJSON *ThermometryRulesTemperatureInfoList = cJSON_GetObjectItem(root, "ThermometryRulesTemperatureInfoList");
        cJSON *ThermometryRulesTemperatureInfo = cJSON_GetObjectItem(ThermometryRulesTemperatureInfoList, "ThermometryRulesTemperatureInfo");
        cJSON *pack = cJSON_GetArrayItem(ThermometryRulesTemperatureInfo, 0);
        cJSON *maxTemperature = cJSON_GetObjectItem(pack, "maxTemperature");
        cJSON *minTemperature = cJSON_GetObjectItem(pack, "minTemperature");
        cJSON *averageTemperature = cJSON_GetObjectItem(pack, "averageTemperature");
        cJSON *MaxTemperaturePoint = cJSON_GetObjectItem(pack, "MaxTemperaturePoint");
        cJSON *MinTemperaturePoint = cJSON_GetObjectItem(pack, "MinTemperaturePoint");
        cJSON *positionX = cJSON_GetObjectItem(MaxTemperaturePoint, "positionX");
        cJSON *positionY = cJSON_GetObjectItem(MaxTemperaturePoint, "positionY");
        cJSON *positionX2 = cJSON_GetObjectItem(MinTemperaturePoint, "positionX");
        cJSON *positionY2 = cJSON_GetObjectItem(MinTemperaturePoint, "positionY");
        lastResult.maxTemperature = maxTemperature->valuedouble;
        lastResult.minTemperature = minTemperature->valuedouble;
        lastResult.averageTemperature = averageTemperature->valuedouble;
        lastResult.MaxTemperaturePoint.positionX = positionX->valuedouble;
        lastResult.MaxTemperaturePoint.positionY = positionY->valuedouble;
        lastResult.MinTemperaturePoint.positionX = positionX2->valuedouble;
        lastResult.MinTemperaturePoint.positionY = positionY2->valuedouble;
        lastResult.isFreezedata = cJSON_GetObjectItem(pack, "isFreezedata")->valueint;
        cJSON_Delete(root);
    }
    else
    {
        printf("Failed to get temperature\n");
    }

    res = cli.Get("/ISAPI/Thermal/channels/1/thermometry/jpegPicWithAppendData?format=json");
    if (res && res->status == 200)
    {
        // Parse the response headers to get the boundary string
        std::string contentType = res->get_header_value("Content-Type");
        std::string boundary = extract_boundary(contentType);

        // Split the response body into parts using the boundary string
        std::vector<std::string> parts = split_multipart(res->body, boundary);
        if (parts.size() < 3)
        {
            printf("Failed to split multipart response\n");
        }
        lastResult.centerTemperature = *(float *)((uint8_t *)parts[2].c_str() + ((160 + 120 * 160) * 4));
    }
}

const char *color_palette[] = {
    "WhiteHot",
    "BlackHot",
    "Fusion1",
    "Fusion2",
    "Rainbow",
    "Ironbow1",
    "Ironbow2",
    "Sepia",
    "Color1",
    "Color2",
    "IceFire",
    "Rain",
    "RedHot",
    "GreenHot",
    "DeepBlue",
};

void CameraUtils::setColorPalette(int palette)
{
    std::string data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Palettes><mode>";
    if (palette < 0 || palette >= IR_COLOR_PALETTE_MAX)
        palette = IR_COLOR_PALETTE_DEFAULT;
    data += color_palette[palette];
    data += "</mode></Palettes>";
    cli.Put("/ISAPI/Image/channels/1/Palettes", data, "application/xml");
}

void CameraUtils::setDigitalNoiceReduce(int mode, int frameLevel, int interFrameLevel)
{
    std::string data;
    //= "<?xml version=\"1.0\" encoding=\"UTF-8\"?><DigitalNoiseReduction><mode>";
    if (mode < IR_DNR_MODE_CLOSE || mode > IR_DNR_MODE_ADVANCED)
        mode = IR_DNR_MODE_CLOSE;
    if (frameLevel < 0 || frameLevel > 100)
        frameLevel = 50;
    if (interFrameLevel < 0 || interFrameLevel > 100)
        interFrameLevel = 50;
    if (mode == IR_DNR_MODE_CLOSE)
    {
        data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><NoiseReduce><mode>close</mode></NoiseReduce>";
    }
    else if (mode == IR_DNR_MODE_GENERAL)
    {
        data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><NoiseReduce><mode>general</mode><GeneralMode><generalLevel>" + std::to_string(frameLevel) + "</frameLevel></GeneralMode></NoiseReduce>";
    }
    else
    {
        data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><NoiseReduce><mode>advanced</mode><AdvancedMode><FrameNoiseReduceLevel>" + std::to_string(frameLevel) + "</FrameNoiseReduceLevel><InterFrameNoiseReduceLevel>" + std::to_string(interFrameLevel) + "</InterFrameNoiseReduceLevel></AdvancedMode></NoiseReduce>";
    }
    cli.Put("/ISAPI/Image/channels/1/noiseReduce", data, "application/xml");
}

void CameraUtils::setDigitalDetailEnhancement(bool en, int level)
{
    std::string data;
    if (level < 0 || level > 100)
        level = 50;
    if (en)
    {
        data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><DDE><mode>on</mode><GeneralMode><enhanceLevel>" + std::to_string(level) + "</enhanceLevel></GeneralMode></DDE>";
    }
    else
    {
        data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><DDE><mode>close</mode></DDE>";
    }
    cli.Put("/ISAPI/Image/channels/1/DDE", data, "application/xml");
}

static std::string extract_boundary(const std::string &contentType)
{
    std::string boundary;
    size_t pos = contentType.find("boundary=");
    if (pos != std::string::npos)
    {
        boundary = contentType.substr(pos + 9);
    }
    return boundary;
}

static std::vector<std::string> split_multipart(const std::string &body, const std::string &boundary)
{
    std::vector<std::string> parts;
    std::string delimiter = "--" + boundary;
    size_t start = body.find(delimiter);
    while (start != std::string::npos)
    {
        size_t start_length = body.find("Content-Length:", start);
        size_t end_length = body.find("\r\n", start_length);
        std::string this_part_length_str = body.substr(start_length + 15, end_length);
        if (start_length == std::string::npos || end_length == std::string::npos)
        {
            break;
        }
        size_t this_part_length = std::stoi(this_part_length_str);
        start = body.find("\r\n\r\n", start) + 4;
        size_t end = body.find(delimiter, start + this_part_length);
        if (end != std::string::npos)
        {
            parts.push_back(body.substr(start, this_part_length));
            start = end;
        }
        else
        {
            break;
        }
    }
    return parts;
}

float CameraUtils::readJpegWithExtra(const char *save_filename, int result_x, int result_y)
{
    auto res = cli.Get("/ISAPI/Thermal/channels/1/thermometry/jpegPicWithAppendData?format=json");
    if (res && res->status == 200)
    {
        // Parse the response headers to get the boundary string
        std::string contentType = res->get_header_value("Content-Type");
        std::string boundary = extract_boundary(contentType);

        // Split the response body into parts using the boundary string
        std::vector<std::string> parts = split_multipart(res->body, boundary);
        if (parts.size() < 3)
        {
            printf("Failed to split multipart response\n");
            return 0.0f;
        }
        if (save_filename != NULL)
        {
            std::ofstream file(std::string(save_filename) + ".jpeg");
            if (file.is_open())
            {
                file << parts[1];
                file.close();
            }
            std::ofstream file2(std::string(save_filename) + ".raw");
            if (file2.is_open())
            {
                file2 << parts[2];
                file2.close();
            }
        }
        lastCenterTemperature = *(float *)((uint8_t *)parts[2].c_str() + ((result_x + result_y * 160) * 4));
        return lastCenterTemperature;
    }
    return 0.0f;
}

void CameraUtils::setCenterMeasure(bool en)
{
    auto res = cli.Get("/ISAPI/Thermal/channels/1/temperatureCorrect?format=json");
    char data[1024];
    if (res && res->status == 200)
    {
        cJSON *root = cJSON_Parse(res->body.c_str());
        cJSON *TemperatureCorrect = cJSON_GetObjectItem(root, "TemperatureCorrect");
        cJSON *streamOverlay = cJSON_GetObjectItem(TemperatureCorrect, "streamOverlay");
        cJSON_SetBoolValue(streamOverlay, en);
        cJSON_PrintPreallocated(root, data, 1024, cJSON_False);
        cJSON_Delete(root);
        cli.Put("/ISAPI/Thermal/channels/1/temperatureCorrect?format=json", data, "application/json");
    }
}

void CameraUtils::calibrateManually()
{
    cli.Put("/ISAPI/Image/channels/1/ManualShutterCorrect", "", "application/xml");
}

void CameraUtils::set4117Cursor(bool min, bool max)
{
    auto res = cli.Get("/ISAPI/Thermal/channels/1/thermometry/basicParam");
    int len;
    if (res && res->status == 200) {
        std::string body = res->body;
        std::string line;
        std::string result = "";
        int last_start = 0;
        int this_end;
        int length = body.length();
        while (1)
        {
            this_end = body.find("\n", last_start);
            if (this_end == std::string::npos){
                result += body.substr(last_start, length - last_start);
                break;
            }
            line = body.substr(last_start, this_end - last_start);
            if (line == "") {
                printf("Warning: Empty line\n");
                break;
            }
            last_start = this_end + 1;
            if (line.find("displayMax") != std::string::npos)
            {
                if (max) {
                    result += "<displayMaxTemperatureEnabled>true</displayMaxTemperatureEnabled>\n";
                } else {
                    result += "<displayMaxTemperatureEnabled>false</displayMaxTemperatureEnabled>\n";
                }
            }
            else if (line.find("displayMin") != std::string::npos)
            {
                if (min) {
                    result += "<displayMinTemperatureEnabled>true</displayMinTemperatureEnabled>\n";
                } else {
                    result += "<displayMinTemperatureEnabled>false</displayMinTemperatureEnabled>\n";
                }
            }
            else if (line.find("<enabled>") != std::string::npos)
            {
                result += "<enabled>true</enabled>\n";
            }
            else if (line.find("<streamOverlay>") != std::string::npos)
            {
                result += "<streamOverlay>true</streamOverlay>\n";
            }
            else
            {
                result += line + "\n";
            }
        }
        cli.Put("/ISAPI/Thermal/channels/1/thermometry/basicParam", result, "application/x-www-form-urlencoded; charset=UTF-8");
    }
}