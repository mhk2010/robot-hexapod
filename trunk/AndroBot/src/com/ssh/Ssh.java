package com.ssh;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import com.androbot.ActivityConnect;
import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelExec;
import com.jcraft.jsch.JSch;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;

import android.os.AsyncTask;
import android.util.Log;


public class Ssh extends AsyncTask<SshParams, Void, SshExec> 
{
	@Override
    protected SshExec doInBackground(SshParams... params) 
	{	
		SshExec exec = new SshExec();
		exec.callback = params[0].callback;
		JSch jsch = new JSch();  
	    try 
	    {
	        Session session=jsch.getSession(params[0].user, params[0].ip, params[0].port);
	        Properties config = new Properties();
			config.put("StrictHostKeyChecking", "no");
			config.put("compression.s2c", "zlib,none");
			config.put("compression.c2s", "zlib,none");
	        session.setConfig(config);
	        session.setPassword("louis");
	        session.connect();
	        
	        String command = params[0].cmd;
	        Channel channel = session.openChannel("exec");
	        ((ChannelExec) channel).setCommand(command);
	        channel.setInputStream(null);
	        
	        ((ChannelExec) channel).setErrStream(System.err);
	        InputStream in;

			in = channel.getInputStream();
			channel.connect();
			Thread.sleep(1000);
			byte[] tmp = new byte[1024];
			while (in.available() > 0)
			{
				int i = in.read(tmp, 0, 1024);
				if (i < 0)
				{
					break;
				}
				exec.result = new String(tmp, 0, i);
			}
			
			if (channel.isClosed())
			{
				System.out.println("exit-status: " + channel.getExitStatus());
			}
			channel.disconnect();
			session.disconnect();
	    }
	    catch (JSchException e) 
	    {
	    	//Log.i(ActivityConnect.TAG,"IOException  => \n" + e.getMessage());
		} 
	    catch (IOException e) 
	    {
	    	//Log.i(ActivityConnect.TAG,"IOException  => \n" + e.getMessage());
		} 
	    catch (InterruptedException e)
		{
	    	//Log.i(ActivityConnect.TAG,"IOException  => \n" + e.getMessage());
		}
		
		return exec;
    }      

    @Override
    protected void onPostExecute(SshExec exec) 
    {
    	if(exec.callback != null)
    	exec.callback.done(exec.result);
    	Log.i(ActivityConnect.TAG,"result  => \n" + exec.result);
    }

    @Override
    protected void onPreExecute() 
    { 
    }
}


