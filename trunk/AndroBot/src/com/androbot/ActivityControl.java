package com.androbot;

import java.io.IOException;
import java.net.URI;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;

import com.joystick.JoyStickView;
import com.joystick.JoyStickView.Position;
import com.mjpeg.MjpegInputStream;
import com.mjpeg.MjpegView;
import com.radar.RadarView;
import com.robot.RobotView;
import com.ssh.Ssh;
import com.ssh.SshParams;
import com.ssh.SshParams.Callback;
import com.tcp.TcpClient;
import com.tcp.TcpClient.ConnectChangeListener;
import com.tcp.TcpClient.IncommingMessageListener;

public class ActivityControl extends Activity implements Callback
{
	private byte vitesse = 4;
	private SeekBar np_vitesse =null;
	private Button but_scan;
	private Button but_toggle;
	public static JoyStickView joystick;
	private MjpegView cam_view1;
	private SshParams ssh_param;
	private RadarView radar = null;
	private RobotView robot = null;
	private int lazerPosition = 0;
	private int old_lazerPosition = 0;
	private int ObjectPosition = 0;
    private int id_object = 0;
	private TcpClient client ;
	private String serverIpAddress = "";
	private int serverTCPPort = 2001;
	private int serverSSHPort = 2222;
    private Boolean start_scan = false ;
    private int cmd = 0;
    
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
        
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_control);
		
		serverIpAddress = ActivityConnect.IP;
		
		//ssh params
		ssh_param = new SshParams();
		ssh_param.ip = serverIpAddress;
		ssh_param.port = serverSSHPort;
		ssh_param.user = "pi";
		ssh_param.password = "louis";
		ssh_param.callback = ActivityControl.this;
		
		//set view
		cam_view1 = (MjpegView) findViewById(R.id.cam_view);
		LayoutParams lp = (LayoutParams) cam_view1.getLayoutParams();
    	lp.width = 480 ;
    	lp.height= 360 ;
	    cam_view1.setLayoutParams(lp);
    	cam_view1.stopPlayback();
    	cam_view1.resumePlayback();
    	
    	
        radar = (RadarView) findViewById(R.id.radar_view);
        radar.setPositionCallback(new com.radar.RadarView.Position() 
		{
			@Override
			public void done(int x, int y)
			{
                if(client.IsConnected())
                {
                	client.Sendcommand(new byte[] {'*',1,0,0,(byte) ((int) ((300-x)*180)/300),vitesse,'#','#'});
                }
			}
		});
        radar.setLazerPosition(lazerPosition);
        id_object = radar.addObjectPosition(0, 0);
        
        robot = (RobotView) findViewById(R.id.robot_view); 
    	
        client = new TcpClient();
        client.setOnConnectChangeListener(new ConnectChangeListener() 
        {
			@Override
			public void OnConnectChange(boolean connect) 
			{
				if( connect )
				{
	                Log.i(ActivityConnect.TAG, "Socket connected");
					client.Sendcommand(new byte[] {'*',1,2,0,vitesse,'#','#'});
				}
				else
				{
	                Log.i(ActivityConnect.TAG, "Socket not connected");
				}
			}
		});
        client.setOnIncommingMessageChangeListener(new IncommingMessageListener() 
        {
			@Override
			public void OnIncommingMessageChange(List<Byte> msg) 
			{
                //Log.i(ActivityConnect.TAG, msg.toString());
                
              //from head
				if((msg.get(1) & 0x00ff) == 0)
				{
					//ultrason
					if(msg.get(2) == 0)
					{
						if( msg.size() > 5 ) 
						{
							ObjectPosition = (int)((msg.get(3) & 0xff) << 8);
							ObjectPosition |=  (msg.get(4) & 0xff) ;
							ObjectPosition &= 0x00FFFF;
							radar.setObjectPosition(id_object, lazerPosition, ObjectPosition);
						}
					}
					//camera
					else if(msg.get(2) == 1)
					{
						
					}
					//light
					else if(msg.get(2) == 2)
					{
						if( msg.size() == 9 ) 
						{
							short lefteye_value = (short) ((short) (msg.get(3) & 0x00ff) << 8) ;
							lefteye_value |=  msg.get(4) & 0x00ff ;
							short righteye_value = (short) ((short) (msg.get(5) & 0x00ff) << 8) ;
							righteye_value |=  msg.get(6) & 0x00ff ;
							robot.setLights(0, lefteye_value  * 150 / 1024 );
							robot.setLights(1, righteye_value * 150 / 1024 );
						}
					}
						
				}
				//from body
				else if((msg.get(1) & 0x00ff) == 1)
				{
					//servos position
					if((msg.get(2) & 0x00ff) == 0)
					{
						if( msg.size() == 19 ) 
						{
							lazerPosition = (180-((byte)msg.get(3) & 0x00FF));
							radar.setLazerPosition((lazerPosition + old_lazerPosition)/2);
							old_lazerPosition = lazerPosition;
							robot.setHeadAngle(0, (180-((byte)msg.get(3) & 0x00FF)) -90,(180-((byte)msg.get(4) & 0x00FF)) -90 );
							
							robot.setAngleLeg(0, ((byte)msg.get(5) & 0x00FF) -90 );
							robot.setAngleCoude(0, ((byte)msg.get(6) & 0x00FF) -90 );
							
							robot.setAngleLeg(1, ((byte)msg.get(7) & 0x00FF) -90 );
							robot.setAngleCoude(1, ((byte)msg.get(8) & 0x00FF) -90 );
							
							robot.setAngleLeg(2, ((byte)msg.get(9) & 0x00FF) -90 );
							robot.setAngleCoude(2, ((byte)msg.get(10) & 0x00FF) -90 );
							
							robot.setAngleLeg(3, ((byte)msg.get(11) & 0x00FF) -90 );
							robot.setAngleCoude(3, ((byte)msg.get(12) & 0x00FF) -90 );
							
							robot.setAngleLeg(4, ((byte)msg.get(13) & 0x00FF) -90 );
							robot.setAngleCoude(4, ((byte)msg.get(14) & 0x00FF) -90 );
							
							robot.setAngleLeg(5, ((byte)msg.get(15) & 0x00FF) -90 );
							robot.setAngleCoude(5, ((byte)msg.get(16) & 0x00FF) -90 );
						}
					}
				}
                
			}
		});
        client.Connect(serverIpAddress, serverTCPPort);
        
		joystick = (JoyStickView) findViewById(R.id.joystick);
		joystick.setPositionCallback(new Position() 
		{
			@Override
			public void done(int x, int y)
			{
				if(client.IsConnected())
				{
					int limit = 50;
					if((y < -limit) && ((x > -limit)||(x < limit)))
					{
						if(cmd != 1)
						{
							client.Sendcommand(new byte[] {'*',1,2,1,vitesse,'#','#'});
							cmd= 1;
			                Log.i(ActivityConnect.TAG," cmd = " + "AVANT");
						}
					}
					else if((y > limit) && ((x > -limit)||(x < limit)))
					{
						if(cmd != 2)
						{
							client.Sendcommand(new byte[] {'*',1,2,2,vitesse,'#','#'});
							cmd= 2;
			                Log.i(ActivityConnect.TAG," cmd = " + "ARRIERE");
						}
					}
					else if((x < -limit) && ((y > -limit)||(y < limit)))
					{
						if(cmd != 3)
						{
							client.Sendcommand(new byte[] {'*',1,2,3,vitesse,'#','#'});
							cmd= 3;
			                Log.i(ActivityConnect.TAG," cmd = " + "GAUCHE");
						}
					}
					else if((x > limit) && ((y > -limit)||(y < limit)))
					{
						if(cmd != 4)
						{
							client.Sendcommand(new byte[] {'*',1,2,4,vitesse,'#','#'});
							cmd= 4;
			                Log.i(ActivityConnect.TAG," cmd = " + "DROITE");
						}
					}
					else
					{
						if(cmd != 0)
						{
							client.Sendcommand(new byte[] {'*',1,2,0,vitesse,'#','#'});
							cmd= 0;
			                Log.i(ActivityConnect.TAG," cmd = " + "STOP");
						}
					}
				}
			}
		});

        but_toggle = (Button)findViewById(R.id.ButtonToggleLed);
        but_toggle.setOnClickListener(new OnClickListener() 
        {
			@Override
			public void onClick(View v) 
			{
				if(client.IsConnected())
				{
					client.Sendcommand(new byte[] {'*',0,3,5,'#','#'});
					if( but_toggle.getText().equals("Off") )
					{
						but_toggle.setText("On");
					}
					else
					{
						but_toggle.setText("Off");
					}
				}
			}
		});
        
        but_scan = (Button)findViewById(R.id.ButtonScan);
        but_scan.setOnClickListener(new OnClickListener() 
        {
			@Override
			public void onClick(View v) 
			{
				if( start_scan == false)
				{
					start_scan = true;
					if(client.IsConnected())
					{
						client.Sendcommand(new byte[] {'*',1,1,0,'#','#'});
						Log.i(ActivityConnect.TAG," cmd = " + "SCAN");
					}
					//ssh_param.cmd = "echo louis | sudo -S ./head_scan.sh 90";
					//new Ssh().execute(ssh_param);
				}
				else
				{
					 start_scan = false;
				}
			}
		});

        np_vitesse = (SeekBar) findViewById(R.id.seekBarVitesse);
        np_vitesse.setProgress(vitesse);
        np_vitesse.setOnSeekBarChangeListener(new OnSeekBarChangeListener() 
        {
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,boolean fromUser) 
			{
				vitesse = (byte) np_vitesse.getProgress();
			}

			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
		});
        
        
    	new WebCamReader().execute("http://" + serverIpAddress + ":8080/?action=stream");
	}
	
	
	public void onRestart() 
	{
		super.onRestart();
		ssh_param.cmd = "echo louis | sudo -S ./launch_webcam.sh start";
		new Ssh().execute(ssh_param);
	}
	public void onDestroy() 
	{
        super.onDestroy();
		ssh_param.cmd = "echo louis | sudo -S ./launch_webcam.sh stop";
		new Ssh().execute(ssh_param);
        if(cam_view1!=null)
        {
        	cam_view1.stopPlayback();
        }
        client.Deconnect();        
	}
    protected void onPause() 
	{
        super.onPause();
		// default command
		ssh_param.cmd = "echo louis | sudo -S ./launch_webcam.sh stop";
		new Ssh().execute(ssh_param);	
        if(cam_view1!=null)
        {
        	cam_view1.stopPlayback();
        }
        client.Deconnect();
    }
    
	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.control, menu);
		return true;
	}
	
	public boolean onOptionsItemSelected(MenuItem item) 
    {
       switch (item.getItemId()) 
       {       		
		 case R.id.action_assis:
			 if(client.IsConnected())
	         {
	         	client.Sendcommand(new byte[] {'*',1,2,5,vitesse,'#','#'});
	         }
		    return true;
       		
		 case R.id.action_etoile:
			 if(client.IsConnected())
	         {
	         	client.Sendcommand(new byte[] {'*',1,2,6,vitesse,'#','#'});
	         }
		    return true;
       		
		 case R.id.action_stop:
			 if(client.IsConnected())
	         {
	         	client.Sendcommand(new byte[] {'*',1,2,0,vitesse,'#','#'});
	         }
		    return true;
       }
       return false;
    }
		
	

	@Override
	public void done(String result) 
	{
		if(result != null)
		{
			cam_view1 = (MjpegView) findViewById(R.id.cam_view);
			LayoutParams lp = (LayoutParams) cam_view1.getLayoutParams();
	    	lp.width = 480 ;
	    	lp.height= 360 ;
		    cam_view1.setLayoutParams(lp);
	    	cam_view1.stopPlayback();
	    	cam_view1.resumePlayback();
	    	new WebCamReader().execute("http://" + serverIpAddress + ":8080/?action=stream");
        }
        client.Reconnect();
	}
	
	
	public class WebCamReader extends AsyncTask<String, Void, MjpegInputStream> 
	{
        protected MjpegInputStream doInBackground(String... url) 
        {
            HttpResponse res = null;
            DefaultHttpClient httpclient = new DefaultHttpClient();     
            try {
                res = httpclient.execute(new HttpGet(URI.create(url[0])));
                Log.d(ActivityConnect.TAG, "Request finished, status = " + res.getStatusLine().getStatusCode());
                if(res.getStatusLine().getStatusCode()==401)
                {
                    //You must turn off camera User Access Control before this will work
                    return null;
                }
                return new MjpegInputStream(res.getEntity().getContent());  
            } catch (ClientProtocolException e) {
                e.printStackTrace();
                //Error connecting to camera
            } catch (IOException e) {
                e.printStackTrace();
                //Error connecting to camera
            }

            return null;
        }

        protected void onPostExecute(MjpegInputStream result) 
        {
            cam_view1.setSource(result);
          	cam_view1.setDisplayMode(MjpegView.SIZE_FULLSCREEN);
            cam_view1.showFps(true);
        }
    }
}
