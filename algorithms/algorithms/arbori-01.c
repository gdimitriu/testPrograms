#include<stdio.h>
#include<stdlib.h>
struct element
{
	int info;
	struct element *fii[2];
};
struct element *virf1,*virf2,*temp,*temp1,*reuvirf,*intvirf,*diffvirf;
struct stiva
{
	int info;
	struct stiva *legatura;
};
struct stiva *tempstiva,*stiva1,*stiva2;
int eroare=0;
void push(int info,struct stiva **virf)
{
	tempstiva=(struct stiva *)calloc(1,sizeof(struct stiva));
	tempstiva->info=info;
	if(*virf==NULL)
	{
		*virf=tempstiva;
		tempstiva->legatura=NULL;
	}
	else
	{
		tempstiva->legatura=*virf;
		*virf=tempstiva;
	}
}
int pop(struct stiva **virf)
{
	int ret;
	eroare=0;
	if(*virf==NULL)
	{
		eroare=1;
		return 0;
	}
	ret=(*virf)->info;
	tempstiva=*virf;
	*virf=(*virf)->legatura;
	free(tempstiva);
	return ret;
}
int introducere(int info,struct element **virf)
{
	int flag;
	int test;
	temp=(struct element *)calloc(1,sizeof(struct element));
	temp->info=info;
	if(*virf==NULL)
	{
		temp->fii[0]=NULL;
		temp->fii[1]=NULL;
		*virf=temp;
	}
	else
	{
		temp->fii[0]=NULL;
		temp->fii[1]=NULL;
		temp1=*virf;
		flag=0;
		while(flag==0)
		{
			if(temp1->info==temp->info)
			{
				free(temp);
				return 1;
			}
			test=temp1->info<temp->info;
			if(temp1->fii[test]==NULL)
			{
				temp1->fii[test]=temp;
				flag=1;
			}
			else 
			{
				temp1=temp1->fii[test];
			}
		}
	}
	return 0;
}
void RSD(struct element **virf,struct stiva **stack)
{
	struct element *virfint;
	virfint=*virf;
	if(virfint==NULL) return;
	push(virfint->info,stack);
	if(virfint->fii[0]!=NULL) RSD(&(virfint->fii[0]),stack);
	if(virfint->fii[1]!=NULL) RSD(&(virfint->fii[1]),stack);
}
void reuniune(struct element **out,struct element **in0,struct element **in1)
{
	int val;
	stiva1=NULL;
	RSD(in0,&stiva1);
	while(eroare==0)
	{
		val=pop(&stiva1);
		if(val==0 && eroare==1) break;
		else introducere(val,out);
	}
	eroare=0;
	stiva1=NULL;
	RSD(in1,&stiva1);
	while(eroare==0)
	{
		val=pop(&stiva1);
		if(val==0 && eroare==1) break;
		else introducere(val,out);
	}
}

int cautare(int info,struct element **virf)
{
	int flag;
	int test;
	temp1=*virf;
	if(*virf==NULL)	return 0;
	else
	{
		flag=0;
		while(flag==0)
		{
			if(temp1->info==info) return 1;
			else
			{
				test=temp1->info<info;
				if(temp1->fii[test]==NULL) return 0;
				else temp1=temp1->fii[test];
			}
		}
	}
}

void intersectie(struct element **out,struct element **in0,struct element **in1)
{
	int val;
	stiva1=NULL;
	RSD(in1,&stiva1);
	eroare=0;
	while(eroare==0)
	{
		val=pop(&stiva1);
		if(val==0 && eroare==1) break;
		else if(cautare(val,in0)==1) introducere(val,out);
	}
}

void diferenta(struct element **out,struct element **in0,struct element **in1)
{
	int val;
	stiva1=NULL;
	RSD(in0,&stiva1);
	eroare=0;
	while(eroare==0)
	{
		val=pop(&stiva1);
		if(val==0 && eroare==1) break;
		else if(cautare(val,in1)==0) introducere(val,out);
	}
}

void SRD_print(struct element **virf)
{
	struct element *virfint;
	virfint=*virf;
	if(virfint==NULL) return;
	if(virfint->fii[0]!=NULL) SRD_print(&(virfint->fii[0]));
		printf("%d ",virfint->info);fflush(stdout);
	if(virfint->fii[1]!=NULL) SRD_print(&(virfint->fii[1]));
}
int main()
{
	int data1[10]={10,12,2,3,20,45,15,18,6,9};
	int data2[10]={12,4,5,3,13,45,25,8,16,19};
	int i;
	virf1=NULL;
	virf2=NULL;
	reuvirf=NULL;
	intvirf=NULL;
	diffvirf=NULL;
	for(i=0;i<10;i++)
	{
		introducere(data1[i],&virf1);
		introducere(data2[i],&virf2);
	}
	printf("\nPrimul arbore\n");fflush(stdout);
	SRD_print(&virf1);
	printf("\nAl doilea arbore\n");fflush(stdout);
	SRD_print(&virf2);
	reuniune(&reuvirf,&virf1,&virf2);
	printf("\nReuniuniune\n");fflush(stdout);
	SRD_print(&reuvirf);
	printf("\nIntersectie\n");fflush(stdout);
	intersectie(&intvirf,&virf1,&virf2);
	SRD_print(&intvirf);
	printf("\nDiferenta\n");fflush(stdout);
	diferenta(&diffvirf,&virf1,&virf2);
	SRD_print(&diffvirf);
	printf("\n");fflush(stdout);
}
