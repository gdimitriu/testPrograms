/* program pentru determinarea unei componente conexe intr-un graf*/
/* realizat de catre Dimitriu Gabriel Gr 21 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *output;
int conexitate(int **mat1,int nr)
{
	int *y,*y1;
	int nod,i,j,k,rezultat;
   int contor,temp;
   int nr_muchii[2];
   int **mat,*temporar;
	mat=(int **)calloc(nr,sizeof(int *));
   temporar=(int *)calloc(nr*nr,sizeof(int));
	for(i=0;i<nr;i++)
   {
   	mat[i]=temporar;
      temporar+=(nr);
   }
   for(i=0;i<nr;i++) for(j=0;j<nr;j++) mat[i][j]=mat1[i][j];
   y=(int *)calloc(nr,sizeof(int));
   y1=(int *)calloc(nr,sizeof(int));
	for(i=0;i<nr;i++) {y[i]=-1;y1[i]=-1;}
   printf("Introduceti nodul de start:");fflush(stdout);
   scanf("%d",&nod);fflush(stdin);
   contor=0;
   nr_muchii[0]=0;
	for(i=0;i<nr;i++) for(j=0;j<nr;j++) if(mat[i][j]==1) nr_muchii[0]++;
   nr_muchii[1]=nr_muchii[0];
   y[contor]=nod;y1[contor]=nod;
   contor++;
   while(1)
   {
   	temp=contor;
		for(i=0;i<contor;i++)
      {
      	for(j=0;j<nr;j++)
         if(mat[y[i]][j]==1)
         {
         	for(k=0;k<temp;k++) if(y[k]==j) break;
            if(k==temp)
            {
            	y[temp]=j;
	  				temp++;
               if(temp>nr) { fprintf(output,"ceva este in neregula \n");fflush(output);}
            }
            mat[y[i]][j]=mat[j][y[i]]=0;
         }
      }
      contor=temp;
      for(i=0;i<contor;i++) if(y[i]!=y1[i]) break;
      if(i!=contor) rezultat=0;
      else rezultat=1;
      nr_muchii[0]=0;
		for(i=0;i<nr;i++) for(j=0;j<nr;j++) if(mat[i][j]==1) nr_muchii[0]++;
      if(nr_muchii[0]==nr_muchii[1] && rezultat==1) break;
      else
      {
      	nr_muchii[1]=nr_muchii[0];
         for(i=0;i<nr;i++) y1[i]=y[i];
      }
   }
   nod=0;
   for(i=0;i<nr;i++) for(j=0;j<nr;j++) if(y[i]==j){ nod++; break;}
   if (nod==nr) rezultat=1;
   else rezultat=0;
   //eliberez memorie
   free(y);
   free(y1);
   free(*mat);
   free(mat);
   return rezultat;
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
//graf de test neconex
int **introducere_matrice1(int *nr)
{
	int i;
   int *temp,**mat;
   *nr=18;
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
   mat[12][13]=mat[13][12]=1;
   mat[13][14]=mat[14][13]=1;
   mat[13][15]=mat[15][13]=1;
   mat[15][16]=mat[16][15]=1;
   mat[15][17]=mat[17][15]=1;
   return mat;
}
//graf de test conex
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
   mat[7][8]=mat[8][7]=1;
   mat[2][4]=mat[4][2]=1;
   mat[3][4]=mat[4][3]=1;
   mat[2][9]=mat[9][2]=1;
   mat[2][10]=mat[10][2]=1;
   mat[10][11]=mat[11][10]=1;
   mat[9][11]=mat[11][9]=1;
   return mat;
}
//functia main
int main(void)
{
	int **mat,nr,i,j,flag;
   output=fopen("output.dat","w");
   mat=introducere_matrice1(&nr); //aici se schimba pentru diferite tipuri de grafuri de testare
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) fprintf(output,"%d ",mat[i][j]);
      fprintf(output,"\n");fflush(output);
   }
	flag=conexitate(mat,nr);
   if(flag==1) fprintf(output,"Acest graf este conex\n");
   else fprintf(output,"Acest graf este neconex\n");
   fflush(output);
   free(*mat);
   free(mat);
   fclose(output);
   return 0;
}
