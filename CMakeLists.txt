cmake_minimum_required(VERSION 3.7.4)

project(LiThermal)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "src/*.c")	#遍历获取source/路径下所有的*.cpp和*.c文件列表

add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)	#添加宏定义
add_compile_definitions(USE_SUNXIFB_DOUBLE_BUFFER)
add_compile_definitions(USE_SUNXIFB_CACHE)
add_compile_definitions(USE_SUNXIFB_G2D)
add_compile_definitions(USE_SUNXIFB_G2D_ROTATE)
add_compile_definitions(CONF_G2D_VERSION_NEW)
add_compile_options(-O2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -Wno-psabi -O2")
set(LV_CONF_PATH "../../include/lv_conf.h")	#设置lv_conf.h的路径

add_executable(${PROJECT_NAME} ${SRC_DIR_LIST})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(libs)
include_directories(include)
include_directories(include/linux_include)
include_directories(include/rlottie_inc)
include_directories(build/target/usr/include)
include_directories(build/toolchain-sunxi-musl/toolchain/include)

add_subdirectory(libs/lvgl)
add_subdirectory(libs/lv_drivers)
target_link_libraries(${PROJECT_NAME} lvgl lv_drivers uapi avcodec avdevice avformat avfilter avutil swscale pthread rlottie m)
