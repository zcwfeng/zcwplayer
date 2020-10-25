//
// Created by 张传伟 on 2020/10/23.
//

#ifndef ZCWPLAYER_JAVACALLHELPER_H
#define ZCWPLAYER_JAVACALLHELPER_H
#include <jni.h>

//标记线程 因为子线程需要attach
#define THREAD_MAIN 1
#define THREAD_CHILD 2

//错误代码
//打不开视频
#define FFMPEG_CAN_NOT_OPEN_URL 1
//找不到流媒体
#define FFMPEG_CAN_NOT_FIND_STREAMS 2
//找不到解码器
#define FFMPEG_FIND_DECODER_FAIL 3
//无法根据解码器创建上下文
#define FFMPEG_ALLOC_CODEC_CONTEXT_FAIL 4
//根据流信息 配置上下文参数失败
#define FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL 6
//打开解码器失败
#define FFMPEG_OPEN_DECODER_FAIL 7
//没有音视频
#define FFMPEG_NOMEDIA 8
class JavaCallHelper {
public:
    JavaCallHelper(JavaVM *_javaVm, JNIEnv *_env, jobject &_jobj);
    ~JavaCallHelper();

    void onError(int code,int thread = THREAD_MAIN);
    void onPrepare(int thread = THREAD_MAIN);
    void onProgress(int progress,int thread = THREAD_MAIN);

public:
    JavaVM *javaVM;
    JNIEnv *env;
    jobject jobj;
    jmethodID jmid_error;
    jmethodID jmid_prepare;
    jmethodID jmid_progress;
};


#endif //ZCWPLAYER_JAVACALLHELPER_H
