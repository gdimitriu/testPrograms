/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the main implementation of problem JPC2.

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
public class JPC2_1 extends Thread{
    protected double[][] mat1;
    protected double[][] mat2;
    protected double[][] mat3;
    protected int n1;
    protected int n2;
    protected int pos;
    protected int nr;
    public JPC2_1(double[][] mat1,double[][] mat2,double[][] mat3,int n1,int n2,int pos,int nr){
	this.mat1=mat1;
	this.mat2=mat2;
	this.mat3=mat3;
	this.pos=pos;
	this.n1=n1;
	this.n2=n2;
	this.nr=nr;
    }
    public void run(){
	int i,j,k;
	for(i=pos;i<n1;i=i+nr)
	    for(j=0;j<n1;j++)
		{
		    mat3[i][j]=0.0;
		    for(k=0;k<n2;k++)
			mat3[i][j]+=mat1[i][k]*mat2[k][j];
		}
    }
}
