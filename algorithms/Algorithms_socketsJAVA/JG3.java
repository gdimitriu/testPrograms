/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the implementation of problem JG3.

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
import java.util.*;
class FrameClose extends WindowAdapter{
    public void windowClosing(WindowEvent event){System.exit(0);}
};
class vJG3 implements ActionListener{
    TextField input;
    TextField display;
    public vJG3(TextField input,TextField display){
	this.input=input;
	this.display=display;
    }
    public void actionPerformed(ActionEvent event){
	String strin=input.getText();
	String strout=strin.toUpperCase();
	display.setText(strout);
    }
}
class pJG3 extends Panel{
    Label l1;
    Label l2;
    TextField input;
    TextField display;
    public void addComponents(){
	l1=new Label("The lowercase string");
	l2=new Label("The uppercase string");
	input=new TextField();
	display=new TextField();
	display.setEditable(false);
	vJG3 al=new vJG3(input,display);
	input.addActionListener(al);
	setLayout(new GridLayout(2,2));
	add(l1);add(input);
	add(l2);add(display);
    }
}
public class JG3{
    public static void main(String[] args){
	Frame f=new Frame("JG3");
	f.addWindowListener(new FrameClose());
	pJG3 panel=new pJG3();
	panel.addComponents();
	f.add(panel,BorderLayout.CENTER);
	f.setSize(400,400);
	f.setVisible(true);
    }
}
