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
public class JPC2{
    public static void main(String[] args){
	int n1=new Integer(args[0]).intValue();
	int n2=new Integer(args[1]).intValue();
	int nr=new Integer(args[2]).intValue();
	double[][] mat1=new double[n1][n2];
	double[][] mat2=new double[n2][n1];
	double[][] mat3=new double[n1][n1];
	double[][] mat4=new double[n1][n1];
	JPC2_1[] threads=new JPC2_1[nr];
	int i,j;
	for(i=0;i<n1;i++) for(j=0;j<n2;j++) mat1[i][j]=1.0;
	for(i=0;i<n2;i++) for(j=0;j<n1;j++) mat2[i][j]=1.0;
	for(i=0;i<nr;i++)
	    {
		threads[i]=new JPC2_1(mat1,mat2,mat3,n1,n2,i,nr);
		threads[i].start();
	    }
	for(i=0;i<n1;i++)
	    for(j=0;j<n1;j++)
		{
		    mat4[i][j]=0.0;
		    for(int k=0;k<n2;k++)
			mat4[i][j]+=mat1[i][k]*mat2[k][j];
		}
	boolean end=true;
	while(end==true)
	    {
		end=false;
		for(i=0;i<nr;i++)
		    if(threads[i].isAlive()==true) end=true;
	    }
	for(i=0;i<n1;i++)
	    {
		for(j=0;j<n1;j++)
		    System.out.print(mat4[i][j]+" ");
		System.out.println();
	    }
	System.out.println("parallel");
	for(i=0;i<n1;i++)
	    {
		for(j=0;j<n1;j++)
		    System.out.print(mat3[i][j]+" ");
		System.out.println();
	    }
    }
}
