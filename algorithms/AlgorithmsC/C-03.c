/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and C.
	This is the implementation of nr of realization of a value in a vector

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
struct lista
{
	int valoare,aparitii;
	struct lista *next;
};
int produsul(int *a,int n)
{
	//make the multiplication of elements
	int prod=1;
	int c;
	for(c=1;c<n;c++) prod*=a[c];
		return prod;
}
struct lista *adauga(struct lista *cap,int numar)
{
	//put a element in the list
	struct lista *aux,*cap1;
	for(cap1=cap;cap1!=NULL;cap1=cap1->next)
		if(numar==cap1->valoare)
		{
			cap1->aparitii=cap1->aparitii+1;
			return cap;
		}
	aux=(struct lista *)calloc(1,sizeof(struct lista));
	aux->valoare=numar;
	aux->aparitii=1;
	aux->next=cap;
	return aux;
}
void afiseaza(struct lista *cap)
{
	//print the list
	while(cap!=NULL)
	{
		printf("Valoare %d apare de %d\n",cap->valoare,cap->aparitii);
		cap=cap->next;
	}
}
void dealocare(struct lista *cap)
{ 
	//dealocation
	struct lista *aux;
	while(cap!=NULL)
	{
		aux=cap;
		cap=cap->next;
		free(aux);
	}
}
int main()
{
	int i,n,*k,c;
	struct lista *baza;
	printf("Give n");
	scanf("%d",&n);
	k=(int *)calloc(n,sizeof(int));
	printf("Give the numbers\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&k[i]);
		fflush(stdin);
	}
	printf("multiplication=%d\n",produsul(k,n));
	baza=(struct lista *)calloc(1,sizeof(struct lista));
	baza->next=NULL;
	baza->valoare=k[0];
	baza->aparitii=1;
	for(c=1;c<n;c++)
		baza=adauga(baza,k[c]);
	afiseaza(baza);
}
	
