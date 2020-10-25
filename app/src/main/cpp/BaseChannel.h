//
// Created by 张传伟 on 2020/10/23.
//

#ifndef ZCWPLAYER_BASECHANNEL_H
#define ZCWPLAYER_BASECHANNEL_H
extern "C" {
#include <libavcodec/avcodec.h>
};

#include "JavaCallHelper.h"

#include "safe_queue.h"


class BaseChannel {
public:
    BaseChannel(int channelId, JavaCallHelper *helper,
                AVCodecContext *avCodecContext,
                const AVRational &timeBase)
            : channelId(channelId),
              helper(helper),
              avCodecContext(avCodecContext),
              time_base(timeBase) {
        pkt_queue.setReleaseHandle(releaseAvPacket);
        frame_queue.setReleaseHandle(releaseAvFrame);

    }

    virtual ~BaseChannel() {
        if (avCodecContext) {
            avcodec_close(avCodecContext);
            avcodec_free_context(&avCodecContext);
            avCodecContext = 0;
        }


    }
    virtual void play() = 0;

    virtual void stop() = 0;

    virtual void decode() = 0;

    void setEnable(bool enable) {
        pkt_queue.setEnable(enable);
        frame_queue.setEnable(enable);
    }

    static void releaseAvFrame(AVFrame *&frame) {
        if (frame) {
            av_frame_free(&frame);
            frame = 0;
        }
    }


    static void releaseAvPacket(AVPacket *&packet) {
        if (packet) {
            av_packet_free(&packet);
            packet = 0;
        }
    }

public:
    int channelId;
    JavaCallHelper *helper;
    AVCodecContext *avCodecContext;
    AVRational time_base;
    SafeQueue<AVPacket *> pkt_queue;
    SafeQueue<AVFrame *> frame_queue;
    bool isPlaying = false;
    double clock = 0;
};


#endif //ZCWPLAYER_BASECHANNEL_H
