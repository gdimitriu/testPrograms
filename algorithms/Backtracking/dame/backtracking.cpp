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
	cout<<"Introduceti numarul de dame=";
	cin>>nr_dame;
	final=new int[nr_dame];
	for(int i=0;i<nr_dame;i++) final[i]=0;
	calcul(0);
}

backtracking::backtracking(int nr)
{
	nr_dame=nr;
	final=new int[nr_dame];
  	for(int i=0;i<nr_dame;i++) final[i]=0;
	calcul(0);
}

backtracking::~backtracking()
{
	delete final;
}

bool backtracking::succesor(int *a,int k)
{
	if((*a)<nr_dame-1)
	{
   		(*a)++;
		return true;
	}
	else return false;
}

bool backtracking::conditii_interne(int k)
{
	int i;
	bool OK;
	i=0;
	OK=true;
	while(i<k && OK)
   		if((backup==final[i]) || (abs(k-i)==abs(final[i]-backup))) OK=false;
		else i++;
	return OK;
}

void backtracking::calcul(int k)
{
	bool found,inainte;
	k=0;
	backup=init(0);
	while(k>=0)
	{
		while(1)
		{
			found=succesor(&backup,k);
			inainte=false;
			if(found) inainte=conditii_interne(k);
			if(inainte) final[k]=backup;
			if(inainte || !found) break;
		}
		if(found)
		{
			if(solutie(k)) 
			{
				Final();
			}
			else
			{
				k++;
				backup=init(k);
			}
		}
		else
		{
			k--;
			backup=final[k];
		}
	}
}

int backtracking::init(int k)
{
	return -1;
}

void backtracking::Final()
{
	int i,j,**mat,*tmat;
	cout<<"Saving data\n";
	ofstream fp("dame.dat",ios::app);
	if(!fp)
	{
		cout<<"Eroare la deschidere fisier";
		exit(-1);
	}
	mat=(int **)calloc(nr_dame,sizeof(int *));
	tmat=(int *)calloc(nr_dame*nr_dame,sizeof(int));
	for(i=0;i<nr_dame;i++)
	{
   		mat[i]=tmat;
		tmat+=nr_dame;
	}
	for(i=0;i<nr_dame;i++) mat[i][final[i]]=1;
	for(i=0;i<nr_dame;i++)
	{
		for(j=0;j<nr_dame;j++) fp<<mat[i][j]<<' ';
   		fp<<endl;
	}
	fp<<endl;
	free(*mat);
	free(mat);
	fp.close();
}

bool backtracking::solutie(int k)
{
	if(k==nr_dame-1) return true;
	else return false;
}
