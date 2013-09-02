package com.radar;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

public class RadarView extends View 
{
		private Paint p = new Paint();
		
        private static final int BACKGROUND = Color.rgb(0x57, 0x81, 0xFC);
        private static final int LINE_COLOR = Color.rgb(0x77, 0xA1, 0xFC);
        private static final int LAZER_COLOR = Color.rgb(0x00, 0xFF, 0x00);
        
        private static int lazer_position = 0;
        private static int lazer_size = 10;
        private RectF lazer_rect = new RectF();
        
        private int location_x = 0;
        private int location_y = 0;
        private int size = 150;

		public interface Position
		{
			void done(int x,int y);
		}
		public Position position = null;

        public void setPositionCallback( Position l_position )
        {
        	position = l_position;
        }
        
        
        private List<ObjectDetect> objs = new ArrayList<ObjectDetect>();

        private class ObjectDetect
        {
        	private int obj_id = 0;
        	private int obj_col = Color.rgb(0xFF, 0x00, 0x00);
            private int obj_angle = 0;
            private int obj_dist = 0;
            private int obj_size = 10;
            private RectF obj_rect = new RectF();
        	ObjectDetect(int angle, int dist , int size, int col )
        	{
        		setAngle(angle);
        		setDistance(dist);
        		setSize(size);
        		obj_col = col;
        	}
        	void setId(int id)
        	{
        		obj_id = id;
        	}
        	int getId()
        	{
        		return obj_id;
        	}
        	void setAngle(int angle)
        	{
            	if(angle > 180)angle = 180;
            	else if(angle < 0)angle = 0;
        		obj_angle = angle;
        	}
        	void setDistance(int dist)
        	{
            	if(dist == 0)dist = 1;
        		obj_dist = dist;
        	}
        	void setSize(int size)
        	{
            	if(size == 0)size = 1;
        		obj_size = size;
        	}
        };
        
        
        public RadarView(Context context) 
        {
            super(context);
        }

        public RadarView(Context context, AttributeSet attrs) {
                super(context, attrs);
        }

        public RadarView(Context context, AttributeSet attrs, int defStyle) {
                super(context, attrs, defStyle);
        }
        
        public void orientationChanged(float f)
        {
                this.invalidate();
        }
        
        public void setLazerPosition( int angle )
        {
        	lazer_position = angle;
        	postInvalidate();
        }
        
        public void deleteObjects(  )
        {
        	objs.clear();
        }
        
        public int addObjectPosition( int angle , int distance )
        {
        	ObjectDetect obj = new ObjectDetect(angle, distance, 10, Color.rgb(0xFF, 0x00, 0x00));
        	obj.setId(objs.size());
        	objs.add(obj);
        	return obj.getId();
        }
        public Boolean setObjectPosition( int id, int angle , int distance )
        {
        	if(id < objs.size())
        	{
	        	objs.get(id).setAngle(angle);
	        	objs.get(id).setDistance(distance);
        	}
        	return true;
        }
        
        @Override
        public boolean onTouchEvent(MotionEvent event) 
        {
            int action = event.getAction();

            if(action == MotionEvent.ACTION_DOWN)
            {
            	if(position!=null)
	            {
	            	position.done((int)event.getX(), (int)event.getY());
	            }
            }
			return false;
        }
        @Override 
        protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
        {
           super.onMeasure(widthMeasureSpec, heightMeasureSpec);
		   //int parentWidth = MeasureSpec.getSize(widthMeasureSpec);
		   //int parentHeight = MeasureSpec.getSize(heightMeasureSpec);
		   this.setMeasuredDimension(size * 2, size );
           
        }
	     
