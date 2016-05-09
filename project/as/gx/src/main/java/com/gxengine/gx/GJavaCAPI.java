package com.gxengine.gx;

import java.util.UUID;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.ContextWrapper;
import android.service.dreams.DreamService;
import android.util.*;

import com.gxengine.GX;

public class GJavaCAPI {
	public static float appGetDefaultWindowScale(Activity activity) {
		DisplayMetrics dm=new DisplayMetrics();
		activity.getWindowManager().getDefaultDisplay().getMetrics(dm);
		return dm.density;
	}
	@SuppressLint("NewApi")
	public static float appGetDefaultWindowScale(DreamService dream) {
		DisplayMetrics dm=new DisplayMetrics();
		dream.getWindowManager().getDefaultDisplay().getMetrics(dm);
		return dm.density; 
	}
	public static String appGetCacheDir(ContextWrapper cw) {
		return cw.getCacheDir().getAbsolutePath();
	}
	public static String appGetPackageCodePath(ContextWrapper cw) {
		return cw.getPackageCodePath();
	}
	public static void appTerminate(Activity activity) {
		activity.finish();
	}
	public static byte[] UUIDCreate() {
		byte[] res=new byte[16];
		
		UUID uuid=UUID.randomUUID();
		
		long v=uuid.getMostSignificantBits();
		res[0]=(byte)(v>>>0);
		res[1]=(byte)(v>>>1);
		res[2]=(byte)(v>>>2);
		res[3]=(byte)(v>>>3);
		res[4]=(byte)(v>>>4);
		res[5]=(byte)(v>>>5);
		res[6]=(byte)(v>>>6);
		res[7]=(byte)(v>>>7);
		v=uuid.getLeastSignificantBits();
		res[8+0]=(byte)(v>>>0);
		res[8+1]=(byte)(v>>>1);
		res[8+2]=(byte)(v>>>2);
		res[8+3]=(byte)(v>>>3);
		res[8+4]=(byte)(v>>>4);
		res[8+5]=(byte)(v>>>5);
		res[8+6]=(byte)(v>>>6);
		res[8+7]=(byte)(v>>>7);
		return res;
	}
	
}
