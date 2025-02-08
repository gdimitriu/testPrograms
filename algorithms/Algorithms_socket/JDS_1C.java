/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the client implementation of problem JDS1.

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

public class JDS_1
{
	public static final int PORT_SERVER=13000;
	static public void main(String args[])
	{
		Socket s=null;
		String output;
		byte[] b;
		try{
			s=new Socket(args[0],PORT_SERVER);
			DataInputStream in=new DataInputStream(s.getInputStream());
			DataOutputStream out=new DataOutputStream(s.getOutputStream());
			String str="Adresa mea este $ local";
			b=new byte[1024*2];
			str.getBytes(0,str.length(),b,0);
			out.write(b);
			int i=in.read(b);
			output=new String(b,0,0,i);
			System.out.println(output);
			str="Adresa mea este $ server";
			b=new byte[1024*2];
			str.getBytes(0,str.length(),b,0);
			out.write(b);
			b=new byte[1024*2];
			i=in.read(b);
			output=new String(b,0,0,i);
			System.out.println(output);
		}catch(IOException e0){ System.err.println(e0);}
		finally
		{
			try{if(s!=null)s.close();} catch(IOException e1){;}
		}
	}
}