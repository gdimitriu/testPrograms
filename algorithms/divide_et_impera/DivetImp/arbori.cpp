// arbori.cpp: implementation of the arbori class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "arbori.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

arbori::arbori()
{
	fp.open("arbori.dat",ios::out);
	char file[32];
	cout<<"Introduceti numele fisierului in care aveti elementele ";
	cin>>file;
	ifstream fpi(file,ios::in);
	int i;
	int nr;
	int temp;
	baza=NULL;
	cout<<"Introduceti cite elemente aveti ";
	cin>>nr;
	for(i=0;i<nr;i++)
	{
		fpi>>temp;
		adaugare(temp);
	}
	fpi.close();
	fp<<endl<<"Parcurgere SRD"<<endl;
	SRD(baza);
	fp<<endl<<"Parcurgere DRS"<<endl;
	DRS(baza);
	cout<<"Introduceti cite elemente aveti de sters ";
	cin>>nr;
	cout<<"Introduceti pe rind elementele de sters ";
	for(i=0;i<nr;i++)
	{
		cin>>temp;
		stergere(temp);
	}
	fp<<endl<<"Dupa stergerea elementelor"<<endl;fp.flush();
	SRD(baza);
}

arbori::~arbori()
{
	fp.close();
}

int arbori::adaugare(int info)
{
	int test;
	temp=(struct nod *)calloc(1,sizeof(struct nod));
	temp->info=info;
	temp->fii[0]=NULL;
	temp->fii[1]=NULL;
	if(baza==NULL)
	{
		baza=temp;
		return 0;
	}
	else
	{
		temp1=baza;
		while(1)
		{
			if(temp->info==temp1->info)
			{
				free(temp);
				return 1;
			}
			else
			{
				test=temp->info>temp1->info;
				if(temp1->fii[test]==NULL)
				{
					temp1->fii[test]=temp;
					return 0;
				}
				else temp1=temp1->fii[test];
			}
		}
	}
}

void arbori::SRD(nod *test)
{
	if(test->fii[0]!=NULL) SRD(test->fii[0]);
	fp<<test->info<<' ';fp.flush();
	if(test->fii[1]!=NULL) SRD(test->fii[1]);
}

void arbori::DRS(nod *test)
{
	if(test->fii[1]!=NULL) DRS(test->fii[1]);
	fp<<test->info<<' ';fp.flush();
	if(test->fii[0]!=NULL) DRS(test->fii[0]);
}

int arbori::adaug1(nod *intr)
{
	int test;
	if(baza==NULL) return -1;
	else
	{
		temp1=baza;
		while(1)
		{
			test=intr->info>temp1->info;
			if(temp1->fii[test]==NULL)
			{
				temp1->fii[test]=intr;
				return 0;
			}
			else temp1=temp1->fii[test];
		}
	}
}

int arbori::stergere(int info)
{
	struct nod *temp2,*temp3;
	int test1,test2=3;
	if(baza==NULL) return -1;
	else
	{
		temp2=baza;
		temp3=baza;
		while(temp2!=NULL)
		{
			test1=info>temp2->info;
			if(test2==3) test2=test1;
			if(info==temp2->info)
			{
				temp3->fii[test2]=NULL;
				adaug1(temp2->fii[1]);
				adaug1(temp2->fii[0]);
				free(temp2);
				return 1;
			}
			else
			{
				temp3=temp2;
				test2=test1;
				temp2=temp2->fii[test1];
			}
		}
		fp<<endl<<"Elementul "<<info<<" nu a fost gasit"<<endl;
		return -1;
	}
}
