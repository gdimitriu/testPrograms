/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the implementation of problem JG2.

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
class TestPanel extends Panel{
    Label l1,l2;
    TextField tf1,tf2;
    TextField display1,display2;
    int count=0;
    public void addTestComponents(){
	l1=new Label("Login:");
	l2=new Label("Password");
	tf1=new TextField("Write your login name");
	tf2=new TextField("Password",30);
	tf2.setEchoChar('*');
	display1=new TextField();
	display2=new TextField();
	display1.setEditable(false);
	display2.setEditable(false);
	TextListener tl=new TextListener(){
		public void textValueChanged(TextEvent event){
		    display1.setText("TextEvent "+(++count));
		}
	    };
	ActionListener al=new ActionListener(){
		public void actionPerformed(ActionEvent event){
		    String oldString=display2.getText();
		    display2.setText(oldString+"...ActionEvent: "+event.getActionCommand());
		}
	    };
	tf1.addActionListener(al);
	tf1.addTextListener(tl);
	tf2.addActionListener(al);
	tf2.addTextListener(tl);
	setLayout(new GridLayout(3,2));
	add(l1);add(tf1);
	add(l2);add(tf2);
	add(display1);add(display2);
    }
}
public class JG2{
    private static int dimX=500,dimY=400;
    public static void main(String[] args){
	Frame frame=new Frame("Test Window");
	class FrameClose extends WindowAdapter{
	    public void windowClosing(WindowEvent e){System.exit(0);}
	}
	frame.addWindowListener(new FrameClose());
	TestPanel panelTest=new TestPanel();
	panelTest.addTestComponents();
	frame.add(panelTest,BorderLayout.CENTER);
	frame.setSize(dimX,dimY);
	frame.setVisible(true);
    }
}
