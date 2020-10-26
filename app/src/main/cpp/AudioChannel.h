//
// Created by 张传伟 on 2020/10/25.
//

#ifndef ZCWPLAYER_AUDIOCHANNEL_H
#define ZCWPLAYER_AUDIOCHANNEL_H


#include "BaseChannel.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavutil/rational.h"
#include <libswresample/swresample.h>

}

class AudioChannel : public BaseChannel {
    friend void *audioPlay_t(void *args);

    friend void bqPlayerCallback(SLAndroidSimpleBufferQueueItf queue, void *pContext);

public:
    AudioChannel(int channelId, JavaCallHelper *helper, AVCodecContext *avCodecContext,
                 const AVRational &timeBase);

    virtual ~AudioChannel();

public:
    virtual void play();

    virtual void stop();

    virtual void decode();

private:
    void _play();
    int _getData();
private:
    pthread_t audioDecodeTask, audioPlayTask;
    SwrContext *swrContext = 0;
    uint8_t *buffer;
    int bufferCount;
    int out_channels;
    int out_sampleSize;
};


#endif //ZCWPLAYER_AUDIOCHANNEL_H
