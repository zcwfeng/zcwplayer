//
// Created by 张传伟 on 2020/10/23.
//

#ifndef ZCWPLAYER_SAFE_QUEUE_H
#define ZCWPLAYER_SAFE_QUEUE_H

#include <pthread.h>
#include <queue>

using namespace std;
template<typename T>

class SafeQueue {
    typedef void (*ReleaseHandle)(T &);

    typedef void (*SyncHandle)(queue<T> &);
public:
    SafeQueue() {
        pthread_mutex_init(&mutex, 0);
        pthread_cond_init(&cond, 0);
    }

    virtual ~SafeQueue() {
        pthread_cond_destroy(&cond);
        pthread_mutex_destroy(&mutex);
    }

    void enQueue(T new_value) {
        pthread_mutex_lock(&mutex);
        if (mEnable) {
            q.push(new_value);
            pthread_cond_signal(&cond);
        } else {
            releaseHandle(new_value);
        }
        pthread_mutex_unlock(&mutex);

    }


    int deQueue(T &value) {
        int ret = 0;
        pthread_mutex_lock(&mutex);
        //在多核处理器下 由于竞争可能虚假唤醒 包括jdk也说明了
        while (mEnable && q.empty()) {
            pthread_cond_wait(&cond, &mutex);
        }
        if (!q.empty()) {
            value = q.front();
            q.pop();
            ret = 1;
        }
        pthread_mutex_unlock(&mutex);

        return ret;
    }

    void setEnable(bool enable) {
        pthread_mutex_lock(&mutex);
        this->mEnable = enable;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

    }

    int empty() {
        return q.empty();
    }

    int size() {
        return q.size();
    }

    void clear() {
        pthread_mutex_lock(&mutex);
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            T value = q.front();
            releaseHandle(value);
            q.pop();
        }
        pthread_mutex_unlock(&mutex);
    }

    void sync() {
        pthread_mutex_lock(&mutex);
        syncHandle(q);
        pthread_mutex_unlock(&mutex);
    }

    void setReleaseHandle(ReleaseHandle r) {
        releaseHandle = r;
    }

    void setSyncHandle(SyncHandle s) {
        syncHandle = s;
    }

private:
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    queue <T> q;
    bool mEnable;
    ReleaseHandle releaseHandle;
    SyncHandle syncHandle;
};

#endif //ZCWPLAYER_SAFE_QUEUE_H
