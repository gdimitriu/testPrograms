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
	cout<<"Introduceti dimensiunea tablei=";cout.flush();
	cin>>nr_dame;
	cout<<"Introduceti pragul ";cout.flush();
	cin>>k0;
	matrice=new int[nr_dame];
	final=new int[nr_dame];
	for(int i=0;i<nr_dame;i++)
	{
		final[i]=nr_dame;
		matrice[i]=0;
	}
	//m_p=1; //pentru prima problema
	m_p=k0; //pentru a doua problema
	ofstream fp("dame.dat",ios::trunc);
	fp.close();
	fp.flush();
	calcul(0);
}

backtracking::backtracking(int nr,int nr1)
{
	nr_dame=nr;
	k0=nr1;
	matrice=new int[nr_dame];
	final=new int[nr_dame];
  	for(int i=0;i<nr_dame;i++)
	{
		final[i]=nr_dame;
		matrice[i]=0;
	}
	//m_p=1;//pentru prima problema
	m_p=k0; //pentru a doua problema
	ofstream fp("dame.dat",ios::trunc);
	fp.close();
	fp.flush();
	calcul(0);
}

backtracking::~backtracking()
{
	delete matrice;
	delete final;
}

bool backtracking::succesor(int *a,int k)
{
	if(k==0 && first) return true;
	if((*a)<nr_dame)
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
	while(i<nr_dame && OK)
	{
		if(final[i]==nr_dame || i==k) i++;
		else if((matrice[k]==final[i]) || (abs(k-i)==abs(final[i]-matrice[k]))) OK=false;
			else i++;
	}
	return OK;
}


int backtracking::init(int k)
{
	return 0;
}

void backtracking::Final()
{
	int i,j,**mat,*tmat;
	cout<<"Saving data\n";cout.flush();
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
	for(i=0;i<nr_dame;i++) if(final[i]!=nr_dame) mat[i][final[i]]=1;
	fp<<"Solutia pentru "<<m_p<<"dame"<<endl;fp.flush();
	for(i=0;i<nr_dame;i++)
	{
		for(j=0;j<nr_dame;j++) fp<<mat[i][j]<<' ';
		fp<<final[i]<<' ';
   		fp<<endl;
	}
	fp.flush();
	fp.close();
	fp.flush();
	free(*mat);
	free(mat);
}

bool backtracking::solutie(int k)
{
	int nrdame;
	nrdame=0;
	for(int i=0;i<nr_dame;i++) if(final[i]!=nr_dame) nrdame++;
	if(nrdame==m_p) return true;
	else if(nrdame<m_p) return false;
	else
	{
		cout<<"Ciudat!!";
		cout.flush();
		return false;
	}
}

void backtracking::calcul(int k)
{
	bool found,inainte;
	//while(m_p<=k0) //pentru prima problema
	while(m_p>=k0 && m_p<nr_dame) //pentru a doua problema
	{
		k=0;
		for(int i=0;i<nr_dame;i++)
		{
			final[i]=nr_dame;
			matrice[i]=0;
		}
		first=true;
		matrice[0]=init(0);
		cout<<m_p<<' ';cout.flush();
		while(k>=0)
		{
			while(1)
			{
				found=succesor(&matrice[k],k);
				first=false;
				inainte=false;
				if(found) inainte=conditii_interne(k);
				if(inainte) final[k]=matrice[k];
				if(inainte || !found) break;
			}
			if(found)
			{
				if(solutie(k)) 
				{
					Final();
					m_p++;
					break;
				}
				else
				{
					k++;
					matrice[k]=init(k);
				}
			}
			else
			{
				matrice[k]=final[k];
				k--;
			}
		}
	}
}
