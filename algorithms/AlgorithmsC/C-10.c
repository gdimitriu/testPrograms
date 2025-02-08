/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and C.
	This is the implementation of tranformation of a digraph from it's
	adiacence matrix to it's adicence list and also implement Merimont.

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
FILE *output;
struct lista
{
	int nod;
   int pondere;
   struct lista *next;
};
struct stiva
{
	int val;
   struct stiva *prec;
};
void push(struct stiva **stack,int val)
{
	//push into stack
	struct stiva *temp;
   temp=(struct stiva *)calloc(1,sizeof(struct stiva));
   temp->val=val;
   temp->prec=NULL;
   if(*stack!=NULL) temp->prec=*stack;
   *stack=temp;
}
int pop(struct stiva **stack)
{
	//pop from stack
	struct stiva *temp;
   int val;
   if(*stack==NULL) return -1;
   temp=*stack;
   *stack=(*stack)->prec;
	val=temp->val;
   free(temp);
   return val;
}
int grad_interior(int nod,int **mat_ad,int nr,int inf)
{
	//interior degree
	int grad,i;
   grad=0;
   for(i=0;i<nr;i++) if(mat_ad[i][nod]!=inf) grad++;
   return grad;
}
int merimont(int **mat_ad,int nr,int inf)
{
	//Merimont algorithm
	struct stiva *stack=NULL;
	int i,j,contor,*gradint,extras;
	gradint=(int *)calloc(nr,sizeof(int));
   //compute interior degre
   for(i=0;i<nr;i++)
   for(j=0;j<nr;j++) if(mat_ad[j][i]!=inf) gradint[i]++;
   contor=nr;
	for(i=0;i<nr;i++) if(gradint[i]==0)
   {
   	push(&stack,i);
      gradint[i]=-1;
   }
   extras=pop(&stack);
   while(extras!=-1)
   {
		contor--;
      for(i=0;i<nr;i++) if(mat_ad[extras][i]!=inf)
      {
      	gradint[i]--;
         if(gradint[i]==0)
         {
         	push(&stack,i);
            gradint[i]=-1;
         }
      }
      extras=pop(&stack);
   }
   if(contor!=0) return 1;
   else return 0;
}
void afisare_lista_adiacente(struct lista **lista_ad,int nr)
{
	//print the adiacence list
	struct lista *temp;
   int i;
   FILE *fp;
   fp=fopen("adiacence_list.dat","w");
   fprintf(fp,"\n");
   for(i=0;i<nr;i++)
   {
   	temp=lista_ad[i];
      fprintf(fp,"nodul %d are vecinii:",i);
   	while(temp!=NULL)
      {
			fprintf(fp,"%d(%d) ",temp->nod,temp->pondere);
         fflush(fp);
         temp=temp->next;
      }
      fprintf(fp,"\n");fflush(fp);
   }
   fclose(fp);
}
struct lista **matrice_lista_adiacente(int **matad,int nr,int inf)
{
	//matrix to adicence list
	int i,j;
	struct lista **ladiacente,*baza,*temp;
	ladiacente=(struct lista **)calloc(nr,sizeof(struct lista *));
	for(i=0;i<nr;i++)
   {
		baza=ladiacente[i]=NULL;
      for(j=0;j<nr;j++) if(matad[i][j]!=inf)
      {
			temp=(struct lista *)calloc(1,sizeof(struct lista));
         temp->nod=j;
         temp->pondere=matad[i][j];
         temp->next=NULL;
      	if(baza==NULL) ladiacente[i]=baza=temp;
         else
         {
         	baza->next=temp;
            baza=temp;
         }
      }
   }
   return ladiacente;
}
int **introducere_matrice(int *nr,int *sum)
{
	//input the adiacence matrix
	int i,j,t,flag;
   int *temp,**mat;
   printf("Cite noduri are digraful\n");fflush(stdout);
   scanf("%d",nr);fflush(stdin);
	mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
	for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
   flag=0;
   printf("Input the arcs, to stop input a negative node.\n");fflush(stdout);
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
int **introducere_matrice1(int *nr,int *sum)
{
	//first static adiacence matrix for testing purpose
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
int **introducere_matrice2(int *nr,int *sum)
{
	//second static adiacence matrix for testing purpose
	int i,j;
   int *temp,**mat;
   *nr=8;
   mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
   for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
   *sum=91;
	mat[0][1]=6;
   mat[0][2]=13;
   mat[0][6]=10;
   mat[1][2]=8;
   mat[1][3]=5;
   mat[2][5]=11;
   mat[2][6]=12;
   mat[4][2]=9;
   mat[4][3]=4;
   mat[4][5]=3;
   mat[5][6]=2;
   mat[7][0]=7;
   mat[7][6]=1;
   for(i=0;i<*nr;i++) for(j=0;j<*nr;j++) if(mat[i][j]==0) mat[i][j]=*sum;
   return mat;
}

int main(void)
{
	int **mat,nr,i,j,inf=0,temp,flag;
   struct lista **lista_ad;
   output=fopen("output.dat","w");
   mat=introducere_matrice2(&nr,&inf);
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) fprintf(output,"%d ",mat[i][j]);
      fprintf(output,"\n");fflush(output);
   }
   lista_ad=matrice_lista_adiacente(mat,nr,inf);
   afisare_lista_adiacente(lista_ad,nr);
	flag=merimont(mat,nr,inf);
   if(flag==0) fprintf(output,"In this digraf isn't loops\n");
   else fprintf(output,"In this digraf is some loops\n");
   fflush(output);
   free(*mat);
   free(mat);
   fclose(output);
   return 0;
}
