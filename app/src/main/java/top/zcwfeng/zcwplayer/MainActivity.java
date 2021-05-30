package top.zcwfeng.zcwplayer;

import android.Manifest;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.SurfaceHolder;

import androidx.appcompat.app.AppCompatActivity;

import pub.devrel.easypermissions.EasyPermissions;
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
//        player.setDataSource("/sdcard/b.mp4");
        player.setDataSource("rtmp://58.200.131.2:1935/livetv/hunantv");
//        player.setDataSource("http://devimages.apple.com.edgekey.net/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8");
//        player.setDataSource("http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8");
//        player.setDataSource("https://xy101x21x112x215xy.mcdn.bilivideo.cn:486/live-bvc/976447/live_23148330_2034105_2500.flv?expires=1622353168&len=0&oi=3733008533&pt=web&qn=0&trid=10003a5c3a2921e74c21a6feed1faae157fd&sigparams=cdn,expires,len,oi,pt,qn,trid&cdn=cn-live-mcdn&sign=c640b273bf753a18a8b174a00e7deb3d&sid=1001429&sk=59b4112a8c653bb");
        player.setOnPrepareListener(new EnjoyPlayer.OnPrepareListener() {
            @Override
            public void onPrepare() {
                player.start();
                Log.e("FFMPEG-JAVA", "执行onPrepare()-EnjoyPlayer.OnPrepareListener()");

            }
        });

        String[] perms = {Manifest.permission.CALL_PHONE
                , Manifest.permission.WRITE_EXTERNAL_STORAGE
                , Manifest.permission.READ_EXTERNAL_STORAGE};

        if (EasyPermissions.hasPermissions(this, perms)) {
            // Already have permission, do the thing
            // ...
        } else {
            // Do not have permissions, request them now
            EasyPermissions.requestPermissions(this, "因为功能需要使用相关权限，请允许",
                    100, perms);
        }
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        EasyPermissions.onRequestPermissionsResult(requestCode, permissions, grantResults, this);
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


