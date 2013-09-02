package com.robot;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.View;

public class RobotView extends View 
{
	private Paint p = new Paint();
	
	private static final int BACKGROUND = Color.rgb(0x50, 0x70, 0x70);
	private static final int EYE_COLOR = Color.rgb(0x70, 0x70, 0x70);

	private int size = 300;
    RectF head = new RectF();
    RectF body = new RectF();
	RectF leg = new RectF();

	public int[] angle_head = new int[2];
	int[] angle_legs = new int[6];
	int[] angle_coudes = new int[6];
	boolean[] eyes = new boolean[]{false,false};
	int[] lights = new int[]{255,255};

	public RobotView(Context context) 
	{
	    super(context);
	}
	
	public RobotView(Context context, AttributeSet attrs) {
	        super(context, attrs);
	}
	
	public RobotView(Context context, AttributeSet attrs, int defStyle) {
	        super(context, attrs, defStyle);
	}
	
	public void setAngleCoude(int index, int angle)
	{
		angle_coudes[ index ] = angle;
        postInvalidate();
	}
	
	public void setAngleLeg(int index, int angle)
	{
		angle_legs[ index ] = angle;
        postInvalidate();
	}
	
	public void setHeadAngle(int index, int angleH, int angleV)
	{
		angle_head[ 0 ] = angleH;
		angle_head[ 1 ] = angleV;
        postInvalidate();
	}
	
	public int getHeadAngle(int index)
	{
		return angle_head[ index ];
	}
	
	public void setEye(int index_eye, boolean light)
	{
		eyes[ index_eye ] = light;
        postInvalidate();
	}
	
	public void setLights(int index_eye, int light)
	{
		lights[ index_eye ] = light;
        postInvalidate();
	
	}
	
	public void orientationChanged(float f)
	{
	        this.invalidate();
	}
	
	@Override 
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
	{
		int desiredWidth = size;
	    int desiredHeight = size - 50;

	    int widthMode = MeasureSpec.getMode(widthMeasureSpec);
	    int widthSize = MeasureSpec.getSize(widthMeasureSpec);
	    int heightMode = MeasureSpec.getMode(heightMeasureSpec);
	    int heightSize = MeasureSpec.getSize(heightMeasureSpec);

	    int width;
	    int height;

	    //Measure Width
	    if (widthMode == MeasureSpec.EXACTLY) {
	        //Must be this size
	        width = widthSize;
	    } else if (widthMode == MeasureSpec.AT_MOST) {
	        //Can't be bigger than...
	        width = Math.min(desiredWidth, widthSize);
	    } else {
	        //Be whatever you want
	        width = desiredWidth;
	    }

	    //Measure Height
	    if (heightMode == MeasureSpec.EXACTLY) {
	        //Must be this size
	        height = heightSize;
	    } else if (heightMode == MeasureSpec.AT_MOST) {
	        //Can't be bigger than...
	        height = Math.min(desiredHeight, heightSize);
	    } else {
	        //Be whatever you want
	        height = desiredHeight;
	    }
	    //MUST CALL THIS
	    setMeasuredDimension(width, height + 20);
	   
	}

