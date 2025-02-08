/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the server implementation of problem JDS3.

    Algorithms and Socket is free software; you can redistribute it 
    and/or modify it under the terms of the GNU General Public License 
    as published by the Free Software Foundation; either version 2 of 
    the License, or (at your option) any later version.

    Algorithms, Socket and Java is distributed in the hope that it will be
    useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms, Socket and Java; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
import java.lang.*;
import java.net.*;
import java.io.*;
import java.util.*;
public class JDS_3S{
   public static InetAddress local;
   public static void main(String[] args){
	ServerSocket server;
	try{
	    local=InetAddress.getLocalHost();
	    server=new ServerSocket(new Integer(args[0]).intValue());
	}catch(Exception e){System.out.println(e.getMessage());return;}
	try{
	    Socket sock=server.accept();
	    DataInputStream in=new DataInputStream(sock.getInputStream());
	    DataOutputStream out=new DataOutputStream(sock.getOutputStream());
	    String str=in.readUTF();
	    String localstr=new String(local.getHostAddress()+":"+args[0]);
	    String outstr=str.replaceAll("[$]",localstr);
	    out.writeUTF(outstr);
	}
	catch(Exception e1){System.out.println(e1.getMessage());}
   }
}
