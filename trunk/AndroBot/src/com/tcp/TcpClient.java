package com.tcp;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;


public class TcpClient
{
	private InputStream input;
	private OutputStream output;
	private Socket socket;
	private volatile boolean connected;
	private Thread thread = null;
	private String mhost;
	private int mport;
	

    public interface ConnectChangeListener
    {
        public void OnConnectChange(boolean connect);
    } 
    public interface IncommingMessageListener
    {
        public void OnIncommingMessageChange(List<Byte> msg);
    }
    private ConnectChangeListener mOnConnect = null;
    private IncommingMessageListener mOnIncommingMessage = null;

	public TcpClient()
	{
		mhost= null;
		mport= 0;
		input = null;
		socket = null;
		connected = false;
		mOnIncommingMessage = null;
		mOnConnect = null;
	}
	public boolean Reconnect(  )
	{
		boolean out = false;
		if(( thread != null ) &&( mhost != null ) && (mport !=0))
		{
			if(!thread.isAlive())
			{
				thread = new Thread(SocketThread);
		    	thread.start();
		    	out = true;
			}
		}
		return out;
	}
	public void Deconnect(  )
	{
		connected = false;
		if(mOnConnect!=null)
		{
			mOnConnect.OnConnectChange(false);
		}
		thread.interrupt();
	}
	public Boolean Connect(String host, int port)
	{
		mhost= host;
		mport= port;
		thread = new Thread(SocketThread);
    	thread.start();
	    return true; 
	}
	public Boolean IsConnected()
	{
		return connected;
	}
    public void setOnIncommingMessageChangeListener(IncommingMessageListener OnIncommingMessage)
    {
    	mOnIncommingMessage = OnIncommingMessage;
    }
    public void setOnConnectChangeListener(ConnectChangeListener connectChangeListener)
    {
        mOnConnect = connectChangeListener;
    }
	
	
	Runnable SocketThread = new Runnable() 
	{
		private boolean InitSocket()
		{
			boolean o_success= false;
        	try 
		    {
				socket = new Socket(mhost, mport);
				if(socket.isConnected() == true)
				{
					connected = true;
				    input = socket.getInputStream();
				    output = socket.getOutputStream();
				    o_success= true;
				}
		    } 
		    catch (UnknownHostException e)
		    {
		    	e.printStackTrace();
		    } 
		    catch (IOException e) 
		    {
		    	e.printStackTrace();
		    }
        	return o_success;
		}
		@Override
		public void run() 
		{
			if(InitSocket() == true)
			{
				if(mOnConnect!=null)
				{
					mOnConnect.OnConnectChange(true);
				}
	        	try 
				{
		            int readBytes = 0;
		            while (connected)
		            {
		        	    byte[] buffer = new byte[1025];
		            	readBytes = input.read(buffer, 0, 1024);
		                if ((readBytes != 0) || (readBytes != -1) || (readBytes < 1024))
		                {
	    					int tmp = 0;
	    					List<Byte> message_buffer = new ArrayList<Byte>();
		                	for(int i = tmp; i < readBytes + 1 ; i++ )
		                    {
		                		if( buffer[tmp] == '*' )
		                    	{
	                        		message_buffer.add(buffer[i]);
	                				if((buffer[i] == '#' ) && (buffer[i + 1] == '#' ))
			                        {
		                        		message_buffer.add(buffer[i + 1]);
		                        		if(mOnIncommingMessage != null)
		                        		{
		                        			mOnIncommingMessage.OnIncommingMessageChange(message_buffer);
		                        		}
			                        	tmp = i + 1; 
			                        	message_buffer = new ArrayList<Byte>();
			                        }
		                    	}
		                		else
		                		{
		                			tmp++;
		                			if(tmp > 1024)
		                			{
		                				i = readBytes + 1 ;
		                			}
		                		}
		                    }
		                }
		                try 
		                {
		                	Thread.sleep(100);
		                } catch (InterruptedException e) {}
		            }
				} 
				catch (IOException e) 
				{
				    e.printStackTrace();
				} 
				try {
					socket.close();
					input = null;
					socket = null;
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			else
			{
				if(mOnConnect!=null)
				{
					mOnConnect.OnConnectChange(false);
				}
			}
		}
	};
 
	
	
	public void Sendcommand(final byte[] pass_bytes)
	{
    	if(socket != null)
		{
			if(socket.isConnected())
			{
				new Thread(new Runnable()
				{ 
		            public void run()
		            {
		            	try {
							output.write(pass_bytes, 0, pass_bytes.length);
						} catch (IOException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
		    			try {
							Thread.sleep(400);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
		            }
				}).start();
				
			}
		}
	}
}
