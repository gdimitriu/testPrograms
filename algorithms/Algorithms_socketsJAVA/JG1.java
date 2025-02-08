/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the implementation of problem JG1.

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
import java.io.*;
import java.util.*;
class Model{
    private int x=0;
    public Model(){};
    public void increment(){x++;}
    public int getx(){return x;}
}
class FrameClose extends WindowAdapter{
    public void windowClosing(WindowEvent e){System.exit(0);}}
public class JG1 extends Frame{
    private Button b;
    protected Model m;
    private Controller  c;
    protected TextField tf;
    public static void main(String[] args){
	Frame v=new JG1();
    };
    public JG1(){
	setTitle("MVC");
	addWindowListener(new FrameClose());
	b=new Button("Actiune");
	add("North",b);
	m=new Model();
	c=new Controller(this);
	b.addActionListener(c);
	tf=new TextField(10);
	add("Center",tf);
	setSize(100,250);
	setVisible(true);
    }
}
class Controller implements ActionListener{
    private JG1 vw;
    public Controller(JG1 v){vw=v;}
    public void actionPerformed(ActionEvent e){
	vw.m.increment();
	int i=vw.m.getx();
	vw.tf.setText(""+i);
    }
}
