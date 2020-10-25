//
// Created by 张传伟 on 2020/10/21.
//
#include <malloc.h>
#include <cstring>
#include "EnjoyPlayer.h"
#include "Log.h"

void *prepare_t(void *args) {
    EnjoyPlayer *player = static_cast<EnjoyPlayer *>(args);
    player->_prepare();
    return 0;
}

EnjoyPlayer::EnjoyPlayer(JavaCallHelper *helper) : helper(helper) {
    avformat_network_init();
    videoChannel = 0;
}

void EnjoyPlayer::setDataSource(const char *path_) {
//    c 实现拷贝
//    path = static_cast<char *>(malloc(strlen(path_) + 1));
//    memset((void *)path,0,strlen(path_)+1);
//    memcpy(path,path_,strlen(path_))
    path = new char[strlen(path_) + 1];
    strcpy(path, path_);
}

void EnjoyPlayer::prepare() {
    //解析  耗时！
    pthread_create(&prepareTask, 0, prepare_t, this);
}

void EnjoyPlayer::_prepare() {
    avFormatContext = avformat_alloc_context();
    /**
     * 1.打开媒体文件
     */
//参数3，文件的封装格式，传null表示自动检测格式 avi/flv
//参数4，map集合，如打开网络文件
//    AVDictionary **opts;
//    av_dict_set(opts, "timeout", "300000", 0);
    int ret = avformat_open_input(&avFormatContext, path, 0, 0);
    if (ret != 0) {
        LOGE("打开%s失败,返回:%d,错误描述%s", path, ret, av_err2str(ret));
        helper->onError(FFMPEG_CAN_NOT_OPEN_URL, THREAD_CHILD);
        return;
    }

    /**
     * 2.查找媒体流
     */
    ret = avformat_find_stream_info(avFormatContext, 0);
    if (ret < 0) {
        LOGE("查找媒体流 %s 失败，返回:%d 错误描述:%s", path, ret, av_err2str(ret));
        helper->onError(FFMPEG_CAN_NOT_FIND_STREAMS, THREAD_CHILD);
        return;
    }

    // 得到视频时长，单位s，AV_TIME_BASE 是FFmpeg宏定义微妙
    duration = avFormatContext->duration / AV_TIME_BASE;
    // 这个媒体文件有几道媒体流（视频流，音频流），用ffmpeg -i xxx 可以查看
    for (int i = 0; i < avFormatContext->nb_streams; ++i) {
        AVStream *avStream = avFormatContext->streams[i];
        // 解码信息 avcodec 过时不用了换成AVCodecParameters
        AVCodecParameters *parameters = avStream->codecpar;
        // ffmpeg -codecs 可以查看我们当前支持的各种解码格式
        // 查找解码器
        AVCodec *dec = avcodec_find_decoder(parameters->codec_id);

        if (!dec) {
            helper->onError(FFMPEG_FIND_DECODER_FAIL, THREAD_CHILD);
            return;
        }
        // 打开解码器
        AVCodecContext *codecContext = avcodec_alloc_context3(dec);
        // 把解码信息赋值给解码器上下文的各种成员.(如果不这么调用，我们需要手动一个一个赋值codecContext->width = ...)
        // avcodec_parameters_from_context() 注意不要写错
        if (avcodec_parameters_to_context(codecContext, parameters) < 0) {
            helper->onError(FFMPEG_ALLOC_CODEC_CONTEXT_FAIL, THREAD_CHILD);
            return;
        }
        // if==0 失败
        if (avcodec_open2(codecContext, dec, 0) != 0) {
            helper->onError(FFMPEG_OPEN_DECODER_FAIL, THREAD_CHILD);
            return;
        }
        // 判断是音频还是视频
        if (parameters->codec_type == AVMEDIA_TYPE_AUDIO) {

        } else if (parameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            //avg_frame_rate 平均帧率
            int fps = av_q2d(avStream->avg_frame_rate);
            videoChannel = new VideoChannel(i, helper, codecContext, avStream->time_base, fps);
            videoChannel->setWindow(window);
        }

    }
    //TODO 未处理音频
    if (!videoChannel) {
        helper->onError(FFMPEG_NOMEDIA, THREAD_CHILD);
        return;
    }

    //告诉Java准备好了可以播放
    helper->onPrepare(THREAD_CHILD);

}

void *start_t(void *args) {
    EnjoyPlayer *player = static_cast<EnjoyPlayer *>(args);
    player->_start();
    return 0;
}

void EnjoyPlayer::start() {

    //1.读取媒体源的数据
    //2.根据数据类型放入Audio/VideoChannel的队列中
    isPlaying = 1;
    if(videoChannel){
        videoChannel->play();
    }
    pthread_create(&startTask, 0, start_t, this);
}

void EnjoyPlayer::_start() {
    int ret;
    while (isPlaying) {
        // 不断的读取
        AVPacket *avPacket = av_packet_alloc();
        ret = av_read_frame(avFormatContext, avPacket);
        // 读取成功
        if (ret == 0) {
            if(videoChannel && avPacket->stream_index == videoChannel->channelId){
                videoChannel->pkt_queue.enQueue(avPacket);
            }
        } else if (ret == AVERROR_EOF) {
            //读取完毕，但是不一定播放完毕，本地视频会出现
            if(videoChannel->pkt_queue.empty() && videoChannel->frame_queue.empty()){
                //播放完毕
                break;
            }
        } else {
            break;
        }
    }
    isPlaying = 0;
    videoChannel->stop();
}

void EnjoyPlayer::setWindow(ANativeWindow *window) {
    // 持久获得surface C++ 中ANativeWindow需要创建全局引用，类似javaCallHelper
    this->window = window;
    if(videoChannel){
        videoChannel->setWindow(window);
    }
}



