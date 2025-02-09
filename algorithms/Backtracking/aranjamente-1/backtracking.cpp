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
	nr_combinatii=aranjamente(nr_max,Nr_elem);
	val_partial=aranjamente(nr_max-1,Nr_elem-1);
	matrice=new int[nr_max];
	int *temp;
	final=(int **)calloc(nr_combinatii,sizeof(int *));
	temp=(int *)calloc(nr_combinatii*Nr_elem,sizeof(int));
	for(int i=0;i<nr_combinatii;i++)
	{
		final[i]=temp;
		temp+=Nr_elem;
	}
	for(i=0;i<nr_max;i++) matrice[i]=0;
	cout<<"total "<<nr_combinatii<<" partial "<<val_partial<<endl;cout.flush();
	calcul(0);
}

backtracking::~backtracking()
{
	free(final);
	delete matrice;
}

int backtracking::aranjamente(int n, int p)
{
	int nr1;
	int i;
	nr1=1;
	for(i=n;i>=(n-p+1);i--) nr1*=i;
	return nr1;
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
	if(k==0)
	{
		while(1)
		{
			if(matrice[nr_reusite]<val_partial)
			{
				matrice[nr_reusite]++;
				return nr_reusite;
			}
			else
			{
				nr_reusite++;
				if(nr_reusite==nr_max)
				{
					cout<<"Something is wrong!!!"<<endl;cout.flush();
					for(int i=0;i<nr_max;i++) matrice[i]=0;
					for(i=0;i<contor;i++) matrice[final[i][0]]++;
					nr_reusite=0;
				}
			}
		}
	}
	else return 0;
}


bool backtracking::solutie(int k)
{
	if(k==Nr_elem)
	{
		int i,j;
		for(i=0;i<contor;i++)
		{
			for(j=0;j<Nr_elem;j++) if(final[i][j]!=final[contor][j]) break;
			if(j==Nr_elem) return false;
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
	while(contor<nr_combinatii)
	{
		backup=init(0);
		first=true;
		final[contor][0]=backup;
		k=1;
		while(k>0)
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
						break;
					}
				}
			}
			if(first!=true)
			{
				k--;
				if(k==0)
				{
					k=1;
					backup=0;
					first=true;
				}
				else
				{
					backup=final[contor][k];
					first=false;
				}
			}
		}
	}
}