	@Override
	protected void onDraw(Canvas canvas) 
	{
	    super.onDraw(canvas);
	    p.setStyle(Paint.Style.FILL_AND_STROKE);
	    p.setStrokeWidth(2);
	    p.setAlpha(90);
	    p.setColor(BACKGROUND);

	    int marge = 10;
		// Draw the robot head
	    int radius = 50;
	    int center_head_x = getWidth()/2;
	    int center_head_y = radius + marge;
	    head.set(	center_head_x - radius, 
		    			center_head_y - radius, 
						center_head_x + radius, 
						center_head_y + radius);
        canvas.drawArc(head, angle_head[0] + (270 - (radius/2)) , radius , true, p);

        //draw the robot eyes 
        p.setColor(EYE_COLOR);
        if( eyes[ 0 ] )
        {
    	    p.setStyle(Paint.Style.STROKE);
        }
        else
        {
    	    p.setStyle(Paint.Style.FILL_AND_STROKE);
        }
        canvas.drawCircle(marge*2, marge*2, 10, p);
        if( eyes[ 1 ] )
        {
    	    p.setStyle(Paint.Style.STROKE);
        }
        else
        {
    	    p.setStyle(Paint.Style.FILL_AND_STROKE);
        }
        canvas.drawCircle(getWidth() - (marge*2), marge*2, 10, p);
	        
        // Draw the robot body
	    p.setColor(BACKGROUND);
	    p.setStyle(Paint.Style.FILL_AND_STROKE);
        int test = 12;
        int largeur = 65;
        int hauteur = 150;
	    int center_body_x = getWidth()/2;
	    int center_body_y = center_head_y;
        canvas.drawRect(center_body_x - largeur + test , center_body_y , center_body_x + largeur -test , center_body_y + hauteur, p);  
        
        // Draw the robot legs
	    int radius_leg = 15;
        largeur = 50;
	    //forward left
	    int center_leg_x = getWidth()/2 - largeur;
	    int center_leg_y = radius + marge * 2;
        leg.set(	center_leg_x - radius, 
        				center_leg_y - radius, 
		    			center_leg_x + radius, 
		    			center_leg_y + radius);
		canvas.drawArc(leg, angle_legs[0]  + (180 - ( radius_leg / 2)) , radius_leg , true, p);
		
		//forward left coude
		double angleRad = Math.toRadians(angle_legs[0]);
        int center_x = center_leg_x - (int)(radius * Math.cos(angleRad));
        int center_y = center_leg_y - (int)(radius * Math.sin(angleRad));
        leg.set(	center_x - radius, 
						center_y - radius, 
						center_x + radius, 
						center_y + radius);
		canvas.drawArc(leg, angle_coudes[0]  + 90-( radius_leg / 2), radius_leg, true, p);
		

		
	    //middle left
		center_leg_x = getWidth()/2 - largeur;
	    center_leg_y = radius + marge + hauteur /2;
        leg.set(	center_leg_x - radius, 
        				center_leg_y - radius, 
		    			center_leg_x + radius, 
		    			center_leg_y + radius);
		canvas.drawArc(leg, angle_legs[1]  + (180 - ( radius_leg / 2)), radius_leg , true, p);
		
		//middle left coude
		angleRad = Math.toRadians(angle_legs[1]);
        center_x = center_leg_x - (int)(radius * Math.cos(angleRad));
        center_y = center_leg_y - (int)(radius * Math.sin(angleRad));
        leg.set(	center_x - radius, 
						center_y - radius, 
						center_x + radius, 
						center_y + radius);
		canvas.drawArc(leg, angle_coudes[1]  + 90-( radius_leg / 2), radius_leg, true, p);
		
	    //rear left
		center_leg_x = getWidth()/2 - largeur;
	    center_leg_y = radius + hauteur;
        leg.set(	center_leg_x - radius, 
        				center_leg_y - radius, 
		    			center_leg_x + radius, 
		    			center_leg_y + radius);
		canvas.drawArc(leg, angle_legs[2]  + (180 - ( radius_leg / 2)) , radius_leg , true, p);
		
		//rear left coude
		angleRad = Math.toRadians(angle_legs[2]);
        center_x = center_leg_x - (int)(radius * Math.cos(angleRad));
        center_y = center_leg_y - (int)(radius * Math.sin(angleRad));
        leg.set(	center_x - radius, 
						center_y - radius, 
						center_x + radius, 
						center_y + radius);
		canvas.drawArc(leg, angle_coudes[2]  + 90-( radius_leg / 2), radius_leg, true, p);
		
		//forward right
	    center_leg_x = getWidth()/2 + largeur;
	    center_leg_y = radius + marge * 2;
        leg.set(	center_leg_x - radius, 
        				center_leg_y - radius, 
		    			center_leg_x + radius, 
		    			center_leg_y + radius);
		canvas.drawArc(leg, angle_legs[3]  + (-radius_leg / 2) , radius_leg , true, p);
		
		//forward right coude
		angleRad = Math.toRadians(angle_legs[3]);
        center_x = center_leg_x + (int)(radius * Math.cos(angleRad));
        center_y = center_leg_y + (int)(radius * Math.sin(angleRad));
        leg.set(	center_x - radius, 
						center_y - radius, 
						center_x + radius, 
						center_y + radius);
		canvas.drawArc(leg, angle_coudes[3]  + 90-( radius_leg / 2), radius_leg, true, p);
		
	    //middle right
		center_leg_x = getWidth()/2 + largeur;
	    center_leg_y = radius + marge + hauteur /2;
        leg.set(	center_leg_x - radius, 
        				center_leg_y - radius, 
		    			center_leg_x + radius, 
		    			center_leg_y + radius);
		canvas.drawArc(leg, angle_legs[4]  + (-radius_leg / 2) , radius_leg , true, p);
		
		//middle right coude
		angleRad = Math.toRadians(angle_legs[4]);
        center_x = center_leg_x + (int)(radius * Math.cos(angleRad));
        center_y = center_leg_y + (int)(radius * Math.sin(angleRad));
        leg.set(	center_x - radius, 
						center_y - radius, 
						center_x + radius, 
						center_y + radius);
		canvas.drawArc(leg, angle_coudes[4]  + 90-( radius_leg / 2), radius_leg, true, p);
		
	    //rear right
		center_leg_x = getWidth()/2 + largeur;
	    center_leg_y = radius + hauteur;
        leg.set(	center_leg_x - radius, 
        				center_leg_y - radius, 
		    			center_leg_x + radius, 
		    			center_leg_y + radius);
		canvas.drawArc(leg, angle_legs[5]  + (-radius_leg / 2), radius_leg , true, p);
		
		//rear right coude
		angleRad = Math.toRadians(angle_legs[5]);
        center_x = center_leg_x + (int)(radius * Math.cos(angleRad));
        center_y = center_leg_y + (int)(radius * Math.sin(angleRad));
        leg.set(	center_x - radius, 
						center_y - radius, 
						center_x + radius, 
						center_y + radius);
		canvas.drawArc(leg, angle_coudes[5]  + 90-( radius_leg / 2), radius_leg, true, p);
	        
		// Draw the robot lights intensity
		marge = 135;
	    p.setStyle(Paint.Style.FILL_AND_STROKE);
	    
	    p.setColor(Color.rgb(255 - lights[ 1 ], 255 - lights[ 1 ], 255 - lights[ 1 ]));
        canvas.drawRect(getWidth()/2 - marge + 40, 10, getWidth()/2 - marge + 60, 30, p);
       
        p.setColor(Color.rgb(255 - lights[ 0 ], 255 - lights[ 0 ], 255 - lights[ 0 ]));
        canvas.drawRect(getWidth()/2 + marge - 60, 10, getWidth()/2 + marge - 40, 30, p);
		
	}

}

