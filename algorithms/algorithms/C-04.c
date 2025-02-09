#include<stdio.h>
#include<stdlib.h>
FILE *output;
int init(int k) {return 0;}
void succesor(int l,int *a,int *v,int nr)
{
	if((*a)<nr-1)
   {
   	(*a)++;
      *v=1;
   }
   else *v=0;
}
void Final(int nr,int *x)
{
	int i,j,**mat,*tmat;
   FILE *fp;
   mat=(int **)calloc(nr,sizeof(int *));
   tmat=(int *)calloc(nr*nr,sizeof(int));
   for(i=0;i<nr;i++)
   {
   	mat[i]=tmat;
      tmat+=nr;
   }
   fp=fopen("dame.dat","w");
   for(i=0;i<nr;i++) mat[x[i]][i]=1;
   for(i=0;i<nr;i++)
   {
	   for(j=0;j<nr;j++) fprintf(fp,"%d ",mat[i][j]);
   	fprintf(fp,"\n");
      fflush(fp);
   }
   fclose(fp);
   free(x);
   free(*mat);
   free(mat);
}
int conditiiinterne(int k,int *x)
{
	int OK,i;
   i=0;
   OK=1;
   while(i<k && OK==1)
   	if(x[k]==x[i] || k-i==abs(x[i]-x[k])) OK=0;
      else i++;
   return OK;
}
void backtracking(int k,int nr,int *x)
{
	int f;
   if(x==NULL) x=(int *)calloc(nr,sizeof(int));
   if(k==nr) Final(nr,x);
   else
   {
   	x[k]=init(k);
		f=1;
      while(f)
      {
      	if(conditiiinterne(k,x))
         {
         	backtracking(k+1,nr,x);
            break;
         }
         else succesor(k,&x[k],&f,nr);
      }
      if(f==0) backtracking(k+1,nr,x);
   }
}

void main(void)
{
	int nr;
   output=fopen("output.dat","w");
   printf("\nCe dimensiune are tabla ?");fflush(stdout);
	scanf("%d",&nr);fflush(stdin);
   backtracking(0,nr,NULL);
   fclose(output);
}
