/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Algorithms, Socket and Java.
	This is the main implementation of problem JPC1.

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
public class JPC1{
    static Object sync=new Object();
    public static void main(String  argv[]){
	double[] rez=new double[1];
	int n=(new Integer(argv[0])).intValue();
	int nr=(new Integer(argv[1])).intValue();
	double[] vector=new double[n];
	JPC1_1[] threads=new JPC1_1[nr];
	for(int i=0;i<n;i++) vector[i]=i;
	for(int i=0;i<nr;i++)
	{
	    threads[i]=new JPC1_1(sync,vector,i,n,nr,rez);
	    threads[i].start();
	}
	boolean end=true;
	while(end==true)
	    {
		end=false;
		for(int i=0;i<nr;i++)
			if(threads[i].isAlive()==true) end=true;
	     }
	double val=0.0;
	for(int i=0;i<n;i++) val=val+vector[i];
	for(int i=0;i<n;i++)System.out.print(vector[i]+" ");
	System.out.println();
	System.out.println(rez[0]);
	System.out.println(val);
    }
};
