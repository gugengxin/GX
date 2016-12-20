package com.gxengine.gx;

import android.content.Intent;

import java.util.UUID;

/**
 * Created by GuGengxin on 2016/12/10.
 */

public class GAndroidC {
    public static float appGetDefaultWindowScale() {
        return GApplication.shared().getResources().getDisplayMetrics().density;
    }
    public static String appGetCacheDir() {
        return GApplication.shared().getCacheDir().getAbsolutePath();
    }
    public static String appGetPackageCodePath() {
        return GApplication.shared().getPackageCodePath();
    }

    public static void appStartActivity() {
        Intent intent=new Intent(GApplication.shared(),GActivity.class);
        GApplication.shared().startActivity(intent);
    }

    public static byte[] UUIDCreate() {
        byte[] res=new byte[16];

        UUID uuid=UUID.randomUUID();

        long v=uuid.getMostSignificantBits();
        res[0]=(byte)(v&0xFF);
        res[1]=(byte)((v>>>1)&0xFF);
        res[2]=(byte)((v>>>2)&0xFF);
        res[3]=(byte)((v>>>3)&0xFF);
        res[4]=(byte)((v>>>4)&0xFF);
        res[5]=(byte)((v>>>5)&0xFF);
        res[6]=(byte)((v>>>6)&0xFF);
        res[7]=(byte)((v>>>7)&0xFF);
        v=uuid.getLeastSignificantBits();
        res[8+0]=(byte)((v)&0xFF);
        res[8+1]=(byte)((v>>>1)&0xFF);
        res[8+2]=(byte)((v>>>2)&0xFF);
        res[8+3]=(byte)((v>>>3)&0xFF);
        res[8+4]=(byte)((v>>>4)&0xFF);
        res[8+5]=(byte)((v>>>5)&0xFF);
        res[8+6]=(byte)((v>>>6)&0xFF);
        res[8+7]=(byte)((v>>>7)&0xFF);
        return res;
    }

}
