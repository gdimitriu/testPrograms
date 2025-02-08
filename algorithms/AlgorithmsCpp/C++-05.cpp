/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Cpp.
	This is the implementation of a list and determination the number of
	realization of the elements from this list. The list will be ordered downward.

    Algorithms and C is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and C is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and Cpp; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/

#include<iostream.h>
class rezultat
{
	int nr;
	int value;
public:
	rezultat *suivant;
	rezultat(int v)
	{ 
		nr=1;
		value=v;
		suivant=NULL; 
		}
	int realisation() { return nr;}
	void realizadd() {nr++;}
	int valueprt(){ return value;}
};
class liste
{
	rezultat *base;
public:
	liste(){};
	liste(int nr) { base=new rezultat(nr);}
	~liste();
	void listeadd(int nr);
	void listeprt();
};
	
int main()
{
	int nr;
	cout<<"How many numbers do you have ?\n";
	cin>>nr;
	int *vector;
	liste *vector1;
	vector=new int[nr];
	for(int i=0;i<nr;i++) cin>>vector[i];
	vector1=new liste(vector[0]);
	for(int i=1;i<nr;i++) vector1->listeadd(vector[i]);
	vector1->listeprt();
	delete vector;
	delete vector1;
}

void liste::listeprt()
{
	rezultat *mobil;
	mobil=base;
	while(mobil!=NULL)
	{
		cout<<"The number "<<mobil->valueprt()<<" is realized by "<<mobil->realisation()<<"\n";
		mobil=mobil->suivant;
	}
}
void  liste::listeadd(int nr)
{
	rezultat *mobil,*temp,*temp1;
	mobil=base;
	int teste=0;
	temp1=NULL;
	while(teste==0)
	{
		if(base->valueprt()<nr)
		{
			temp=new rezultat(nr);
			temp->suivant=base;
			base=temp;
			teste=1;
		}
		else
		{
			if(mobil->valueprt()==nr)
			{
				mobil->realizadd();
				teste=1;
			}
			else
			{
				if(mobil->valueprt()>nr)
				{
					temp1=mobil;
					if(mobil->suivant==NULL) break;
					else	mobil=mobil->suivant;
				}
				else
				{
					temp=new rezultat(nr);
					temp->suivant=temp1->suivant;
					temp1->suivant=temp;
					teste=1;
				}
			}
		}
	}
	if(teste==0)
	{
		temp=new rezultat(nr);
		mobil->suivant=temp;
	}
}
liste::~liste()
{
	rezultat *mobil;
	mobil=base;
	while(base!=NULL)
	{
		mobil=base;
		base=mobil->suivant;
		delete mobil;
	}
}