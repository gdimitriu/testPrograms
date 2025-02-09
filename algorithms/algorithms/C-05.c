#include<stdio.h>
#include<stdlib.h>
FILE *output;
int init(int k) {return 0;}
void succesor(int l,int *a,int *v,int color)
{
	if((*a)<color)
   {
   	(*a)++;
      *v=1;
   }
   else *v=0;
}
void Final(int nr,int *x)
{
   FILE *fp;
   int i;
   fp=fopen("country.dat","w");
	for(i=0;i<nr;i++) fprintf(fp,"country %d=%d\n",i,x[i]);
   fclose(fp);
   free(x);
}
int conditiiinterne(int k,int *x,int **mat)
{
	int OK,i;
   OK=1;
   i=0;
   while(i<k && OK==1)
   {
   	if(mat[i][k]==1 && x[k]==x[i]) OK=0;
      else i++;
   }
   return OK;
}
void backtracking(int k,int nr,int *x,int **mat,int color)
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
      	if(conditiiinterne(k,x,mat))
         {
         	backtracking(k+1,nr,x,mat,color);
            break;
         }
         else succesor(k,&x[k],&f,color);
      }
      if(f==0) backtracking(k+1,nr,x,mat,color);
   }
}
void introducere(int ***mat,int *nr)
{
	int *tmat,i;
	printf("\nCe dimensiune are problema ?");fflush(stdout);
	scanf("%d",nr);fflush(stdin);
   *mat=(int **)calloc(*nr,sizeof(int *));
   tmat=(int *)calloc((*nr)*(*nr),sizeof(int));
   for(i=0;i<*nr;i++)
   {
   	*mat[i]=tmat;
      tmat+=*nr;
   }
}
int  **introducere6(int *nr)
{
	int **mat,*tmat,i;
	*nr=6;
	mat=(int **)calloc(*nr,sizeof(int *));
   tmat=(int *)calloc((*nr)*(*nr),sizeof(int));
   for(i=0;i<*nr;i++)
   {
   	mat[i]=tmat;
      tmat+=*nr;
   }
	mat[0][1]=1;
	mat[0][2]=1;
   mat[0][4]=1;
   mat[0][5]=1;
   mat[1][0]=1;
   mat[1][2]=1;
   mat[1][3]=1;
   mat[1][4]=1;
   mat[2][0]=1;
   mat[2][1]=1;
   mat[2][3]=1;
   mat[3][1]=1;
   mat[3][2]=1;
   mat[3][4]=1;
   mat[4][0]=1;
   mat[4][1]=1;
   mat[4][3]=1;
   mat[4][5]=1;
   mat[5][0]=1;
   mat[5][4]=1;
   return mat;
}
void main(void)
{
	int nr,**mat,culori;
   int i,j;
   output=fopen("output.dat","w");
   printf("Introduceti cite culori aveti >=4\n");fflush(stdout);
   scanf("%d",&culori);fflush(stdin);
   mat=introducere6(&nr);
   backtracking(0,nr,NULL,mat,culori);
   fclose(output);
   free(*mat);
   free(mat);
}
