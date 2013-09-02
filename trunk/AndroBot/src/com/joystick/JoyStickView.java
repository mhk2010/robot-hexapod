package com.joystick;

import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

public class JoyStickView extends View 
{
		private Paint p = new Paint();
		public interface Position
		{
			void done(int x,int y);
		}
		public Position position = null;
        private static final int BACKGROUND = Color.rgb(0x57, 0x81, 0xFC);
        
        private int location_x = 0; 
        private int location_y = 0;
        private int size = 250;
        Context context;
    	private int obj_x = size/2;
    	private int obj_y = size/2;
    	private int action;
    	private int color_push = Color.LTGRAY;
    	private Timer t =null;
    	
        public JoyStickView(Context context) 
        {
            super(context);
            this.context = context;
            obj_x = size/2;
            obj_y = size/2;
            if(t == null)
            {
            	t = new Timer();
            }
        }

        public JoyStickView(Context context, AttributeSet attrs) 
        {
            super(context, attrs);
            this.context = context;
            obj_x = size/2;
            obj_y = size/2;
            if(t == null)
            {
            	t = new Timer();
            }
        }

        public JoyStickView(Context context, AttributeSet attrs, int defStyle) 
        {
            super(context, attrs, defStyle);
            this.context = context; 
            obj_x = size/2;
            obj_y = size/2;
            if(t == null)
            {
            	t = new Timer();
            }
        }
        
        public void setPositionCallback( Position l_position )
        {
        	position = l_position;
        }
        
        public void orientationChanged(float f)
        {
            this.invalidate();
        }
            
        @Override 
        protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
        {
           super.onMeasure(widthMeasureSpec, heightMeasureSpec);
		   this.setMeasuredDimension(size, size );
           
        }

        
        @Override
        public boolean onTouchEvent(MotionEvent event) 
        {
            action = event.getAction();

            if(action == MotionEvent.ACTION_MOVE)
            {
        		float tan_angle_x = (float) (Math.atan2(event.getX() - (size/2), event.getY() - (size/2)) - Math.PI/2);
        		obj_x = (int) (size/2 + (float) (75 * ( Math.cos(-tan_angle_x)))); 
        		obj_y = (int) (size/2 + (float) (75 * ( Math.sin(-tan_angle_x))));           	
            	
            	color_push = Color.RED;
            }
            else
            {
            	color_push = Color.LTGRAY;
            }
            
            t.scheduleAtFixedRate(new TimerTask() 
            {
                @Override
                public void run() 
                {
                	if(action == MotionEvent.ACTION_UP)
                    {
                		if(obj_x > (size/2))
                		{
                			obj_x--;
                		}
                		else if(obj_x < (size/2))
                		{
                			obj_x++;
                		}
                		
                		if(obj_y > (size/2))
                		{
                			obj_y--;
                		}
                		else if(obj_y < (size/2))
                		{
                			obj_y++;
                		}
                		
                		if((obj_x == (size/2)) && (obj_y == (size/2)))
        				{
                			this.cancel();
        				}
                		
                		if(position!=null)
        	            {
        	            	position.done(obj_x - size / 2, obj_y - size / 2);
        	            }
                        postInvalidate();
                    }
                }
            }, 0, 20);


            if(position!=null)
            {
            	position.done(obj_x - size / 2, obj_y - size / 2);
            }
            
            invalidate();
            
            return true; // processed
        }
        
        
		@Override
        protected void onDraw(Canvas canvas) 
        {
            super.onDraw(canvas);
            
            location_x = (int) (getWidth() / 2);
            location_y = (int) (getHeight() / 2);
            p.setStyle(Paint.Style.FILL_AND_STROKE);
            p.setColor(BACKGROUND);
            p.setStrokeWidth(2);
            p.setAlpha(90); 
            
            //big circle
            canvas.drawCircle(location_x, location_y, size/2, p);
            
            //arrows
            p.setStrokeWidth(2);
            p.setColor(Color.DKGRAY);
            int triangle_size = 20;
            canvas.drawLine( location_x - triangle_size/2, 40 ,location_x + triangle_size/2 , 40,p);
            canvas.drawLine( location_x - triangle_size/2, 40 ,location_x , 25,p);
            canvas.drawLine( location_x + triangle_size/2, 40 ,location_x , 25,p);

            canvas.drawLine( location_x - triangle_size/2, getHeight() - 40 ,location_x + triangle_size/2 , getHeight() - 40,p);
            canvas.drawLine( location_x - triangle_size/2, getHeight() - 40 ,location_x , getHeight() - 25,p);
            canvas.drawLine( location_x + triangle_size/2, getHeight() - 40 ,location_x , getHeight() - 25,p);

            canvas.drawLine( 40, location_y - triangle_size/2, 40, location_y + triangle_size/2 ,p);
            canvas.drawLine( 40, location_y - triangle_size/2, 25 , location_y ,p);
            canvas.drawLine( 40, location_y + triangle_size/2, 25 , location_y ,p);

            canvas.drawLine( getWidth() - 40, location_y - triangle_size/2, getWidth() - 40, location_y + triangle_size/2 ,p);
            canvas.drawLine( getWidth() - 40, location_y - triangle_size/2, getWidth() - 25 , location_y ,p);
            canvas.drawLine( getWidth() - 40, location_y + triangle_size/2, getWidth() - 25 , location_y ,p);
            
            
            //center circle
            p.setColor(Color.BLACK);
            canvas.drawCircle(location_x, location_y, size/25, p);
            p.setColor(Color.DKGRAY);
            canvas.drawCircle(location_x, location_y, size/27, p);
            p.setColor(Color.GRAY);
            canvas.drawCircle(location_x, location_y, size/32, p);
            p.setColor(Color.LTGRAY);
            canvas.drawCircle(location_x, location_y, size/100, p);
            
            
            //joystick stick
            p.setStyle(Paint.Style.FILL);
            p.setColor(Color.BLACK);
            p.setStrokeWidth(22);
            canvas.drawLine(location_x, location_y, obj_x,  obj_y, p);
            p.setColor(Color.DKGRAY);
            p.setStrokeWidth(20);
            canvas.drawLine(location_x, location_y, obj_x,  obj_y, p);
            p.setStrokeWidth(15);
            p.setColor(Color.GRAY);
            canvas.drawLine(location_x, location_y, obj_x,  obj_y, p);
            p.setStrokeWidth(5);
            p.setColor(Color.LTGRAY);
            canvas.drawLine(location_x, location_y, obj_x,  obj_y, p);

            //joystick button
            p.setColor(Color.BLACK);
            canvas.drawCircle(obj_x, obj_y, size/5 + 2, p);
            p.setColor(color_push);
            canvas.drawCircle(obj_x, obj_y, size/5, p);
            p.setColor(Color.GRAY);
            canvas.drawCircle(obj_x, obj_y, size/6, p);
            p.setColor(Color.DKGRAY);
            canvas.drawCircle(obj_x, obj_y, size/15, p);
            p.setColor(Color.BLACK);
            canvas.drawCircle(obj_x, obj_y, size/20, p);
            
        }
        

}

