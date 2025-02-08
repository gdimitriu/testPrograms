/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Cpp.
	This is the definition and implementation of problem 6.

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
class eleve
{
	char nom[20];
	char prenom[20];
	double notes[3];
	double moyenne;
public:
	eleve *suivant;
	eleve()
	{
		cout<<"Introduisez le nom: ";
		cin>>nom;
		cout<<"Introduisez le prenom: ";
		cin>>prenom;
		cout<<"Introduisez les trois notes:";
		for(int i=0;i<3;i++) cin>>notes[i];
		suivant=NULL;
		moyenne=0.0;
	}
	eleve(char *n,char *p,double *not)
	{
		strcpy(nom,n);
		strcpy(prenom,p);
		for(int i=0;i<3;i++) notes[i]=not[i];
		suivant=NULL;
		moyenne=0.0;
	}
	eleve(char *n,char *p,double n1,double n2,double n3)
	{
		strcpy(nom,n);
		strcpy(prenom,p);
		notes[0]=n1;
		notes[1]=n2;
		notes[2]=n3;
		suivant=NULL;
		moyenne=0;
	}
	void preleve()
	{
		cout<<"L'eleve "<<nom<<" "<<prenom<<" a les notes suivantes ";
		cout<<notes[0]<<" "<<notes[1]<<" "<<notes[2]<<endl;
	}
	void prelevem()
	{
		cout<<"L'eleve "<<nom<<" "<<prenom<<" a les notes suivantes ";
		cout<<" "<<notes[0]<<" "<<notes[1]<<" "<<notes[2];
		cout<<" et la moyenne de "<<moyenne<<endl;
	}
	void meleve(void)
	{
		moyenne=0.0;
		for(int i=0;i<3;i++) moyenne+=notes[i];
		moyenne/=3;
	}
	double mpr(void) 
	{
	    if(moyenne==0.0) meleve();
	    return moyenne;
	}
};
