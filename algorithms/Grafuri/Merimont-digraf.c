/* program pentru determinarea daca un digraf este ciclic sau aciclic cu ajutorul lui Merimont */
/* realizat de catre Dimitriu Gabriel gr 21 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *output;
//pentru lucrul cu stiva
struct stiva
{
	int val;
   struct stiva *prec;
};
void push(struct stiva **stack,int val)
{
	struct stiva *temp;
   temp=(struct stiva *)calloc(1,sizeof(struct stiva));
   temp->val=val;
   temp->prec=NULL;
   if(*stack!=NULL) temp->prec=*stack;
   *stack=temp;
}
int pop(struct stiva **stack)
{
	struct stiva *temp;
   int val;
   if(*stack==NULL) return -1;
   temp=*stack;
   *stack=(*stack)->prec;
	val=temp->val;
   free(temp);
   return val;
}
//algoritmul lui merimont
int merimont(int **mat_ad,int nr,int inf)
{
	struct stiva *stack=NULL;
	int i,j,contor,*gradint,extras;
	gradint=(int *)calloc(nr,sizeof(int));
   //calculeaza gradul interior
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
//introducere digraf de la tastatura
int **introducere_matrice(int *nr,int *sum)
{
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
   printf("Introduceti arcele, pentru oprire introduceti un nod negativ\n");fflush(stdout);
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
//graf de test
int **introducere_matrice1(int *nr,int *sum)
{
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
//graf de test
int **introducere_matrice2(int *nr,int *sum)
{
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
//functia main
int main(void)
{
	int **mat,nr,i,j,inf=0,temp,flag;
   output=fopen("output.dat","w");
   mat=introducere_matrice2(&nr,&inf);
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) fprintf(output,"%d ",mat[i][j]);
      fprintf(output,"\n");fflush(output);
   }
	flag=merimont(mat,nr,inf);
   if(flag==0) fprintf(output,"Acest digraf este aciclic\n");
   else fprintf(output,"Acest digraf este ciclic\n");
   fflush(output);
   free(*mat);
   free(mat);
   fclose(output);
   return 0;
}
