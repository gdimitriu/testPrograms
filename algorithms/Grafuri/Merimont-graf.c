/* program pentru determinarea ciclicitatii grafurilor cu ajutorul lui Merimont */
/* realizat de catre Dimitriu Gabriel gr 21 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *output;
/* functiile pentru lucru cu stiva */
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
//functia pentru algoritmul lui merimont
int merimont(int **mat_ad,int nr)
{
	struct stiva *stack=NULL;
	int i,j,contor,*grad,extras;
	grad=(int *)calloc(nr,sizeof(int));
   //calculez gradele
   for(i=0;i<nr;i++)
   for(j=0;j<nr;j++) if(mat_ad[j][i]==1) grad[i]++;
   contor=nr;
	for(i=0;i<nr;i++) if(grad[i]==1)
   {
   	push(&stack,i);
      grad[i]--;
   }
   extras=pop(&stack);
   while(extras!=-1)
   {
		contor--;
      for(i=0;i<nr;i++) if(mat_ad[extras][i]==1)
      {
      	grad[i]--;
         if(grad[i]==1)
         {
         	push(&stack,i);
            grad[i]--;
         }
      }
      extras=pop(&stack);
   }
   if(contor!=0) return 1;
   else return 0;
}
//functia pentru introducre matrice de la tastatura
int **introducere_matrice(int *nr)
{
	int i,j,flag;
   int *temp,**mat;
   printf("Cite noduri are graful\n");fflush(stdout);
   scanf("%d",nr);fflush(stdin);
	mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
	for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
   flag=0;
   printf("Introduceti muchiile, pentru oprire introduceti un nod negativ\n");fflush(stdout);
	while(flag==0)
   {
   	scanf("%d %d",&i,&j);
      if(i<0 || j<0) break;
      mat[i][j]=mat[j][i]=1;
   }
   return mat;
}
//graf de test ciclic
int **introducere_matrice1(int *nr)
{
	int i;
   int *temp,**mat;
   *nr=12;
   mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
   for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
	mat[0][1]=mat[1][0]=1;
   mat[0][2]=mat[2][0]=1;
   mat[0][3]=mat[3][0]=1;
   mat[0][5]=mat[5][0]=1;
   mat[5][6]=mat[6][5]=1;
   mat[5][7]=mat[7][5]=1;
   mat[5][8]=mat[8][5]=1;
   mat[7][8]=mat[8][7]=1;
   mat[2][4]=mat[4][2]=1;
   mat[3][4]=mat[4][3]=1;
   mat[2][9]=mat[9][2]=1;
   mat[2][10]=mat[10][2]=1;
   mat[10][11]=mat[11][10]=1;
   mat[9][11]=mat[11][9]=1;
   return mat;
}
//graf de test aciclic
int **introducere_matrice2(int *nr)
{
	int i;
   int *temp,**mat;
   *nr=12;
   mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
   for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
  	mat[0][1]=mat[1][0]=1;
   mat[0][2]=mat[2][0]=1;
   mat[0][3]=mat[3][0]=1;
   mat[0][5]=mat[5][0]=1;
   mat[5][6]=mat[6][5]=1;
   mat[5][7]=mat[7][5]=1;
   mat[5][8]=mat[8][5]=1;
   mat[3][4]=mat[4][3]=1;
   mat[2][9]=mat[9][2]=1;
   mat[2][10]=mat[10][2]=1;
   mat[9][11]=mat[11][9]=1;
   return mat;
}
//functia main
int main(void)
{
	int **mat,nr,i,j,flag;
   output=fopen("output.dat","w");
   mat=introducere_matrice(&nr); //aici se schimba pentru diferite tipuri de grafuri de testare
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) fprintf(output,"%d ",mat[i][j]);
      fprintf(output,"\n");fflush(output);
   }
	flag=merimont(mat,nr);
   if(flag==0) fprintf(output,"Acest graf este aciclic\n");
   else fprintf(output,"Acest graf este ciclic\n");
   fflush(output);
   free(*mat);
   free(mat);
   fclose(output);
   return 0;
}
