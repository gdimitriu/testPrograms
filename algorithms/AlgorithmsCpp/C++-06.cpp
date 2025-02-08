/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Cpp.
	This is the implementation of problem 6.

    Algorithms and Cpp is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and Cpp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and Cpp; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include"C++-06.h"

class lista
{
	eleve  *temp,*base,*aux;
	int sorte;
public:
	lista() { 	base=temp=new eleve();}
	~lista();
	void addeleve();
	void calcm() { sorte=0; for(temp=base;temp!=NULL;temp=temp->suivant) temp->meleve();}
	void printlista() { for(temp=base;temp!=NULL;temp=temp->suivant) temp->preleve();}
	void printmlista(){ for(temp=base;temp!=NULL;temp=temp->suivant) temp->prelevem();}
	void printlista(int prag)
	{
		for(temp=base;temp!=NULL;temp=temp->suivant) 
			if(temp->mpr()>=prag) temp->prelevem();
	}
	int concours(int k);
	void sort();
};
lista::~lista()
{
	while(base!=NULL)
	{
		aux=base;
		base=base->suivant;
		delete aux;
	}
}
void lista::addeleve()
{
	temp=new eleve();
	int flag;
	aux=base;
	if(sorte!=1)
	{
		while(aux->suivant!=NULL) aux=aux->suivant;
		aux->suivant=temp;
	}
	else
	{
		temp->meleve();
		flag=0;
		if(aux->mpr()<temp->mpr())
		{
			temp->suivant=base;
			base=temp;
			flag=1;
		}
		while((aux->suivant!=NULL)&&(flag==0))
		{
			if(aux->suivant->mpr()<temp->mpr())
			{
				temp->suivant=aux->suivant;
				aux->suivant=temp;
				flag=1;
			}
			aux=aux->suivant;
		}
		if(flag==0) aux->suivant=temp;
	}
}
void lista::sort()
{
	eleve *temp1,*max,*base1=NULL,*aux1=NULL;	
	int flag;
	if(sorte==0)
	{
		while(base!=NULL)
		{
			flag=0;
			temp1=temp=base;
			aux=max=base;
			aux=aux->suivant;
			while(aux!=NULL)
			{
				if(max->mpr()<aux->mpr()) 
				{
					max=aux;
					temp1=temp;
					flag=1;
				}
				temp=aux;
				aux=aux->suivant;
			}
			if(flag==0) //si base c'est le plus grand
			{
				if(aux1==NULL && base1==NULL) //pour le premier fois
				{
					aux1=base1=base;
					base=base->suivant;
					aux1->suivant=NULL;
				}else
				{
					aux1->suivant=base;
					aux1=base;
					base=base->suivant;
					aux1->suivant=NULL;
				}
			}
			else
			{
				if(aux1==NULL	&& base1==NULL) //pour le premier fois
				{
					aux1=base1=max;
					temp1->suivant=max->suivant;
					aux1->suivant=NULL;
				}
				else
				{
					aux1->suivant=max;
					aux1=max;
					temp1->suivant=max->suivant;
					aux1->suivant=NULL;
				}
			}				
		}
		base=base1;
		sorte=1;
	}	
}
int lista::concours(int k)
{
	if(sorte=0) sort();
	int places=0;
	aux=base;
	while(places<k)
	{
		aux->prelevem();
		places++;
		if(places==k)
		{
			temp=aux->suivant;
			while(temp->mpr()==aux->mpr())
			{
				temp->prelevem();
				places++;
				temp=temp->suivant;
			}
		}
		else aux=aux->suivant;
	}
	return places;
}


int main()
{
	lista *liste=new lista();
	int prag;
	for(int i=0;i<3;i++) liste->addeleve();
	liste->calcm();
	liste->sort();
	liste->printmlista();
	cin>>prag;
	liste->printlista(prag);
	cin>>prag;
	cout<<"Places avaible "<<liste->concours(prag)<<endl;
}