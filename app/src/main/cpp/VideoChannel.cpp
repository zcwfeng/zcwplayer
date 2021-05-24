//
// Created by 张传伟 on 2020/10/23.
//

#include "VideoChannel.h"
#include "Log.h"

extern "C" {
#include <libswscale/swscale.h>
#include <libavutil/rational.h>
#include <libavutil/imgutils.h>
#include <libavutil/time.h>
};
/* no AV sync correction is done if below the minimum AV sync threshold */
#define AV_SYNC_THRESHOLD_MIN 0.04
/* AV sync correction is done if above the maximum AV sync threshold */
#define AV_SYNC_THRESHOLD_MAX 0.1

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
        // 生产太慢等一下数据
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
    isPlaying = 0;
    helper = 0;
    pthread_join(videoDecodeTask, 0);
    pthread_join(videoPlayTask, 0);
    if (window) {
        ANativeWindow_release(window);
    }
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
                                            avCodecContext->pix_fmt,//自动获取xxx.mp4等的像素格式AV_PIX_FMT_RGBA_y420p
                                            avCodecContext->width,
                                            avCodecContext->height,
                                            AV_PIX_FMT_RGBA,
                                            SWS_FAST_BILINEAR,//SWS_FAST_BILINEAR 或者 SWS_BILINEAR 算法
                                            0, 0, 0);// SwsFilter效果用OpenGL做
    uint8_t *data[4];// 用来接受结果
    int linesize[4];
    av_image_alloc(data, linesize, avCodecContext->width,
                   avCodecContext->height, AV_PIX_FMT_RGBA,
                   1);
    AVFrame *frame = 0;

    double frame_delay = 1.0 / fps;

    int ret;
    while (isPlaying) {
        //阻塞方法
        ret = frame_queue.deQueue(frame);
        // 可能用户停止了播放
        if (!isPlaying) {
            break;
        }
        // 原始包加入队列，需要等一下
        if (!ret) {
            continue;
        }
        //RGBA
        //R
        //G
        //B
        //A
        //byte[][]
        // ffmpeg 标准额外延时，视频顺畅的刷新
        double extra_delay = frame->repeat_pict / (2 * fps);
        double delay = extra_delay * frame_delay;
        // 音视频同步
        if (audioChannel) {
            // 值：就是pts 和音频中的一样，pts  优化后的数据 best_effort_timestamp
            clock = frame->best_effort_timestamp * av_q2d(time_base);
            double diff = clock - audioChannel->clock;
            // 给一个时间差允许范围，不需要太苛刻 ff_player 和ijk_player 参考0.04-0.1 秒 之间

            /**
             * 1.正常延迟时间delay < 0.04 同步阈值就是0.04
             * 2.0.04 < delay < 0.1 同步阈值就是 delay
             * 3. delay > 0.1 同步阈值就是 0.1
             */
            double sync = FFMAX(AV_SYNC_THRESHOLD_MIN, FFMIN(AV_SYNC_THRESHOLD_MAX, delay));
            if (diff <= -sync) {
                // 视频落后太多，需要同步，修改delay 时间，减小delay，赶上音频
                delay = FFMAX(0, delay + diff);
            } else if (diff >= sync) {
                // 视频快乐，让delay 时间大一些，等待音频同步上来
                delay = delay + diff;
            }

            LOGE("Video:%lf Audio:%lf delay:%lf A-V=%lf", clock, audioChannel->clock, delay, -diff);

        }

        av_usleep(delay * 1000000);
        // TODO 2、指针数据，比如RGBA，每一个维度的数据就是一个指针，那么RGBA需要4个指针，所以就是4个元素的数组，数组的元素就是指针，指针数据
        //      3、每一行数据他的数据个数
        //      4、 offset
        //      5、 要转化图像的高
        sws_scale(swsContext, frame->data, frame->linesize, 0,
                  frame->height, data, linesize);

        _onDraw(data, linesize, avCodecContext->width, avCodecContext->height);
        releaseAvFrame(frame);
    }

    av_free(&data[0]);
    isPlaying = 0;
    releaseAvFrame(frame);
    sws_freeContext(swsContext);
}

void VideoChannel::_onDraw(uint8_t **Data, int *linesize, int width, int height) {
    pthread_mutex_lock(&surfaceMutex);
    if (!window) {
        pthread_mutex_lock(&surfaceMutex);
        return;
    }
    ANativeWindow_setBuffersGeometry(window, width, height,
                                     WINDOW_FORMAT_RGBA_8888);
    ANativeWindow_Buffer buffer;
    // 自己有缓冲区
    if (ANativeWindow_lock(window, &buffer, 0) != 0) {
        ANativeWindow_release(window);
        window = 0;
        pthread_mutex_unlock(&surfaceMutex);
        return;
    }
    //将视频数据刷到buffer
    uint8_t *dstData = static_cast<uint8_t *>(buffer.bits);
    int dstSize = buffer.stride * 4;
    uint8_t *srcData = Data[0];
    int srcSize = linesize[0];

    /*
     * window: 4x4,8 位
     * ffmpeg: 4x4,4
     *
     * window
     * [
     * x,x,x,x,x,x,x,x,
     * x,x,x,x,x,x,x,x
     * x,x,x,x,x,x,x,x
     * x,x,x,x,x,x,x,x
     * ]
     *
     * 我们有效数据是前4个，所以ffmpeg取每行的前四个，一行一行的赋值，画这个图片
     *
     *
     *
     */



    // 一行一行拷贝，ffmpeg原始数据和对齐后数据可能不一样
    for (int i = 0; i < buffer.height; ++i) {
        memcpy(dstData + i * dstSize, srcData + i * srcSize, srcSize);
    }


    ANativeWindow_unlockAndPost(window);
    pthread_mutex_unlock(&surfaceMutex);
}







