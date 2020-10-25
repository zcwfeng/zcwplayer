//
// Created by 张传伟 on 2020/10/23.
//

#ifndef ZCWPLAYER_VIDEOCHANNEL_H
#define ZCWPLAYER_VIDEOCHANNEL_H


#include <android/native_window.h>
#include "BaseChannel.h"

extern "C" {
#include <libavcodec/avcodec.h>

};

class VideoChannel : public BaseChannel {
    friend void *videoPlay_t(void *args);

public:
    VideoChannel(int channelId, JavaCallHelper *helper, AVCodecContext *avCodecContext,
                 const AVRational &timeBase, int fps);

    virtual ~VideoChannel();

    void setWindow(ANativeWindow *window);



public:
    virtual void play();

    virtual void stop();

    virtual void decode();

private:
    void _play();

private:
    int fps;
    pthread_mutex_t surfaceMutex;
    pthread_t videoDecodeTask, videoPlayTask;
    bool isPlaying;
    ANativeWindow *window = 0;

    void onDraw(uint8_t *Data[4], int linesize[4], int width, int height);
};


#endif //ZCWPLAYER_VIDEOCHANNEL_H
