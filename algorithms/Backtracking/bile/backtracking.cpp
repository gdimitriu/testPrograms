// backtracking.cpp: implementation of the backtraking class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "backtracking.h"
#include <fstream.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

backtracking::backtracking()
{
	final=new int[9];
	for(int i=0;i<9;i++) final[i]=0;
	nr_reusite=0;
	calcul(0);
}

backtracking::~backtracking()
{
	delete final;
}

void backtracking::Final()
{
	int j;
	cout<<"Saving data\n";cout.flush();
	ofstream fp("data.dat",ios::app);
	if(!fp)
	{
		cout<<"Eroare la deschidere fisier";
		exit(-1);
	}
	for(j=0;j<9;j++) fp<<final[j]<<' ';
	fp<<endl;
	fp.flush();
	fp.close();
}

int backtracking::init(int k)
{
	return 0;
}


bool backtracking::solutie(int k)
{
	if(k==8)
	{
		int sx,so,sz;
		int i;
		for(i=0,so=0;i<4;i++) so+=final[i];
		for(i=3,sx=0;i<7;i++) sx+=final[i];
		for(i=6,sz=final[0];i<9;i++) sz+=final[i];
		if(so!=sx) return false;
		if(sz!=so) return false;
		nr_reusite++;
		cout<<nr_reusite;cout.flush();
		return true;
	}
	else return false;
}

bool backtracking::conditii_interne(int k)
{
	int i;
	for(i=0;i<k;i++) if(final[i]==backup) return false;
	return true;
}

bool backtracking::succesor(int *a)
{
	if((*a)<9)
	{
		(*a)++;
		return true;
	}
	else return false;
}

void backtracking::calcul(int k)
{
	bool found,inainte;
	backup=init(0);
	k=0;
	while(k>=0)
	{
		while(1)
		{
			found=succesor(&backup);
			inainte=false;
			if(found) inainte=conditii_interne(k);
			if(inainte)	final[k]=backup;
			if(inainte || !found) break;
		}
		if(found)
		{
			if(solutie(k)) Final();
			else { k++; backup=init(k);}
		}
		else
		{
			k--;
			backup=final[k];
		}
	}
}
