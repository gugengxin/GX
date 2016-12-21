package com.gxengine.gx;

import java.lang.ref.WeakReference;
import android.annotation.SuppressLint;
import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GWindow extends SurfaceView implements SurfaceHolder.Callback {
	
	public interface Delegate {
		public void onWindowCreated(GWindow win, Surface surface);
		public void onWindowChanged(GWindow win, Surface surface, int width, int height);
		public void onWindowDestroyed(GWindow win, Surface surface);
		public void onWindowTouchEvent(GWindow win, MotionEvent event);
	}

	public GWindow(Context context, Delegate dge) {
		super(context);
		setDelegate(dge);
		this.getHolder().addCallback(this);
	}

	public Delegate getDelegate() {
		return _delegate.get();
	}

	public void setDelegate(Delegate dge) {
		_delegate=new WeakReference<Delegate>(dge);
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		getDelegate().onWindowCreated(this, holder.getSurface());
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
		getDelegate().onWindowChanged(this, holder.getSurface(), width, height);
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		getDelegate().onWindowDestroyed(this, holder.getSurface());
	}

	@SuppressLint("ClickableViewAccessibility")
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		getDelegate().onWindowTouchEvent(this, event);
		return true;
	}

	private WeakReference<Delegate> _delegate;
}
