/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and C.
	This is the implementation of sorting operations.

    Algorithms and C is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and C is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and C; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<stdio.h>
#include<stdlib.h>
void bubble(int *sir,int contor)
{
	//bubble sort
	int i,j,temp;
	for(i=1;i<contor;i++)
	for(j=contor-1;j>=i;j--)
	{
		if(sir[j-1]>sir[j])
		{
			temp=sir[j-1];
			sir[j-1]=sir[j];
			sir[j]=temp;
		}
	}
}
void sel(int *sir,int contor)
{
	//sort by selection
	int i,j,k;
	int temp1,temp;
	for(i=0;i<contor-1;i++)
	{
		k=i;
		temp1=0;
		temp=sir[k];
		for(j=i+1;j<contor;j++)
		{
			if(sir[j]<temp)
			{
				k=j;
				temp=sir[k];
				temp1=1;
			}
		}
		if(temp1==1)
		{
			sir[k]=sir[i];
			sir[i]=temp;
		}
	}
}
				
void ins(int *sir,int contor)
{
	//sort by insertion
	int i,j;
	int temp;
	for(i=1;i<contor;i++)
	{
		temp=sir[i];
		for(j=i-1;j>=0&&temp<sir[j];j--)
		{
			sir[j+1]=sir[j];
			sir[j]=temp;
		}
	}
}

int main(void)
{
int *sir1;
int nr,i;
	printf("\nInput the number of elements nr=");fflush(stdout);
	scanf("%d",&nr);fflush(stdin);
	sir1=(int *)calloc(nr,sizeof(int));
	for(i=0;i<nr;i++)
	{
		printf("\nelem %d=",i);fflush(stdout);
		scanf("%d",&sir1[i]);fflush(stdin);
	}
	ins(sir1,nr);
	printf("the ordered elements are\n");fflush(stdout);
	for(i=0;i<nr;++i)
	{
		printf("%d=%d\n",i,sir1[i]);fflush(stdout);
	}
	free(sir1);
	exit(0);
}