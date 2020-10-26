package top.zcwfeng.zcwplayer;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.SurfaceHolder;

import androidx.appcompat.app.AppCompatActivity;

import top.zcwfeng.zcwplayer.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements SurfaceHolder.Callback {

    EnjoyPlayer player;
    ActivityMainBinding viewBinding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        viewBinding = ActivityMainBinding.inflate(LayoutInflater.from(this));
        setContentView(viewBinding.getRoot());
        viewBinding.surfaceView.getHolder().addCallback(this);
        player = new EnjoyPlayer();
//        player.setDataSource("/sdcard/play1.mp4");
//        player.setDataSource("http://ivi.bupt.edu.cn/hls/cctv8hd.m3u8");
//        player.setDataSource("http://devimages.apple.com.edgekey.net/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8");
        player.setDataSource("http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8");
        player.setOnPrepareListener(new EnjoyPlayer.OnPrepareListener() {
            @Override
            public void onPrepare() {
                player.start();
                Log.e("FFMPEG-JAVA", "执行onPrepare()-EnjoyPlayer.OnPrepareListener()");

            }
        });
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        player.setSurface(holder.getSurface());
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    @Override
    protected void onResume() {
        super.onResume();
        player.prepare();
        Log.e("FFMPEG-JAVA", "执行player.prepare()-onResume()");

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        player.stop();
        Log.e("FFMPEG-JAVA", "执行player.stop()-onDestroy()");
    }
}


