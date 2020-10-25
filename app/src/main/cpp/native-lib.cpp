#include <jni.h>
#include <string>
#include "Log.h"
#include "EnjoyPlayer.h"

//结构提，其中JNIEnv和线程绑定，当c/C++子线程调用主线程的时候需要用到
JavaVM *javaVm = 0;
//    TODO JNI adapt
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){
    javaVm = vm;
    return JNI_VERSION_1_4;
}


//jobject 就是EnjoyPlayer的一个实例
extern "C"
JNIEXPORT jlong JNICALL
Java_top_zcwfeng_zcwplayer_EnjoyPlayer_nativeInit(JNIEnv *env, jobject thiz) {
    EnjoyPlayer *player = new EnjoyPlayer(new JavaCallHelper(javaVm,env,thiz));
    return (jlong) (player);
}

extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_zcwplayer_EnjoyPlayer_setDataSource(JNIEnv *env, jobject thiz, jlong native_handl,
                                                     jstring path_) {
    // 深拷贝pathtr
    const char *path = env->GetStringUTFChars(path_, 0);
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(native_handl);
    player->setDataSource(path);
    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_zcwplayer_EnjoyPlayer_prepare(JNIEnv *env, jobject thiz, jlong native_handle) {
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(native_handle);
    player->prepare();
}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_zcwplayer_EnjoyPlayer_start(JNIEnv *env, jobject thiz, jlong native_handle) {
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(native_handle);
    player->start();
}

extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_zcwplayer_EnjoyPlayer_setSurface(JNIEnv *env,
        jobject thiz,
        jlong native_handle,
        jobject surface) {

    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(native_handle);
    ANativeWindow *window = ANativeWindow_fromSurface(env,surface);
    player->setWindow(window);

}