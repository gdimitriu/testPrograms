/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the server implementation of problem JDS4.

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
public class JDS_4S
{
	public static int PORT_SERVER=13001;
	static public void main(String args[])
	{
		ServerSocket s_intilnire=null;
		Socket s_client=null;
		int[] buf;
		int[] rez;
		try{ s_intilnire=new ServerSocket(PORT_SERVER);}
		catch(IOException e1) {System.err.println(e1);}
		try
		{
			for(;;)
			{
				s_client=s_intilnire.accept();
				DataInputStream in=new DataInputStream(s_client.getInputStream());
				DataOutputStream out=new DataOutputStream(s_client.getOutputStream());
				buf=new int[10];
				for(int i=0;i<10;i++) buf[i]=in.readInt();
				rez=new int[10];
				for(int i=0;i<10;i++) rez[i]=0;
				for(int i=0;i<10;i++) rez[buf[i]]++;
				for(int i=0;i<10;i++) out.writeInt(rez[i]);
				s_client.close();
			}
		}catch(IOException e2) {System.err.println(e2);}
	}
}