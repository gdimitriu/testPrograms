// backtracking.cpp: implementation of the backtraking class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "backtracking.h"
#include<fstream.h>
#include<stdlib.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

backtracking::backtracking()
{
	cout<<"Introduceti dimensiunea permutarii=";
	cin>>nr_max;
	cout<<"Introduceti dimensiunea aranjementelor=";
	cin>>Nr_elem;
	nr_combinatii=combinari(nr_max,Nr_elem);
	int *temp;
	final=(int **)calloc(nr_combinatii,sizeof(int *));
	temp=(int *)calloc(nr_combinatii*Nr_elem,sizeof(int));
	for(int i=0;i<nr_combinatii;i++)
	{
		final[i]=temp;
		temp+=Nr_elem;
	}
	cout<<"total "<<nr_combinatii<<endl;cout.flush();
	calcul(0);
}

backtracking::~backtracking()
{
	free(final);
}

int backtracking::combinari(int n, int p)
{
	int nr1,nr2;
	int i;
	for(i=n,nr1=1;i>=(n-p+1);i--) nr1*=i;
	for(i=1,nr2=1;i<=p;i++) nr2*=i;
	return nr1/nr2;
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
	for(j=0;j<Nr_elem;j++) fp<<final[contor][j]<<' ';
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
	if(k==Nr_elem)
	{
		int i,j,k;
		for(i=0;i<contor;i++)
		{
			int test;
			for(j=0,test=0;j<Nr_elem;j++)
			{
				for(k=0;k<Nr_elem;k++) if(final[i][j]==final[contor][k]) test++;
			}
			if(test==Nr_elem) return false;
		}
		return true;
	}
	else return false;
}

bool backtracking::conditii_interne(int k)
{
	int i;
	for(i=0;i<k;i++) if(final[contor][i]==backup) return false;
	return true;
}

bool backtracking::succesor(int *a)
{
	if(first) return true;
	if((*a)<nr_max-1)
	{
		(*a)++;
		return true;
	}
	else return false;
}

void backtracking::calcul(int k)
{
	bool found,inainte;
	contor=0;
	nr_reusite=0;
	backup=init(0);
	k=0;
	first=true;
	while(k>=0)
	{
		while(1)
		{
			found=succesor(&backup);
			first=false;
			inainte=false;
			if(found) inainte=conditii_interne(k);
			if(inainte)	final[contor][k]=backup;
			if(inainte || !found) break;
		}
		if(found)
		{
			if(k<Nr_elem)
			{
				k++;
				backup=init(k);
				first=true;
			}
			else
			{
				if(solutie(k)) 
				{
					Final();
					contor++;
					if(contor==nr_combinatii) return;
				}
				else
				{
					backup=final[contor][k];
					first=false;
				}
			}
		}
		else
		{
			k--;
			backup=final[contor][k];
			first=false;
		}
	}
}
