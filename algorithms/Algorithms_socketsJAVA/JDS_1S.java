/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the server implementation of problem JDS1.

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
public class JDS_1S{
    public static void main(String[] args){
	ServerSocket server;
	Socket sock=null;
	try{
	    server=new ServerSocket(new Integer(args[0]).intValue());
	}catch(Exception e1){System.out.println(e1.getMessage());return;}
	try{
	    sock=server.accept();
	    DataInputStream in=new DataInputStream(sock.getInputStream());
	    DataOutputStream out=new DataOutputStream(sock.getOutputStream());
	    out.writeUTF("Please input the password");
	    String strin=in.readUTF();
	    if(strin.compareTo(args[1])==0) out.writeUTF("Acces accepted");
	    else out.writeUTF("Acces denied");
	}catch(Exception e2){
	    System.out.println(e2.getMessage());
	    try{
		sock.close();
	    }catch(Exception e3){};
	}
    }
}