        @Override
        protected void onDraw(Canvas canvas) 
        {
                super.onDraw(canvas);
                location_x = (int) (getWidth() / 2);
                location_y = (int) (getHeight() );
                p.setStyle(Paint.Style.FILL_AND_STROKE);
                p.setColor(BACKGROUND);
                p.setStrokeWidth(2);
                p.setAlpha(90);

                // Draw the radar circle
                //canvas.drawCircle(location_x, location_y, size, p);
                lazer_rect.set(	location_x - size, 
    					location_y - size, 
    					location_x + size, 
    					location_y + size);
                canvas.drawArc(lazer_rect, 180 , 180 , true, p);
                
                // Set the style to stroke so we don't fill the other stuff
                p.setStyle(Paint.Style.STROKE);
                p.setColor(LINE_COLOR);
                
                // Draw the next two inner circles
                //canvas.drawCircle(location_x, location_y, size * 2/3, p);
                lazer_rect.set(	location_x - size* 2/3, 
    					location_y - size* 2/3, 
    					location_x + size* 2/3, 
    					location_y + size* 2/3);
                canvas.drawArc(lazer_rect, 180 , 180 , true, p);
                
                //canvas.drawCircle(location_x, location_y, size * 1/3, p);
                lazer_rect.set(	location_x - size* 1/3, 
    					location_y - size* 1/3, 
    					location_x + size* 1/3, 
    					location_y + size* 1/3);
                canvas.drawArc(lazer_rect, 180 , 180 , true, p);
                
                // Draw the cross in the middle
                canvas.drawLine(location_x, location_y - size, location_x, location_y, p);
                canvas.drawLine(location_x - size , location_y, size + location_x, location_y, p);
                
                // Draw the visible quadrant lines
                canvas.drawLine(location_x, location_y, location_x + (float)(size * Math.cos(5*Math.PI/4)), location_y + (float)(size * Math.sin(5*Math.PI/4)), p);
                canvas.drawLine(location_x, location_y, location_x + (float)(-size * Math.cos(5*Math.PI/4)), location_y + (float)(size * Math.sin(5*Math.PI/4)), p);

                // Draw the lazer
                p.setStrokeWidth(2);
                p.setColor(LAZER_COLOR);
                p.setAlpha(125);
                p.setStyle(Paint.Style.FILL_AND_STROKE);
                lazer_rect.set(	location_x - size, 
		    					location_y - size, 
		    					location_x + size, 
		    					location_y + size);
                canvas.drawArc(lazer_rect, 180 + lazer_position - lazer_size/2, lazer_size , true, p);
                
                // Draw all objects
                for(int loop = 0; loop < objs.size() ; loop++)
                {
                	p.setColor(objs.get(loop).obj_col);
                    p.setStyle(Paint.Style.STROKE);
                    objs.get(loop).obj_rect.set(	(float)location_x - (float)((float)objs.get(loop).obj_dist*((float)size/100)), 
				    		                		(float)location_y - (float)((float)objs.get(loop).obj_dist*((float)size/100)), 
				    		                		(float)location_x + (float)((float)objs.get(loop).obj_dist*((float)size/100)), 
				    		                		(float)location_y + (float)((float)objs.get(loop).obj_dist*((float)size/100)));
                    
                    canvas.drawArc(objs.get(loop).obj_rect,
		                    		180 + objs.get(loop).obj_angle - ((float)objs.get(loop).obj_size * (float)( 100 / objs.get(loop).obj_dist ))/2,
		                    		(float)objs.get(loop).obj_size * (float)( 100 / objs.get(loop).obj_dist ) ,
		                    		false,
		                    		p);

                }
                
                
        }
        
        
        
        
         /*public void updateTour(Location location, List<PointOfInterest> selectedPOIs) {
                this.location = location;
                nearbyPOIs.clear();
                
               for (PointOfInterest poi: selectedPOIs)
                {
                        Location loc = poi.getLocation();
                        Location poiLocation = new Location("");
                        poiLocation.setLatitude(loc.getLatitude());
                        poiLocation.setLongitude(loc.getLongitude());
                        double distValue = location.distanceTo(poiLocation);
                        
                        if (distValue <= 1000) {
                                nearbyPOIs.add(poi);
                        }
                }
                
                this.invalidate();
        };*/
}

