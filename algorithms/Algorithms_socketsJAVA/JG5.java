/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the implementation of problem JG5.

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
import java.applet.*;
class vJG5 implements ActionListener{
    TextField input;
    TextField display;
    public vJG5(TextField input,TextField display){
	this.input=input;
	this.display=display;
    }
    public void actionPerformed(ActionEvent event){
	String strin=input.getText();
	String strout=strin.toUpperCase();
	display.setText(strout);
    }
}
public class JG5 extends Applet{
    Label l1;
    Label l2;
    TextField input;
    TextField display;
    public void init(){
	l1=new Label("The lowercase string");
	l2=new Label("The uppercase string");
	input=new TextField();
	display=new TextField();
	display.setEditable(false);
	vJG5 al=new vJG5(input,display);
	input.addActionListener(al);
	setLayout(new GridLayout(2,2));
	add(l1);add(input);
	add(l2);add(display);
    }
}
