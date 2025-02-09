/* program pentru determinarea unui ciclu eulerian*/
/* realizat de catre Dimitriu Gabriel gr 21 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *output;
//functie care determina daca eliminind o muchie este punte
int punte(int **mat1,int nr,int nr1,int nr2,int nr_ram)
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
      temporar+=nr;
   }
   for(i=0;i<nr;i++) for(j=0;j<nr;j++) mat[i][j]=mat1[i][j];
   mat[nr1][nr2]=mat[nr2][nr1]=0; //elimin muchia
   y=(int *)calloc(nr,sizeof(int));
   y1=(int *)calloc(nr,sizeof(int));
	for(i=0;i<nr;i++) {y[i]=-1;y1[i]=-1;}
   contor=0;
   nr_muchii[0]=0;
	for(i=0;i<nr;i++) for(j=0;j<nr;j++) if(mat[i][j]==1) nr_muchii[0]++;
   nr_muchii[1]=nr_muchii[0];
   y[contor]=nr1;y1[contor]=nr1;
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
   if (nod==nr_ram) rezultat=1; //este conex deci nu este punte
   else rezultat=0; //nu este conex deci este punte
   //eliberez memorie
   free(y);
   free(y1);
   free(*mat);
   free(mat);
   return rezultat;
}
void eulerian(int **mat,int nr)
{
	int i,j,k,flag,nr_ram;
	int element,vechi,grad,tbridge;
	for(j=0;j<nr;j++)
	{
   		grad=0;
		for(i=0;i<nr;i++) if(mat[j][i]==1) grad++;
		if(grad%2==1)
		{
      		fprintf(output,"Graful nu are un ciclu eulerian!");
			fflush(output);
			return;
		}
	}
	element=0;
	fprintf(output,"%d ",element);
	grad=0;
	for(i=0;i<nr;i++) if(mat[0][i]==1) grad++;
	flag=0;
	nr_ram=nr;
	i=0;
	while(grad!=0)
	{
		vechi=element;
		while(1)
		{
   			if(mat[element][i]==1)
			{
				tbridge=mat[element][i];
				mat[element][i]=mat[i][element]=0;
	  	   		if(punte(mat,nr,element,i,nr_ram)==1)
				{
	  			 	fprintf(output,"%d ",i);
					fflush(output);
					element=i;
				}
				else
				{
            		if(flag==1)
					{
        		     	fprintf(output,"%d ",i);
						fflush(output);
               			element=i;
						nr_ram=nr;
 						for(j=0;j<nr;j++)
						{
                  			for(k=0;k<nr;k++) if(mat[j][k]==1) break;
							if(k==nr) nr_ram--;
						}
						flag=0;
      				}
					else mat[element][i]=mat[i][element]=tbridge;
				}
			}
			i++;
			if(i==nr) break;
		}
		if(vechi==element) flag=1;
		else flag=0;
   		grad=0;
		for(i=0;i<nr;i++) if(mat[element][i]==1) grad++;
		i=0;
   }
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
//   *nr=16;
   *nr=6;
   mat=(int **)calloc(*nr,sizeof(int *));
   temp=(int *)calloc((*nr)*(*nr),sizeof(int));
   for(i=0;i<*nr;i++)
   {
   	mat[i]=temp;
      temp+=(*nr);
   }
/*
	mat[0][6]=mat[6][0]=1;
   mat[6][7]=mat[7][6]=1;
   mat[0][7]=mat[7][0]=1;
	mat[0][1]=mat[1][0]=1;
   mat[1][14]=mat[14][1]=1;
   mat[14][15]=mat[15][14]=1;
	mat[1][15]=mat[15][1]=1;
	mat[1][2]=mat[2][1]=1;
   mat[2][3]=mat[3][2]=1;
   mat[3][13]=mat[13][3]=1;
   mat[12][13]=mat[13][12]=1;
   mat[3][12]=mat[12][3]=1;
   mat[3][4]=mat[4][3]=1;
   mat[4][11]=mat[11][4]=1;
   mat[11][10]=mat[10][11]=1;
   mat[4][10]=mat[10][4]=1;
   mat[4][5]=mat[5][4]=1;
   mat[5][9]=mat[9][5]=1;
   mat[8][9]=mat[9][8]=1;
   mat[5][8]=mat[8][5]=1;
   mat[0][5]=mat[5][0]=1;
*/
   mat[0][1]=mat[1][0]=1;
   mat[1][2]=mat[2][1]=1;
   mat[2][3]=mat[3][2]=1;
   mat[3][4]=mat[4][3]=1;
   mat[4][5]=mat[5][4]=1;
   mat[5][0]=mat[0][5]=1;
   mat[5][1]=mat[1][5]=1;
   mat[5][3]=mat[3][5]=1;
   mat[3][1]=mat[1][3]=1;
   return mat;
}
//functia main
int main(void)
{
	int **mat,nr,i,j;
   output=fopen("output.dat","w");
   mat=introducere_matrice1(&nr); //aici se schimba pentru diferite tipuri de grafuri de testare
   fprintf(output,"Matricea de adiacenta asociata grafului este:\n");
   for(i=0;i<nr;i++)
   {
   	for(j=0;j<nr;j++) fprintf(output,"%d ",mat[i][j]);
      fprintf(output,"\n");fflush(output);
   }
   fprintf(output,"Ciclul eulerian al grafului este:");
	eulerian(mat,nr);
   fflush(output);
   free(*mat);
   free(mat);
   fclose(output);
   return 0;
}