package com.androbot;

import com.ssh.Ssh;
import com.ssh.SshParams;
import com.ssh.SshParams.Callback;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class ActivityConnect extends Activity implements Callback
{
	public static final String TAG = "AndroBot";
	public static String IP = "78.233.202.101";
	public static EditText edit_text_ip;
	public static EditText edit_text_port;

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_connect);
		
		
		edit_text_ip = (EditText) findViewById(R.id.edittextIp);
		edit_text_port = (EditText) findViewById(R.id.edittextPort);
		
		Button but = (Button) findViewById(R.id.buttonConnect);
		but.setOnClickListener( new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
				SshParams ssh_param = new SshParams();
				// IP address of target
				ssh_param.ip = edit_text_ip.getText().toString();// "78.233.202.101";
				// default port number
				ssh_param.port = Integer.parseInt(edit_text_port.getText().toString());//2222;
				// default user
				ssh_param.user = "pi";
				// default password
				ssh_param.password = "louis";
				// default command
				ssh_param.cmd = "echo louis | sudo -S ./launch_webcam.sh start";
				// callback
				ssh_param.callback = ActivityConnect.this;
				new Ssh().execute(ssh_param);				
			}
		});
	}
	
	@Override
	public void onRestoreInstanceState(Bundle savedInstanceState) 
	{
		
	}

	@Override
	public void onSaveInstanceState(Bundle outState) 
	{
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) 
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		//getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void done(String result) 
	{
		if(result != null)
		{
			IP = edit_text_ip.getText().toString();
			Toast.makeText(getApplicationContext(), "Connecté" , Toast.LENGTH_LONG).show();
		    Intent i = new Intent(ActivityConnect.this, ActivityControl.class);
		    startActivity(i);
		    finish();
		}
		else
		{
			Toast.makeText(getApplicationContext(), "Erreur de connection !" , Toast.LENGTH_LONG).show();
		}
	}

	
}
