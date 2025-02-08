/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the thread implementation of problem JPC1.

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
public class JPC1_1 extends Thread{
    protected Object mutex;
    protected double[] vect;
    protected int pos;
    protected int n;
    protected int nr;
    double[] rez;
    public JPC1_1(Object sync,double[] vect,int pos,int n,int nr,double[] rez)
    {
	mutex=sync;
	this.vect=vect;
	this.pos=pos;
	this.n=n;
	this.nr=nr;
	this.rez=rez;
    }
    public void run(){
	int i;
	double rez1=0.0;
	for(i=pos;i<n;i=i+nr) rez1=rez1+vect[i];
	synchronized(mutex){
	    rez[0]=rez[0]+rez1;
	}
    }
}
