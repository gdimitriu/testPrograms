/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the client implementation of problem JDS4.

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
import java.util.*;

public class JDS_4C
{
	public static final int PORT_SERVER=13001;
	static public void main(String args[])
	{
		Socket s=null;
		byte[] b;
		int[] buf=new int[10];
		int[] rez=new int[10];
		try{
			s=new Socket(args[0],PORT_SERVER);
			DataInputStream in=new DataInputStream(s.getInputStream());
			DataOutputStream out=new DataOutputStream(s.getOutputStream());
			Random Randgen=new Random();
			for(int i=0;i<10;i++) 
			{ 
				buf[i]=(Randgen.nextInt()%10);
				if(buf[i]<0) buf[i]=-buf[i];
			}
			for(int i=0;i<10;i++) out.writeInt(buf[i]);
			for(int i=0;i<10;i++) rez[i]=in.readInt();
			for(int i=0;i<10;i++) System.out.print(buf[i]+" ");
			System.out.println();
			for(int i=0;i<10;i++) System.out.print(rez[i]+" ");
			System.out.println();
			s.close();
		}catch(IOException e0) {System.err.println(e0);}
	}
}