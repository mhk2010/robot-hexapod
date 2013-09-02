package com.ssh;


public class SshParams
{
	public interface Callback
	{
		void done(String result);
	}
	public String ip = null;
	public int port = 0;
	public String user = null;
	public String password = null;
	public String cmd = null;
	public Callback callback = null;
};
class SshExec
{
	SshParams.Callback callback = null;
	String result = null;
	String error = null;
}
