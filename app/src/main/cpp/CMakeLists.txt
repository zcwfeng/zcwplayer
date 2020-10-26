cmake_minimum_required(VERSION 3.10.2)
#project("zcwplayer")
aux_source_directory(. SOURCE)

add_library(
        native-lib
        SHARED
        ${SOURCE})


# 设置变量
set(libs ${CMAKE_SOURCE_DIR}/${ANDROID_ABI})
#-L：引入库查找路径
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${libs}")

# 引入头文件
include_directories(include)

target_link_libraries(
        native-lib
        avfilter avformat avcodec avutil swresample swscale rtmp android z OpenSLES
        log
)

