// quicksort.cpp: implementation of the quicksort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "quicksort.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

quicksort::quicksort()
{
	fp.open("quicksort.dat",ios::out);
	cout<<"Introduceti ce dimensiune are sirul ";cout.flush();
	cin>>nr;
	sir=new float[nr];
	cout<<"Introduceti numele fisierului de intrare ";
	char fisier[32];
	cin>>fisier;
	ifstream fin(fisier,ios::in);
	int i;
	for(i=0;i<nr;i++) fin>>sir[i];
	fin.close();
	quick(0,nr-1);
	for(i=0;i<nr;i++) fp<<sir[i]<<' ';
	fp.flush();
}

quicksort::~quicksort()
{
	fp.close();
	delete sir;
}

void quicksort::quick(int st, int dr)
{
	if(st<dr)
	{
		poz(st,dr);
		quick(st,k-1);
		quick(k+1,dr);
	}
}

void quicksort::poz(int st, int dr)
{
	int s,d,aux1,d1,s1;
	float aux;
	s1=0; d1=-1;
	s=st; d=dr;
	if(d>nr-1) return;
	while(s<d)
	{
		if(sir[s]>sir[d])
		{
			aux=sir[d];
			sir[d]=sir[s];
			sir[s]=aux;
			aux1=s1;
			s1=-d1;
			d1=-aux1;
		}
		s=s+s1;
		d=d+d1;
	}
	k=d;
}
