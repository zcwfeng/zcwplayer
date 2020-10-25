package top.zcwfeng.zcwplayer;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Surface;
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
        player.setDataSource("/sdcard/play1.mp4");
//        player.setDataSource("http://91.9p9.xyz/ev.php?VID=7201Nz2yvV2QBsfERGkxn0PtHCjt5P3vvloEehVK07PbQtfZ");
//        player.setDataSource("http://tx.hls.huya.com/huyalive/89530005-89530005-384528443485716480-21619896-10057-A-0-1.m3u8");
        player.setOnPrepareListener(new EnjoyPlayer.OnPrepareListener() {
            @Override
            public void onPrepare() {
                player.start();

            }
        });
        player.prepare();
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Surface surface = holder.getSurface();
        player.setSurface(surface);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}


