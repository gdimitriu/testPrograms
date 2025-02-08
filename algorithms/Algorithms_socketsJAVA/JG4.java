/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the implementation of problem JG4.

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
import java.awt.*;
import java.awt.event.*;
import java.util.*;
class FrameClose extends WindowAdapter{
    public void windowClosing(WindowEvent event){System.exit(0);}
}
class vJG4 implements ActionListener{
    TextField first;
    TextField second;
    TextField operator;
    TextField display;
    public vJG4(TextField first,TextField second,TextField operator,TextField display){
	this.first=first;
	this.second=second;
	this.operator=operator;
	this.display=display;
    }
    public void actionPerformed(ActionEvent event){
	Double fd=new Double(first.getText());
	Double sd=new Double(second.getText());
	String sop=operator.getText();
	switch(sop.charAt(0)){
	case '+':
	    display.setText(new Double(fd.doubleValue()+sd.doubleValue()).toString());
	    break;
	case '-':
	    display.setText(new Double(fd.doubleValue()-sd.doubleValue()).toString());
	    break;
	case '*':
	    display.setText(new Double(fd.doubleValue()*sd.doubleValue()).toString());
	    break;
	case '/':
	    if(sd.doubleValue()==0.0) display.setText("Divided by zero");
	    display.setText(new Double(fd.doubleValue()/sd.doubleValue()).toString());
	    break;
	default:
	    display.setText("Operation unssuported");
	}
    }
}
class pJG4 extends Panel{
    Label l1;
    Label l2;
    Label l3;
    Label l4;
    TextField first;
    TextField second;
    TextField operator;
    TextField display;
    public void addComponents(){
	l1=new Label("First operand");
	l2=new Label("Second operand");
	l3=new Label("Operation: +,-,*,/");
	l4=new Label("Result of the operation");
	first=new TextField();
	second=new TextField();
	display=new TextField();
	display.setEditable(false);
	operator=new TextField();
	vJG4 al=new vJG4(first,second,operator,display);
	operator.addActionListener(al);
	setLayout(new GridLayout(4,2));
	add(l1);add(first);
	add(l2);add(second);
	add(l3);add(operator);
	add(l4);add(display);
    }
}
public class JG4{
    public static void main(String[] args){
	Frame f=new Frame("Operations");
	f.addWindowListener(new FrameClose());
	pJG4 panel=new pJG4();
	panel.addComponents();
	f.add(panel,BorderLayout.CENTER);
	f.setSize(400,400);
	f.setVisible(true);
    }
}
