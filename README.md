# zcwplayer

一款开源播放器，学习和实践



##视音频播放器流程概况

![ffmpeg解封装解码流程API概况](ffmpeg解封装解码流程API概况.jpg)

##视音频播放器流程概况

## ![视音频播放器流程概况](视音频播放器流程概况.png)



## 代码逻辑功能：

1. EnjoyPlayer.cpp 控制主要逻辑实现

EnjoyPlayer 初始化av_formate_init
setDataSource
prepare
start
    - VideoChannel/AudioChannel::play
        - VideoChannel/AudioChannel::decode
        - VideoChannel/AudioChannel::_play
    - _start

2. VideoChannel.cpp 控制视频逻辑处理

pthread,video_decode,t:decode
    - avcodec_send_packet
    - avcodec_receive_frame
    - 插入frame_queue 队列
    
pthread,video_play_t:_play
    - 格式转换sws_scale: sws_getContext 初始化
    - 准备格式转换接受数据申请空间：av_image_alloc
    - 按照行进行渲染格式转换：sws_scale 
    - 【音视频同步处理】
    - 读取 frame_queue 队列，出队列
    - 渲染数据：_onDraw
        - ANativeWindow_Buffer ----对应SurfaceView
        - ANativeWindow:memcpy 
stop

3. AudioChannel.cpp



## 涉及到的点：

1. 开启线程
prepare 1个线程
队列存放AVPacket 1个线程
音频播放和解码 2个线程
视频播放和解码 2个线程
2. 导入ffmpeg头文件，需要 c的方式 extern C
3. 将视频数据刷到buffer 的时候我们的数据是 RGBA * 4 
但是ffmpeg 是 8位，所以我们需要字节对齐。 需要 除以 64 得到整数对齐
4. 生产者消费队列模型，编解码到播放需要用到线程交互模型和队列操作，数据加锁。
5. 开启权限 WRITE_EXTERNAL_STORAGE