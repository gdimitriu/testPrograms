/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and C.
	This is the implementation of service system.

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
struct elem
{
	uint numar;
	struct elem *urmator;
};
int s;
struct elem *baza,*final,*temp;
int inserare(void)
{
	//input in a queue
	temp=(struct elem *)calloc(1,sizeof(struct elem));
	temp->urmator=NULL;
	if(baza!=NULL)
	{
		baza=final=temp;
	}
	else
	{
		final->urmator=temp;
		final=temp;
	}
	temp->numar=rand()%5;
	return 0;
}
int deservire(void)
{
	//service of element
	if(baza!=NULL)
	{
		baza->numar=baza->numar-s;
		if(baza->numar>0)
		{
			final->urmator=baza;
			baza=baza->urmator;
			final=final->urmator;
			final->urmator=NULL;
		}
		else
		{
			temp=baza;
			baza=baza->urmator;
			free(temp);
		}
	}
	return 0;
}
int main(void)
{
	int timp;
	baza=NULL;
	printf("Input the service constant ");fflush(stdout);
	scanf("%d",&s);fflush(stdin);
	while(1)
	{
		timp=rand()%2;
		if(timp==1) inserare();
		deservire();
	}
}