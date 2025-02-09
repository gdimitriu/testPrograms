#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int comparatie(char *in,char *cuvint)
{
	int i,j,k;
	int dim;
	char *temp;
	dim=strlen(cuvint)+1;
	temp=(char *)calloc(dim,sizeof(char));
	temp[dim-1]='\0';
	for(j=0;j<strlen(in);j++)
	{
		for(i=0;i<dim-1;i++) temp[i]=in[i+j];
		if(strcmp(temp,cuvint)==0) return j;
	}
	return -1;
}
int main()
{
	char data[]="taste de cautare";
	char cuv[]="te de";
	printf("rezultat %d\n",comparatie(data,cuv));
}