//
// Created by 张传伟 on 2020/10/23.
//

#ifndef ZCWPLAYER_VIDEOCHANNEL_H
#define ZCWPLAYER_VIDEOCHANNEL_H


#include <android/native_window.h>
#include "BaseChannel.h"
#include "AudioChannel.h"

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

    void _onDraw(uint8_t **Data, int *linesize, int width, int height);

private:
    int fps;
    pthread_mutex_t surfaceMutex;
    pthread_t videoDecodeTask, videoPlayTask;
    bool isPlaying;
    ANativeWindow *window = 0;
public:
    AudioChannel *audioChannel = 0;

};


#endif //ZCWPLAYER_VIDEOCHANNEL_H
