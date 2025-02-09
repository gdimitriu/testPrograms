#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct nod
{
	int info;
	struct nod *fii[2];
};
struct nod *baza,*temp,*temp1;
int adaugare(int info)
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
int SRD(struct nod *test)
{
	if(test->fii[0]!=NULL) SRD(test->fii[0]);
	printf("%d ",test->info);fflush(stdout);
	if(test->fii[1]!=NULL) SRD(test->fii[1]);
}
int inaltime(struct nod *test)
{
	int nr1=0,nr2=0;
	if(test->fii[0]!=NULL) nr1+=inaltime(test->fii[0]);
	if(test->fii[1]!=NULL) nr2+=inaltime(test->fii[1]);
	if(nr1<nr2) return nr2+1;
	else return nr1+1;
}
int adaug1(struct nod *intr)
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
int stergere(int info)
{
	struct nod *temp2,*temp3;
	int test1,test2=3;
	if(baza==NULL) return -1;
	else
	{
		temp2=baza;
		temp3=baza;
		while(1)
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
	}
}
int main()
{
	int data[15]={10,4,2,3,5,13,20,-19,-4,-3,6,14,8,-6,0};
	int i;
	baza=NULL;
	for(i=0;i<15;i++) adaugare(data[i]);
	SRD(baza);
	printf("\nInaltimea arborelui este %d\n",inaltime(baza));fflush(stdout);
	stergere(2);
	SRD(baza);
	printf("\n");fflush(stdout);
}