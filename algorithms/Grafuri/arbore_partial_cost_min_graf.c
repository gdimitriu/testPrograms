/* program pentru determinarea unui arbore partial de cost minim intr-un graf*/
/* realizat de catre Dimitriu Gabriel gr 21 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *output;
struct element
{
	int i;
   int j;
   int val;
   struct element *next;
};
//functie pentru crearea cozii muchiilor
struct element *creare_coada(int nr,int **mat)
{
	struct element *nod,*lista,*curent,*temp;
   int i,j;
   lista=NULL;
   for(i=0;i<nr;i++)
    for(j=i;j<nr;j++)
    {
		if(mat[i][j]!=0)
      {
      	if(lista==NULL)
         {
         	lista=(struct element *)calloc(1,sizeof(struct element));
			   lista->next=NULL;
            lista->i=i;
            lista->j=j;
            lista->val=mat[i][j];
         }
         else
         {
         	nod=(struct element *)calloc(1,sizeof(struct element));
            nod->i=i;
            nod->j=j;
            nod->val=mat[i][j];
            curent=lista;
            temp=NULL;
            nod->next=NULL;
            while(curent!=NULL)
            {
               if(nod->val<=curent->val)
               {
               	if(temp==NULL)
                  {
	               	nod->next=lista;
   	               lista=nod;
                     break;
                  }
                  else
                  {
                  	temp->next=nod;
                     nod->next=curent;
                     break;
                  }
               }
               else
               {
						temp=curent;
                  curent=curent->next;
               }
            }
            if(curent==NULL) temp->next=nod;
         }
      }
    }
	return lista;
}
//functia pentru scoaterea unui element din coada
struct element *scoatere(struct element *coada,int *i,int *j,int *val)
{
	struct element *lista;
   *i=coada->i;
   *j=coada->j;
   *val=coada->val;
	lista=coada->next;
   free(coada);
   return lista;
}
//functia pentru gerenarea arborelui partial de cost minin
int arbore(int nr,int **mat)
{
	int *L,i,j,val;
   int cost;
   struct element *coada;
   L=(int *)calloc(nr,sizeof(int));
   for(i=0;i<nr;i++) L[i]=i;
	coada=creare_coada(nr,mat);
   cost=0;
   while(coada!=NULL)
   {
		coada=scoatere(coada,&i,&j,&val);
      if(L[i]==L[j]) mat[i][j]=mat[j][i]=0; //sterg muchia
      else
      {
         cost+=val;
         fprintf(output,"%d,%d=%d ",i,j,val);fflush(output);
         val=L[j];
      	L[j]=L[i];
         for(j=0;j<nr;j++) if(L[j]==val) L[j]=L[i];
      }
   }
   free(L);
   return cost;
}
//functia pentru introducre matrice de la tastatura
int **introducere_matrice(int *nr)
{
	int i,j,flag,val;
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
   	scanf("%d %d %val",&i,&j,&val);
      if(i<0 || j<0) break;
      mat[i][j]=mat[j][i]=val;
   }
   return mat;
}
//graf de test neconex
int **introducere_matrice1(int *nr)
{
	int i;
   int *temp,**mat;
   *nr=16;
   mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
   for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
	mat[0][6]=mat[6][0]=6;
   mat[6][7]=mat[7][6]=2;
   mat[0][7]=mat[7][0]=5;
	mat[0][1]=mat[1][0]=1;
   mat[1][9]=mat[9][1]=5;
   mat[9][8]=mat[8][9]=1;
	mat[8][1]=mat[1][8]=6;
   mat[1][2]=mat[2][1]=4;
	mat[2][3]=mat[3][2]=3;
   mat[3][10]=mat[10][3]=5;
   mat[10][11]=mat[11][10]=2;
   mat[11][3]=mat[3][11]=6;
   mat[3][4]=mat[4][3]=4;
   mat[4][12]=mat[12][4]=5;
   mat[12][13]=mat[13][12]=1;
   mat[13][4]=mat[4][13]=6;
   mat[4][5]=mat[5][4]=4;
   mat[5][14]=mat[14][5]=5;
   mat[14][15]=mat[15][14]=3;
   mat[15][5]=mat[5][15]=6;
   mat[0][5]=mat[5][0]=3;
   return mat;
}
//functia main
int main(void)
{
	int **mat,nr,i,j,cost;
   output=fopen("output.dat","w");
   mat=introducere_matrice1(&nr); //aici se schimba pentru diferite tipuri de grafuri de testare
   fprintf(output,"Matricea de adiacenta asociata grafului este:\n");
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) fprintf(output,"%d ",mat[i][j]);
      fprintf(output,"\n");fflush(output);
   }
   fflush(output);
   cost=arbore(nr,mat);
	fprintf(output,"\n Matricea de adiacenta asociata arborelui de cost minim cu costul %d este:\n",cost);
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) fprintf(output,"%d ",mat[i][j]);
      fprintf(output,"\n");fflush(output);
   }
   fflush(output);
   free(*mat);
   free(mat);
   fclose(output);
   return 0;
}