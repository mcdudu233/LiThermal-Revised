#include "my_main.h"
pthread_mutex_t lv_mutex;

/// @brief 热成像刷新线程
pthread_t thread_app;
void *thread_app_func(void *)
{
    static uint32_t last_color_palette = -1;
    static uint32_t last_show_center = -1;
    static int centerRefreshCounter = 0;
    static uint32_t last_use4117Cursors = -1;
    static uint32_t last_enableMinValueDisplay = -1;
    static uint32_t last_enableMaxValueDisplay = -1;
    while (cameraUtils.connected == false)
        usleep(40000);
    LOCKLV();
    widget_graph_updateSettings();
    ui_crosshairs_updateVisibility();
    widget_graph_check_visibility();
    UNLOCKLV();
    while (1)
    {
        if (last_color_palette != globalSettings.colorPalette)
        {
            last_color_palette = globalSettings.colorPalette;
            cameraUtils.setColorPalette(globalSettings.colorPalette);
        }
        if (last_use4117Cursors != globalSettings.use4117Cursors)
        {
            last_use4117Cursors = globalSettings.use4117Cursors;
            if (last_use4117Cursors)
            {
                cameraUtils.set4117Cursor(globalSettings.enableMinValueDisplay, globalSettings.enableMaxValueDisplay);
                cameraUtils.setCenterMeasure(globalSettings.enableCenterValueDisplay);
            }
            else
            {
                cameraUtils.set4117Cursor(false, false);
                cameraUtils.setCenterMeasure(false);
            }
            last_enableMaxValueDisplay = globalSettings.enableMaxValueDisplay;
            last_enableMinValueDisplay = globalSettings.enableMinValueDisplay;
            last_show_center = globalSettings.enableCenterValueDisplay;
        }
        if (last_enableMaxValueDisplay != globalSettings.enableMaxValueDisplay || last_enableMinValueDisplay != globalSettings.enableMinValueDisplay || last_show_center != globalSettings.enableCenterValueDisplay)
        {
            if (globalSettings.use4117Cursors)
            {
                cameraUtils.set4117Cursor(globalSettings.enableMinValueDisplay, globalSettings.enableMaxValueDisplay);
                cameraUtils.setCenterMeasure(globalSettings.enableCenterValueDisplay);
            }
            last_enableMaxValueDisplay = globalSettings.enableMaxValueDisplay;
            last_enableMinValueDisplay = globalSettings.enableMinValueDisplay;
            last_show_center = globalSettings.enableCenterValueDisplay;
        }
        if (current_mode == MODE_MAINPAGE || current_mode == MODE_CAMERA_SETTINGS)
        {
            cameraUtils.getTemperature();
        }
        LOCKLV();
        ui_crosshairs_updatePos();
        widget_graph_check_visibility();
        UNLOCKLV();

        usleep(40000);
    }
    return NULL;
}

// UI刷新线程
pthread_t thread_ui;
void *thread_ui_func(void *)
{
    HAL::lv_loop();
}

// 自动配置端口映射
void port_forward(){
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");
    system("sysctl -w net.ipv4.conf.all.route_localnet=1");
    system("modprobe iptable_nat");
    system("modprobe xt_nat");
    system("iptables -t nat -F");
    system("iptables -t nat -X");
    system("iptables -t nat -A OUTPUT -p tcp -d 127.0.0.1 --dport 80 -j DNAT --to 192.168.64.64:80");
    system("iptables -t nat -A POSTROUTING -p tcp -s 127.0.0.1 -d 192.168.64.64 --dport 80 -j SNAT --to 192.168.64.32");
}

int main()
{
    sleep(1); // Why?
    port_forward();

    system("mkdir " GALLERY_PATH);
    pthread_mutex_init(&lv_mutex, NULL);
    HAL::init();
    readFiles(GALLERY_PATH);
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(lv_layer_sys(), LV_OBJ_FLAG_SCROLLABLE);
    printf("Loop begin\n");
    waitboot_scr_load(lv_scr_act());
    widget_graph_create();
    ui_crosshairs_create();
    pthread_create(&thread_ui, NULL, thread_ui_func, NULL);
    cameraUtils.initHTTPClient();
    pthread_create(&thread_app, NULL, thread_app_func, NULL);
    void *result;
    pthread_join(thread_ui, &result);
    return 0;
}
