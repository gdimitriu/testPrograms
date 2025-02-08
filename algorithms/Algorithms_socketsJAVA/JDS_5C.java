/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the client implementation of problem JDS5.

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
public class JDS_5C{
    public static void main(String[] args){
	Socket sock;
	try{
	    sock=new Socket(args[0],new Integer(args[1]).intValue());
	    BufferedReader inc=new BufferedReader(new InputStreamReader(System.in));
	    DataInputStream in=new DataInputStream(sock.getInputStream());
	    DataOutputStream out=new DataOutputStream(sock.getOutputStream());
	    String str=inc.readLine();
	    out.writeUTF(str);
	    String strin=in.readUTF();
	    System.out.println(str+"->"+strin);
	}catch(Exception e1){System.out.println(e1.getMessage());}
    }
}
