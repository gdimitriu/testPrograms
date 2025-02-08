/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and C.
	This is the implementation of Roy Floyd and Diskstra for a digraf 
	given by it's adiadicence matrix.

    Algorithms and C is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and C is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and C; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int **introducere(int *nr,int *sum)
{
	//input the adiacence matrix
	int i,j,t,flag;
   int *temp,**mat;
   printf("Input the number of nodes for digraph\n");fflush(stdout);
   scanf("%d",nr);fflush(stdin);
	mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
	for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
   flag=0;
   printf("Input the arcs, to stop input a negative node\n");fflush(stdout);
	while(flag==0)
   {
   	scanf("%d %d %d",&i,&j,&t);
      if(i<0 || j<0) break;
      (*sum)+=t;
      mat[i][j]=t;
   }
   for(i=0;i<*nr;i++) for(j=0;j<*nr;j++) if(mat[i][j]==0) mat[i][j]=*sum;
   return mat;
}
int **introducere1(int *nr,int *sum)
{
	//statical input
	int i,j;
   int *temp,**mat;
   *nr=6;
   mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
   for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
   *sum=89;
	mat[0][1]=5;
   mat[0][4]=9;
   mat[0][5]=8;
   mat[1][4]=7;
   mat[2][0]=5;
   mat[2][1]=6;
   mat[2][5]=15;
   mat[3][1]=7;
   mat[3][2]=6;
   mat[3][5]=12;
   mat[4][3]=3;
   mat[5][4]=6;
   for(i=0;i<*nr;i++) for(j=0;j<*nr;j++) if(mat[i][j]==0) mat[i][j]=*sum;
   return mat;
}
void roy_floyd(int **mat,int nr,int inf)
{
	//implementation of Roy-Floyd
	int **wmat,*temp,i,j,k,l,m,tmp;
   FILE *fp;
   wmat=(int **)calloc(nr,sizeof(int *));
   temp=(int *)calloc(nr*nr,sizeof(int));
   for(i=0;i<nr;i++)
   {
   	wmat[i]=temp;
      temp+=nr;
   }
   memcpy(&wmat[0][0],&mat[0][0],nr*nr*sizeof(int));
   fp=fopen("roy_floyd.dat","w");
   for(i=0;i<nr;i++)
   for(j=0;j<nr;j++)
   {
   	if(wmat[j][i]!=inf)
      	for(k=0;k<nr;k++)
         {
         	tmp=wmat[j][i]+wmat[i][k];
            if(wmat[j][k]>tmp) wmat[j][k]=tmp;
            if(j==2 && k==3) fprintf(fp,"%d ",wmat[j][k]);
         }
   }
   fprintf(fp,"Matricea drumurilor minime finala\n");fflush(fp);
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) fprintf(fp,"%d ",wmat[i][j]);
      fprintf(fp,"\n");fflush(fp);
   }
   fclose(fp);
   free(*wmat);
   free(wmat);
}
void diskstra(int u0,int **mat,int nr,int inf)
{
	//implementation of Disckstra
	int *L,*ind,i,j,*pred,min,cmin,k,tmp;
   FILE *fp;
   L=(int *)malloc(nr*sizeof(int));
   for(i=0;i<nr;i++) L[i]=inf;
   ind=(int *)calloc(nr,sizeof(int));
   pred=(int *)calloc(nr,sizeof(int));
   L[u0]=0;
   ind[u0]=1;
   i=0;
   pred[u0]=-1;
   while(i<nr)
   {
   	for(j=0;j<nr;j++)
      {
      	if(ind[j]==0)
         	for(k=0;k<nr;k++)
            {
            	if(mat[k][j]!=inf)
               {
               	tmp=L[k]+mat[k][j];
                  if(L[j]>tmp)
                  {
                  	L[j]=tmp;
                     pred[j]=k;
                  }
               }
            }
      }
      min=inf;
      cmin=0;
      for(j=0;j<nr;j++) if((!ind[j]) && (min>L[j]))
      {
      	min=L[j];
         cmin=j;
      }
      ind[cmin]=1;
      i++;
   }
   fp=fopen("diskstra.dat","a");
   fprintf(fp,"distance from %d\n",u0);
   for(i=0;i<nr;i++) fprintf(fp,"%d ",L[i]);
   fprintf(fp,"\n");
   fflush(fp);
   fclose(fp);
   free(ind);
   free(L);
   free(pred);
}
int main(void)
{
	int **mat,nr,i,j,inf=0,temp;
   mat=introducere1(&nr,&inf);
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) printf("%d ",mat[i][j]);
      printf("\n");fflush(stdout);
   }
   roy_floyd(mat,nr,inf);
   for(i=0;i<nr;i++) diskstra(i,mat,nr,inf);
   free(*mat);
   free(mat);
   return 0;
}
