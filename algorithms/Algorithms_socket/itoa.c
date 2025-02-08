/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the itoa implementation of problem CDS4.

    Algorithms and Socket is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and Socket is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and Socket; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<stdio.h>
#include"itoa.h"
void itoa(int value,char *str,int base)
{
volatile int i;
volatile int value1;
volatile int j;
volatile int flag;
	j=0;
	flag=1;
	if(value<0)
	{
		value=-value;
		str[j]='-';
		j++;
	}
	if(value==0)
	{
		str[j]='0';
	}
	else
	{
	    for(i=1000000000;i>0;i=i/10)
	    {
		    value1=value/i;
		    if((value1==0)&&(flag==0))
		    {
			    str[j]='0';
			    j++;
			    value=value-value1*i;
		    }
		    if(value1!=0)
		    {
			    flag=0;
			    str[j]=(char)(value1+48);
			    j++;
			    value=value-value1*i;
		    }
    	    }
	}
}
