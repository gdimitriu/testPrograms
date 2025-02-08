/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and C.
	This is the implementation of list of cars.

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
#define N 10
struct inmatriculare
{
	char marca[20];
	char culoare[10];
	int nr;
	struct inmatriculare *urmator;
};
int main(void)
{
	struct inmatriculare masini[N],*baza,*p,*temp;
	int i,j,k;
	for(i=0;i<N;i++)
	{
		printf("Type[%d] \n",i);fflush(stdout);
		scanf("%s",masini[i].marca);fflush(stdin);
		printf("color[%d]\n",i);fflush(stdout);
		scanf("%s",masini[i].culoare);fflush(stdin);
		printf("number[%d]\n",i);fflush(stdout);
		scanf("%d",&masini[i].nr);fflush(stdin);
		masini[i].urmator=(struct inmatriculare *)NULL;
	}
	baza=p=temp=masini;
	for(i=1;i<N;i++)
	{
		temp=p=baza;
		if(baza->nr>=masini[i].nr) //daca elem < baza
		{
			masini[i].urmator=baza;
			baza=&masini[i];
		}
		else//pt restul elem != baza
		{
			while(p!=(struct inmatriculare *)NULL)
			{
				if(p->nr<masini[i].nr)
				{
					temp=p;
					p=p->urmator;
					if(p==(struct inmatriculare *)NULL) temp->urmator=&masini[i];
				}
				else
				{
					masini[i].urmator=temp->urmator;
					temp->urmator=&masini[i];
					break;
				}
			}
		}
	}
	//afisez
	p=baza;
	printf("ordered list\n");
	for(i=0;i<N;i++)
	{
		printf("%d\n",p->nr);
		p=p->urmator;
	}
}
