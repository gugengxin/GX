package com.gxengine.gx;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GOpenGLView extends SurfaceView implements SurfaceHolder.Callback {

	public GOpenGLView(Context context) {
		super(context);
		init();
	}

	public GOpenGLView(Context context, AttributeSet attrs) {
		super(context, attrs);
		init();
	}

	public GOpenGLView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		init();
	}
	
	protected void init() {
		this.getHolder().addCallback(this);
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Log.d("GAOpenGLView", "surfaceCreated");
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
		Log.d("GAOpenGLView", String.format("surfaceChanged %d %d %d",format,width,height));
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.d("GAOpenGLView", "surfaceDestroyed");
	}

}
