/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the server implementation of problem JDS2.

    Algorithms and Socket is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and Socket is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and Socket; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
import java.io.*;
import java.net.*;
class deservire
{
	protected DataInputStream in;
	protected DataOutputStream out;
	protected Socket client;
	StringBuffer output;
	String input;
	byte[] b;
	deservire(Socket s_client)
	{
		try
		{
			client=s_client;
			in=new DataInputStream(client.getInputStream());
			out=new DataOutputStream(client.getOutputStream());
			b=new byte[1024*2];
			int i=in.read(b);
			input=new String(b,0,0,i);
			char temp;
			output=new StringBuffer("");
			for(int j=0;j<input.length();j++)
			{
				temp=input.charAt(j);
				if(temp<97) output.append(temp);
				else output.append((char)(temp-32));
			}
			String str=output.toString();
			str.getBytes(0,str.length(),b,0);
			out.write(b);
			client.close();
		}catch(IOException e2){ System.err.println(e2);}
	}
}

public class JDS_2S
{
	public static final int PORT_SERVER=12345;
	static public void main(String args[])
	{
		ServerSocket s_intilnire=null;
		Socket s_client=null;

		try{ s_intilnire=new ServerSocket(PORT_SERVER);}
		catch(IOException e1) {System.err.println(e1);}
		try
		{
			for(;;)
			{
				s_client=s_intilnire.accept();
				deservire d=new deservire(s_client);
			}
		}catch(IOException e3) {System.err.println(e3);}
	}
}