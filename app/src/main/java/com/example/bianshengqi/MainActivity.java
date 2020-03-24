package com.example.bianshengqi;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.bianshengqi.util.EffectUtils;

import org.fmod.FMOD;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    Button mBtnNormal;
    Button mBtnLuoli;
    Button mBtnDashu;
    Button mBtnJingSong;
    Button mBtnGaoGuai;
    Button mBtnKongLing;
    private int type;
    private ExecutorService fixedThreadPool;
    private PlayerThread playerThread;
    private String path = "file:///android_asset/hensen.mp3";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }

    protected void init(){
        mBtnNormal = findViewById(R.id.btn_normal);
        mBtnLuoli = findViewById(R.id.btn_luoli);
        mBtnDashu = findViewById(R.id.btn_dashu);
        mBtnJingSong = findViewById(R.id.btn_jingsong);
        mBtnGaoGuai = findViewById(R.id.btn_gaoguai);
        mBtnKongLing = findViewById(R.id.btn_kongling);

        mBtnNormal.setOnClickListener(this);
        mBtnLuoli.setOnClickListener(this);
        mBtnDashu.setOnClickListener(this);
        mBtnJingSong.setOnClickListener(this);
        mBtnGaoGuai.setOnClickListener(this);
        mBtnKongLing.setOnClickListener(this);

        fixedThreadPool = Executors.newFixedThreadPool(1);
        FMOD.init(this);
    }

    class PlayerThread implements Runnable {

        @Override
        public void run() {
            EffectUtils.fix(path, type);
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_normal:{
                type = EffectUtils.MODE_NORMAL;
            }
            break;
            case R.id.btn_luoli:{
                type = EffectUtils.MODE_LUOLI;
            }
            break;
            case R.id.btn_dashu:{
                type = EffectUtils.MODE_DASHU;
            }
            break;
            case R.id.btn_jingsong:{
                type = EffectUtils.MODE_JINGSONG;
            }
            break;
            case R.id.btn_gaoguai:{
                type = EffectUtils.MODE_GAOGUAI;
            }
            break;
            case R.id.btn_kongling:{
                type = EffectUtils.MODE_KONGLING;
            }
            break;
            default:
                break;
        }

        playerThread = new PlayerThread();
        fixedThreadPool.execute(playerThread);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }
}
