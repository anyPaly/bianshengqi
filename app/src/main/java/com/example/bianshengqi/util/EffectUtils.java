package com.example.bianshengqi.util;

public class EffectUtils {

    public static final int MODE_NORMAL = 0;
    public static final int MODE_LUOLI = 1;
    public static final int MODE_DASHU = 2;
    public static final int MODE_JINGSONG = 3;
    public static final int MODE_GAOGUAI = 4;
    public static final int MODE_KONGLING = 5;


    public native static void fix(String path, int type);

    static {
        System.loadLibrary("fmodL");
        System.loadLibrary("fmod");
        System.loadLibrary("sound");
    }
}
