#include<stdio.h>
#include<stdlib.h>

struct nod
{
	int info;
	struct nod *fii[2];
} *temp,*baza;

void introducere(struct nod **temp1,int *info)
{
	if(*temp1==NULL) //introducem in arbore
	{
		temp=(struct nod *)calloc(1,sizeof(struct nod));
		temp->fii[0]=NULL;
		temp->fii[1]=NULL;
		temp->info=*info;
		*temp1=temp;
	}
	else
	{
		if((*temp1)->info<*info) introducere(&(*temp1)->fii[1],info);
		else introducere(&(*temp1)->fii[0],info);
	}
}
void SRD(struct nod *temp1)
{
	if(temp1->fii[0]!=NULL) SRD(temp1->fii[0]);
	printf("%d ",temp1->info);fflush(stdout);
	if(temp1->fii[1]!=NULL) SRD(temp1->fii[1]);
}

void main(void)
{
#define NR 10
	int numere[NR]={10,-1,3,6,2,-5,120,-2,5,0};
	int i;
	baza=NULL;
	printf("\n");fflush(stdout);
	for(i=0;i<NR;i++)
		introducere(&baza,&numere[i]);
	SRD(baza);
}
