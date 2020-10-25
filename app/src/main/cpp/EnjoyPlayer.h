//
// Created by 张传伟 on 2020/10/21.
//

#ifndef ZCWPLAYER_ENJOYPLAYER_H
#define ZCWPLAYER_ENJOYPLAYER_H

#include <pthread.h>
#include "JavaCallHelper.h"
#include "VideoChannel.h"
#include <android/native_window_jni.h>

extern "C" {
#include <libavformat/avformat.h>
}

class EnjoyPlayer {
    friend void *prepare_t(void *args);

    friend void *start_t(void *args);

public:
    EnjoyPlayer(JavaCallHelper *helper);

    void start();

    void setWindow(ANativeWindow *window);

public:
    void prepare();

    void setDataSource(const char *path);


private:
    void _prepare();

    void _start();

private:
    char *path;
    pthread_t prepareTask;
    JavaCallHelper *helper;
    int64_t duration;
    VideoChannel *videoChannel;
    pthread_t startTask;
    bool isPlaying;
    AVFormatContext *avFormatContext;
    ANativeWindow *window = 0;
};


#endif //ZCWPLAYER_ENJOYPLAYER_H
