//
// Created by 张传伟 on 2020/10/23.
//

#include "VideoChannel.h"

extern "C" {
#include <libswscale/swscale.h>
#include <libavutil/rational.h>
#include <libavutil/imgutils.h>
};

VideoChannel::VideoChannel(int channelId, JavaCallHelper *helper, AVCodecContext *avCodecContext,
                           const AVRational &timeBase, int fps)
        : BaseChannel(channelId, helper,
                      avCodecContext,
                      timeBase), fps(fps) {
    pthread_mutex_init(&surfaceMutex, 0);

}

VideoChannel::~VideoChannel() {
    pthread_mutex_destroy(&surfaceMutex);
}

void VideoChannel::decode() {
    AVPacket *avPacket = 0;
    while (isPlaying) {
        // 阻塞
        //1. 能够渠道数据
        //2.停止播放。
        int ret = pkt_queue.deQueue(avPacket);
        if (!isPlaying) {
            break;
        }
        if (!ret) {
            continue;
        }
        // 向解码器发送数据
        avcodec_send_packet(avCodecContext, avPacket);
        releaseAvPacket(avPacket);//释放掉
        if (ret < 0) {
            //失败
            break;
        }
        AVFrame *frame = av_frame_alloc();
        // 读取
        ret = avcodec_receive_frame(avCodecContext, frame);
        if (ret == AVERROR(EAGAIN)) {// 我还要
            continue;
        } else if (ret < 0) {
            break;
        }
        frame_queue.enQueue(frame);

    }
    releaseAvPacket(avPacket);
}

void VideoChannel::stop() {

}

void *videoDecode_t(void *args) {
    VideoChannel *videoChannel = static_cast<VideoChannel *>(args);
    videoChannel->decode();
    return 0;

}

void *videoPlay_t(void *args) {
    VideoChannel *videoChannel = static_cast<VideoChannel *>(args);
    videoChannel->_play();
    return 0;

}

void VideoChannel::play() {
    isPlaying = 1;
    //开启队列工作
    setEnable(true);
    // 解码
    pthread_create(&videoDecodeTask, 0, videoDecode_t, this);
    // 播放
    pthread_create(&videoPlayTask, 0, videoPlay_t, this);
}

void VideoChannel::setWindow(ANativeWindow *window) {
    // 注意线程安全，我们这里是子线程操作，需要加上锁
    pthread_mutex_lock(&surfaceMutex);
    if (this->window) {
        ANativeWindow_release(this->window);
    }
    this->window = window;
    pthread_mutex_unlock(&surfaceMutex);

}

void VideoChannel::_play() {
    //YUV 转换 ijkPlayer 用的是libYUV -> RGBA
    // 缩放,格式转换
    SwsContext *swsContext = sws_getContext(avCodecContext->width,
                                            avCodecContext->height,
                                            avCodecContext->pix_fmt,
                                            avCodecContext->width,
                                            avCodecContext->height,
                                            AV_PIX_FMT_RGBA,
                                            SWS_FAST_BILINEAR,
                                            0, 0, 0);
    uint8_t *data[4];// 用来接受结果
    int linesize[4];
    av_image_alloc(data, linesize, avCodecContext->width,
                   avCodecContext->height, AV_PIX_FMT_RGBA,
                   1);
    AVFrame *frame = 0;
    int ret;
    while (isPlaying) {
        //阻塞方法
        ret = frame_queue.deQueue(frame);
        // 可能用户停止了播放
        if (!isPlaying) {
            break;
        }
        if (!ret) {
            continue;
        }
        //RGBA
        //R
        //G
        //B
        //A
        //byte[][]
    // TODO 2、指针数据，比如RGBA，每一个维度的数据就是一个指针，那么RGBA需要4个指针，所以就是4个元素的数组，数组的元素就是指针，指针数据
    //      3、每一行数据他的数据个数
    //      4、 offset
    //      5、 要转化图像的高
        sws_scale(swsContext, frame->data, frame->linesize, 0,
                  frame->height, data, linesize);

        onDraw(data, linesize, avCodecContext->width, avCodecContext->height);

    }

    av_free(&data[0]);
    isPlaying = 0;
    releaseAvFrame(frame);
    sws_freeContext(swsContext);
}

void VideoChannel::onDraw(uint8_t **data, int *linesize, int width, int height) {
    pthread_mutex_lock(&surfaceMutex);
    if (!window) {
        pthread_mutex_lock(&surfaceMutex);
        return;
    }
    ANativeWindow_setBuffersGeometry(window, width, height,
                                     WINDOW_FORMAT_RGBA_8888);
    ANativeWindow_Buffer buffer;
    if (ANativeWindow_lock(window, &buffer, 0) != 0) {
        ANativeWindow_release(window);
        window = 0;
        pthread_mutex_unlock(&surfaceMutex);
        return;
    }
    //将视频数据刷到buffer
    uint8_t *dstData = static_cast<uint8_t *>(buffer.bits);
    int dstSize = buffer.stride * 4;
    uint8_t *srcData = data[0];
    int srcSize = linesize[0];

    // 一行一行拷贝，ffmpeg原始数据和对齐后数据可能不一样
    for (int i = 0; i < buffer.height; ++i) {
        memcpy(dstData + i * dstSize, srcData + i * srcSize, srcSize);
    }


    ANativeWindow_unlockAndPost(window);
    pthread_mutex_unlock(&surfaceMutex);
}







