package com.mjpeg;

import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class MjpegView extends SurfaceView implements SurfaceHolder.Callback {
        public final static int POSITION_UPPER_LEFT = 9;
        public final static int POSITION_UPPER_RIGHT = 3;
        public final static int POSITION_LOWER_LEFT = 12;
        public final static int POSITION_LOWER_RIGHT = 6;

        public final static int SIZE_STANDARD = 1;
        public final static int SIZE_BEST_FIT = 4;
        public final static int SIZE_FULLSCREEN = 8;

        private int X_touch = 0xFFFF;
        private int Y_touch = 0xFFFF;
        
        private MjpegViewThread thread = null;
        private MjpegInputStream mIn = null;
        private boolean showFps = false;
        private boolean mRun = false;
        private boolean surfaceDone = false;
        private Paint overlayPaint;
        private int overlayTextColor;
        private int overlayBackgroundColor;
        private int ovlPos;
        private int dispWidth;
        private int dispHeight;
        private int displayMode;
        private boolean resume = false;
        private String display_text ="";
        private int display_text_x = 0;
        private int display_text_y = 0;
        private Context context;
        private Timer t_touch = new Timer();
        
        
		public interface Position
		{
			void done(int x,int y);
		}
		public Position position = null;

        public class MjpegViewThread extends Thread {
                private SurfaceHolder mSurfaceHolder;
                private int frameCounter = 0;
                private long start;
                private Bitmap ovl;

                public MjpegViewThread(SurfaceHolder surfaceHolder, Context context) {
                        mSurfaceHolder = surfaceHolder;
                }

                private Rect destRect(int bmw, int bmh) {
                        int tempx;
                        int tempy;
                        if (displayMode == MjpegView.SIZE_STANDARD) {
                                tempx = (dispWidth / 2) - (bmw / 2);
                                tempy = (dispHeight / 2) - (bmh / 2);
                                return new Rect(tempx, tempy, bmw + tempx, bmh + tempy);
                        }
                        if (displayMode == MjpegView.SIZE_BEST_FIT) {
                                float bmasp = (float) bmw / (float) bmh;
                                bmw = dispWidth;
                                bmh = (int) (dispWidth / bmasp);
                                if (bmh > dispHeight) {
                                        bmh = dispHeight;
                                        bmw = (int) (dispHeight * bmasp);
                                }
                                tempx = (dispWidth / 2) - (bmw / 2);
                                tempy = (dispHeight / 2) - (bmh / 2);
                                return new Rect(tempx, tempy, bmw + tempx, bmh + tempy);
                        }
                        if (displayMode == MjpegView.SIZE_FULLSCREEN)
                                return new Rect(0, 0, dispWidth, dispHeight);
                        return null;
                }

                public void setSurfaceSize(int width, int height) {
                        synchronized (mSurfaceHolder) {
                                dispWidth = width;
                                dispHeight = height;
                        }
                }

                private Bitmap makeFpsOverlay(Paint p, Bitmap obm ,String fps_text) 
                {
                        Rect b = new Rect();
                        p.getTextBounds(fps_text, 0, fps_text.length(), b);
                        int bwidth = b.width() + 2;
                        int bheight = b.height() + 2;
                        
                        
                        Canvas c = new Canvas(obm);
                        p.setColor(overlayBackgroundColor);
                        Rect rect = new Rect();
                        rect.set(dispWidth - bwidth, 0, dispWidth, bheight);
                        c.drawRect(rect, p);
                        p.setColor( overlayTextColor );
                        c.drawText(fps_text, dispWidth - bwidth, (bheight / 2) - ((p.ascent() + p.descent()) / 2) + 1, p);
                        
                        return obm;
                }
                
                private Bitmap makeOverlay(Bitmap bm,Paint p,int x, int y, String text) 
                {
                	Canvas c = new Canvas(bm);
                    p.setColor( overlayTextColor );
                    c.drawText(text,x,y, p);
                    return bm;
                }

                public void run() 
                {
                    start = System.currentTimeMillis();
                    PorterDuffXfermode mode = new PorterDuffXfermode(
                                    PorterDuff.Mode.DST_OVER);
                    Bitmap bm = null;
                    int width;
                    int height;
                    Rect destRect;
                    Canvas c = null;
                    Paint p = new Paint();
                    String fps = "";
                    while (mRun) 
                    {
                        if (surfaceDone) 
                        {
                            try 
                            {
                                c = mSurfaceHolder.lockCanvas();
                                synchronized (mSurfaceHolder) 
                                {
                                    try 
                                    {
                                    	if(mIn != null)
                                    	{
                                            bm = mIn.readMjpegFrame();
                                            destRect = destRect(bm.getWidth(),
                                                            bm.getHeight());
                                            if (c != null)
                                            {
                                                c.drawColor(Color.BLACK);
                                                c.drawBitmap(bm, null, destRect, p);
                                                
                                                if((X_touch != 0xFFFF) && (Y_touch != 0xFFFF))
                                                {
                                                    p.setStyle(Paint.Style.STROKE);
                                                	p.setColor(Color.RED);
                                                    p.setStrokeWidth(4);
                                                	c.drawRect(X_touch - 40, Y_touch - 40, X_touch + 40, Y_touch + 40, p);
                                                	p.setColor(Color.BLACK);
                                                }
                                                
                                                if (showFps) 
                                                {
                                                    p.setXfermode(mode);
                                                    if (ovl != null) 
                                                    {
                                                        height = ((ovlPos & 1) == 1) ? destRect.top
                                                                        : destRect.bottom
                                                                                        - ovl.getHeight();
                                                        width = ((ovlPos & 8) == 8) ? destRect.left
                                                                        : destRect.right
                                                                                        - ovl.getWidth();
                                                        c.drawBitmap(ovl, width, height, null);
                                                    }
                                                    p.setXfermode(null);
                                                    frameCounter++;
                                                    if ((System.currentTimeMillis() - start) >= 1000) 
                                                    {
                                                        fps = String.valueOf(frameCounter)
                                                                        + "fps";
                                                        frameCounter = 0;
                                                        start = System.currentTimeMillis();

                                                        Bitmap obm = Bitmap.createBitmap(dispWidth, dispHeight, Bitmap.Config.ARGB_8888);
                                                        ovl = makeFpsOverlay(overlayPaint, obm, fps);
                                                        if(display_text != "")
                                                        {
                                                        	ovl = makeOverlay(ovl, overlayPaint ,display_text_x, display_text_y, display_text); 
                                                        }
                                                    }
                                                }
                                            }
                                    	} 
                                    }
                                    catch (IOException e) 
                                    {
                                    }
                                }
                            }
                            finally 
                            {
                            	if (c != null)
                            	{
                            		mSurfaceHolder.unlockCanvasAndPost(c);
                            	}
                            }
                        }
                    }
                }
        }

        private void init(Context context) {

                this.context = context;
                SurfaceHolder holder = getHolder();
                holder.addCallback(this);
                thread = new MjpegViewThread(holder, context);
                setFocusable(true);
                if (!resume) {
                        resume = true;
                        overlayPaint = new Paint();
                        overlayPaint.setTextAlign(Paint.Align.LEFT);
                        overlayPaint.setTextSize(12);
                        overlayPaint.setTypeface(Typeface.DEFAULT);
                                                
                        overlayTextColor = Color.WHITE;
                        overlayBackgroundColor = Color.BLACK;
                        ovlPos = MjpegView.POSITION_UPPER_RIGHT;
                        displayMode = MjpegView.SIZE_STANDARD;
                        dispWidth = getWidth();
                        dispHeight = getHeight();
                }
        }

        public void setPositionCallback( Position l_position )
        {
        	position = l_position;
        }
        
        public void startPlayback() {
                if (mIn != null) 
                {
                    mRun = true;
                    thread.start();
                }
        }

        public void resumePlayback() {
                mRun = true;
                init(context);
                thread.start();
        }

        public void stopPlayback() {
        	if(mRun)
        	{
                mRun = false;
                boolean retry = true;
                while (retry) 
                {
                        try {
                                thread.join();
                                retry = false;
                        } catch (InterruptedException e) {
                        }
                }
        	}
        }

        public MjpegView(Context context, AttributeSet attrs) {
                super(context, attrs);
                init(context);
        }

        public void surfaceChanged(SurfaceHolder holder, int f, int w, int h) {
                thread.setSurfaceSize(w, h);
        }

        public void surfaceDestroyed(SurfaceHolder holder) {
                surfaceDone = false;
                stopPlayback();
        }

        public MjpegView(Context context) {
                super(context);
                init(context);
        }

        public void surfaceCreated(SurfaceHolder holder) {
                surfaceDone = true;
        }

        public void showFps(boolean b) {
                showFps = b;
        }

        public void setSource(MjpegInputStream source) {
                mIn = source;
                //startPlayback();
        }

        public void setOverlayPaint(Paint p) {
                overlayPaint = p;
        }

        public void setOverlayTextColor(int c) {
                overlayTextColor = c;
        }

        public void setOverlayBackgroundColor(int c) {
                overlayBackgroundColor = c;
        }

        public void setOverlayPosition(int p) {
                ovlPos = p;
        }

        public void setDisplayMode(int s) {
                displayMode = s;
        }
        
        public void setDisplayText(String text , int x, int y) 
        {
        	display_text = text;
        	display_text_x = x;
        	display_text_y = y;
        }
        
        @Override
        public boolean onTouchEvent(MotionEvent event) 
        {
            int action = event.getAction();

            if(action == MotionEvent.ACTION_UP)
            {
            	if(position!=null)
	            {
	            	position.done((X_touch*10)/480, (Y_touch*3)/360);
	            }
            	t_touch = new Timer();
            	t_touch.schedule(new TimerTask()
            	{
					@Override
					public void run() 
					{
						X_touch = (int) 0xFFFF;
		            	Y_touch = (int) 0xFFFF;
						cancel();
					}
				}, 2000);
            }
            else 
            {
            	X_touch = (int) event.getX();
            	Y_touch = (int) event.getY();
            	t_touch.cancel();
            }
            return true; 
        }
        
}