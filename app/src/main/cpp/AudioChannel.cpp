//
// Created by 张传伟 on 2020/10/25.
//

#include "AudioChannel.h"
#include "Log.h"


void *audioDecode_t(void *args) {
    AudioChannel *audioChannel = static_cast<AudioChannel *>(args);
    audioChannel->decode();
    return 0;

}

void *audioPlay_t(void *args) {
    AudioChannel *audioChannel = static_cast<AudioChannel *>(args);
    audioChannel->_play();
    return 0;

}

AudioChannel::~AudioChannel() {
    free(buffer);
    buffer = 0;
}

AudioChannel::AudioChannel(int channelId,
                           JavaCallHelper *helper,
                           AVCodecContext *avCodecContext,
                           const AVRational &timeBase)
        : BaseChannel(channelId, helper, avCodecContext, timeBase) {
    // 2 声道
    out_channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
    // 每个样本大小
    out_sampleSize = av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
    // 采样率
    int out_samleRate = 44100;
    bufferCount = out_channels * out_samleRate * out_sampleSize;
    buffer = static_cast<uint8_t *>(malloc(bufferCount));

}

void AudioChannel::play() {
    swrContext = swr_alloc_set_opts(0, AV_CH_LAYOUT_STEREO,
                                    AV_SAMPLE_FMT_S16, 44100,
                                    avCodecContext->channel_layout,
                                    avCodecContext->sample_fmt,
                                    avCodecContext->sample_rate,
                                    0, 0);
    swr_init(swrContext);
    isPlaying = 1;
    setEnable(1);
    //解码
    pthread_create(&audioDecodeTask, 0, audioDecode_t, this);

    //播放
    pthread_create(&audioPlayTask, 0, audioPlay_t, this);

}

void AudioChannel::stop() {
    isPlaying = 0;
    helper = 0;
    pthread_join(audioDecodeTask, 0);
    pthread_join(audioPlayTask, 0);
    _releaseOpenSL();
    if (swrContext) {
        swr_free(&swrContext);
        swrContext = 0;
    }
}

void AudioChannel::decode() {
    AVPacket *packet = 0;
    while (isPlaying) {
        // 阻塞
        //1. 能够渠道数据
        //2.停止播放。
        int ret = pkt_queue.deQueue(packet);
        if (!isPlaying) {
            break;
        }
        if (!ret) {
            continue;
        }
        // 向解码器发送数据
        avcodec_send_packet(avCodecContext, packet);
        releaseAvPacket(packet);//释放掉
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
}

void bqPlayerCallback(SLAndroidSimpleBufferQueueItf queue, void *pContext) {
    AudioChannel *audioChannel = static_cast<AudioChannel *>(pContext);
    int dataSize = audioChannel->_getPCMData();
    if (dataSize > 0) {
        (*queue)->Enqueue(queue, audioChannel->buffer, dataSize);
    }
}

void AudioChannel::_play() {
    /**
     *
     * 1.创建引擎
     */

    // 创建引擎engineObject
    SLresult result;
    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    if (SL_RESULT_SUCCESS != result) {
        return;
    }
    // 初始化
    result = (*engineObject)->Realize(engineObject,
                                      SL_BOOLEAN_FALSE);
    if (SL_RESULT_SUCCESS != result) {
        return;
    }
    // 获取引擎接口engineInterface
    result = (*engineObject)->GetInterface(engineObject,
                                           SL_IID_ENGINE, &engineInterface);
    if (SL_RESULT_SUCCESS != result) {
        return;
    }

    /**
     * 2 创建混音器
     */
    //通过引擎接口创建混音器
    result = (*engineInterface)->CreateOutputMix(engineInterface, &outputMixObject, 0, 0, 0);
    if (SL_RESULT_SUCCESS != result) {
        return;
    }
    // 初始化混音器outputMixObject
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    if (SL_RESULT_SUCCESS != result) {
        return;
    }

    /**
     * 3 创建播放器
     */

    //创建buffer缓冲类型的队列作为数据定位器(获取播放数据) 2个缓冲区
    SLDataLocator_AndroidSimpleBufferQueue android_queue =
            {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    //pcm数据格式: pcm、声道数、采样率、采样位、容器大小、通道掩码(双声道)、字节序(小端)
    SLDataFormat_PCM pcm = {SL_DATAFORMAT_PCM, 2, SL_SAMPLINGRATE_44_1,
                            SL_PCMSAMPLEFORMAT_FIXED_16,
                            SL_PCMSAMPLEFORMAT_FIXED_16,
                            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
                            SL_BYTEORDER_LITTLEENDIAN};

    //数据源 （数据获取器+格式）  从哪里获得播放数据
    SLDataSource slDataSource = {&android_queue, &pcm};

    //设置混音器
    SLDataLocator_OutputMix outputMix =
            {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&outputMix, NULL};
    //需要的接口
    const SLInterfaceID ids[1] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[1] = {SL_BOOLEAN_TRUE};
    //创建播放器
    (*engineInterface)->CreateAudioPlayer(engineInterface, &bqPlayerObject, &slDataSource,
                                          &audioSnk, 1,
                                          ids, req);
    //初始化播放器
    (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);


    /**
     * 4 播放
     */

    //获得播放数据队列操作接口
    (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
                                    &bqPlayerBufferQueue);
    //设置回调(启动播放器后执行回调来获取数据并播放)
    (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, this);

    //获取播放状态接口

    (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerInterface);
    // 设置播放状态
    (*bqPlayerInterface)->SetPlayState(bqPlayerInterface, SL_PLAYSTATE_PLAYING);
    //TODO 容易忘记
    //需要手动调用一次播放回调
    bqPlayerCallback(bqPlayerBufferQueue, this);


}

/**
 * 获取PCM数据，一旦获取到返回
 * @return
 */
int AudioChannel::_getPCMData() {
    int dataSize;
    AVFrame *frame = 0;
    // 因为isPlaying可能是否发生变化的，所以判断!isPlaying 同理ret也可能，因为我们是多线程
    while (isPlaying) {
        int ret = frame_queue.deQueue(frame);
        if (!isPlaying) {
            break;
        }
        if (!ret) {
            continue;
        }
        //转换，nb_samples 一个声道的样本数
        int nb = swr_convert(swrContext, &buffer, bufferCount,
                             (const uint8_t **) (frame->data), frame->nb_samples);
        dataSize = nb * out_channels * out_sampleSize;

        // 播放这段音频的时间
//        clock = frame->pts * av_q2intfloat(time_base);
        clock = frame->pts * av_q2d(time_base);
        // 假设：time_base {1,20} <-> pst = 1/20 为单位 <->1 秒钟分成20份

        break;
    }


    return dataSize;
}

void AudioChannel::_releaseOpenSL() {
    LOGE("停止播放");
    //设置停止状态
    if (bqPlayerInterface) {
        (*bqPlayerInterface)->SetPlayState(bqPlayerInterface, SL_PLAYSTATE_STOPPED);
        bqPlayerInterface = 0;
    }
    //销毁播放器
    if (bqPlayerObject) {
        (*bqPlayerObject)->Destroy(bqPlayerObject);
        bqPlayerObject = 0;
        bqPlayerBufferQueue = 0;
    }
    //销毁混音器
    if (outputMixObject) {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = 0;
    }
    //销毁引擎
    if (engineObject) {
        (*engineObject)->Destroy(engineObject);
        engineObject = 0;
        engineInterface = 0;
    }
}
