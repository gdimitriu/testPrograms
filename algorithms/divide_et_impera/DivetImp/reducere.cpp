// reducere.cpp: implementation of the reducere class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "reducere.h"
#include<stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

reducere::reducere()
{
	char file[32];
	cout<<"Introduceti numele fisierului in care aveti elementele ";
	cin>>file;
	ifstream fpi(file,ios::in);
	cout<<"Introduceti cite numere aveti ";
	cin>>nr;
	int i;
	valori=(float *)calloc(nr,sizeof(float));
	for(i=0;i<nr;i++) fpi>>valori[i];
	fpi.close();
	cout<<operatie(0,nr-1);
}

reducere::~reducere()
{
	free(valori);
}

float reducere::operatie(int beg,int fin)
{
	if((fin-beg)==0) return valori[beg];
	if((fin-beg)<2) return valori[beg]+valori[fin];
	else
	{
		int temp=(fin-beg)/2;
		return operatie(beg,beg+temp)+operatie(beg+temp+1,fin);
	}
}
