package top.zcwfeng.zcwplayer;

import android.view.Surface;

public class EnjoyPlayer {
    static {
        System.loadLibrary("native-lib");
    }

    public long nativeHandle;

    public EnjoyPlayer() {
        this.nativeHandle = nativeInit();
    }

    public void prepare() {
        prepare(nativeHandle);
    }

    public void setDataSource(String path) {
        setDataSource(nativeHandle, path);
    }

    public void setSurface(Surface surface) {
        setSurface(nativeHandle, surface);
    }

    public void start() {
        start(nativeHandle);
    }

    public void stop() {

    }

    public void pause() {

    }


    private native long nativeInit();

    private native void setDataSource(long nativeHandl, String path);

    private native void prepare(long nativeHandle);

    private native void start(long nativeHandle);

    private native void setSurface(long nativeHandle, Surface surface);


    //-------------C++ 给Java 的各种回调，类似MediaPlayer.OnErrorListener等--

    private void onError(int code) {
        if (onErrorListener != null) {
            onErrorListener.onError(code);
        }
    }


    private void onProgress(int progress) {
        if (onProgressListener != null) {
            onProgressListener.onProgress(progress);
        }
    }

    private void onPrepare() {
        if (onPrepareListener != null) {
            onPrepareListener.onPrepare();
        }
    }

    public interface OnErrorListener {
        void onError(int err);
    }

    public interface OnProgressListener {
        void onProgress(int progress);
    }

    public interface OnPrepareListener {
        void onPrepare();
    }

    private OnErrorListener onErrorListener;
    private OnProgressListener onProgressListener;
    private OnPrepareListener onPrepareListener;

    public void setOnErrorListener(OnErrorListener onErrorListener) {
        this.onErrorListener = onErrorListener;
    }

    public void setOnProgressListener(OnProgressListener onProgressListener) {
        this.onProgressListener = onProgressListener;
    }

    public void setOnPrepareListener(OnPrepareListener onPrepareListener) {
        this.onPrepareListener = onPrepareListener;
    }


}
