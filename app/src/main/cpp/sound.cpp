//
// Created by Light on 2020/3/24.
//

#include <jni.h>
#include <android/log.h>
#include "inc/fmod.hpp"
#include <unistd.h>

#define LOGV(...)   __android_log_print((int)ANDROID_LOG_INFO, "FMOD", __VA_ARGS__)
using namespace FMOD;

#define MODE_NORMAL 0
#define MODE_LUOLI 1
#define MODE_DASHU 2
#define MODE_JINGSONG 3
#define MODE_GAOGUAI 4
#define MODE_KONGLING 5

extern "C"
JNIEXPORT void JNICALL
Java_com_example_bianshengqi_util_EffectUtils_fix(JNIEnv *env, jobject clazz, jstring path_jstr,
jint type) {
    LOGV("EffectUtils_Fix");
    //声音引擎
    System *system;
    //声音
    Sound *sound;
    //数字处理(音效)
    DSP *dsp;
    //正在播放
    bool playing = true;
    //音乐轨道
    Channel *channel;
    //播放速度
    float frequency = 0;
    //音频地址
    const char* path_cstr = env->GetStringUTFChars(path_jstr, NULL);

    System_Create(&system);

    //初始化
    system->init(32, FMOD_INIT_NORMAL, NULL);
    try
    {
        system->createSound(path_cstr, FMOD_DEFAULT, NULL, &sound);
        switch (type) {
            case MODE_NORMAL:
                system->playSound(sound, 0, false, &channel);
                break;
            case MODE_LUOLI:
                //提升或者降低音调的一种特效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 1.8);
                //添加进倒channel,添加进轨道
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case MODE_DASHU:
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case MODE_JINGSONG:
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 2);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case MODE_GAOGUAI:
                //提高说话的速度
                system->playSound(sound, 0, false, &channel);
                channel->getFrequency(&frequency);
                frequency = frequency * 2;
                channel->setFrequency(frequency);
                break;
            case MODE_KONGLING:
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
        }
    }
    catch (...)
    {
        LOGV("发生异常");
        return;
    }
    system->update();
    //单位是微秒
    //每秒钟判断下是否正在播放
    while (playing) {
        channel->isPlaying(&playing);
        usleep(1000);
    }

    goto end;

    end: env->ReleaseStringUTFChars(path_jstr, path_cstr);
    sound->release();
    system->close();
    system->release();
}