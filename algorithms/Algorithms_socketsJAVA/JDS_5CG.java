/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the implementation of problem JDSG1.

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
import java.awt.*;
import java.awt.event.*;
import java.lang.*;
import java.io.*;
import java.net.*;
class FrameClose extends WindowAdapter{
    public void windowClosing(WindowEvent event){System.exit(0);}
};
class vJDS_5CG implements ActionListener{
    TextField input;
    TextField display;
    TextField address;
    TextField port;
    public vJDS_5CG(TextField input,TextField display,TextField inadd,TextField inport){
	this.input=input;
	this.display=display;
	address=inadd;
	port=inport;
    }
    public void actionPerformed(ActionEvent event){
	Socket sock=null;
	DataInputStream in;
	DataOutputStream out;
	try{
	    sock=new Socket(address.getText(),new Integer(port.getText()).intValue());
	}catch(Exception e){
	    System.out.println(e.getMessage());
	    System.exit(-1);
	}
	try{
	    in=new DataInputStream(sock.getInputStream());
	    out=new DataOutputStream(sock.getOutputStream());
	    out.writeUTF(input.getText());
	    display.setText(in.readUTF());
	    sock.close();
	}catch(Exception e1){
	    System.out.println(e1.getMessage());
	    System.exit(-1);
	}
    }
}
class pJDS_5CG extends Panel{
    Label l1;
    Label l2;
    Label la;
    Label lp;
    TextField input;
    TextField display;
    TextField inadd;
    TextField inport;
    public void addControls(){
	l1=new Label("The lowercase string");
	l2=new Label("The uppercase string");
	la=new Label("Address of the server");
	lp=new Label("Port of the server");
	input=new TextField();
	display=new TextField();
	display.setEditable(false);
	inadd=new TextField();
	inport=new TextField();
	vJDS_5CG al=new vJDS_5CG(input,display,inadd,inport);
	input.addActionListener(al);
	setLayout(new GridLayout(4,2));
	add(la);add(inadd);
	add(lp);add(inport);
	add(l1);add(input);
	add(l2);add(display);
    }
}
public class JDS_5CG{
    public static void main(String[] args){
	Frame f=new Frame("JDS_5CG");
	f.addWindowListener(new FrameClose());
	pJDS_5CG panel=new pJDS_5CG();
	panel.addControls();
	f.add(panel,BorderLayout.CENTER);
	f.setSize(400,400);
	f.setVisible(true);
    }
}
