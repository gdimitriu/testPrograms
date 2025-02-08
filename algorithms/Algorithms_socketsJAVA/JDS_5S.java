/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the server implementation of problem JDS5.

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
import java.io.*;
import java.util.*;
import java.net.*;
public class JDS_5S{
    public static void main(String[] args){
	ServerSocket serv;
	try{
	    serv=new ServerSocket(new Integer(args[0]).intValue());
	}catch(Exception e1) {return ;}
	try{
	    Socket sock=serv.accept();
	    DataOutputStream out=new DataOutputStream(sock.getOutputStream());
	    DataInputStream in=new DataInputStream(sock.getInputStream());
	    String str=in.readUTF();
	    String strout=str.toUpperCase();
	    out.writeUTF(strout);
	    //	    sock.close();
	}catch(Exception e){}
    }
}
