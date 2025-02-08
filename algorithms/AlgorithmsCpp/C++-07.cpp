/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Cpp.
	This is the program who find if a graph is a tree.

    Algorithms and Cpp is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and Cpp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and Cpp; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<iostream.h>
#include<stdlib.h>

struct data
{
  	int val;
   struct data *prec;
};
class stiva
{
public:
   	void push(int val1);
    int pop(void);
    stiva();
    ~stiva(){};
private:
   	struct data *virf,*temp;
};
void stiva::push(int val1)
{
	//push into stack
   temp=new data;
   temp->val=val1;
   temp->prec=NULL;
   if(virf!=NULL) temp->prec=virf;
   virf=temp;
}
int stiva::pop(void)
{
	//pop from stack
   int val;
   if(virf==NULL) return -1;
   temp=virf;
   virf=virf->prec;
	val=temp->val;
   delete temp;
   return val;
}
stiva::stiva(void)
{
   virf=NULL;
}

class arbore
{
public:
	arbore(int **mat,int nr1);
	void conex();
	void ciclic();
	int este();
	int rezultat;
private:
	int **mat1;
	int nr;
};
arbore::arbore(int **mat,int nr1)
{
	mat1=mat;
	nr=nr1;
}
void arbore::conex()
{
	//verify if the graph is connex
	int *y,*y1;
	int i,j,k,nod;
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
	contor=0;
	nr_muchii[0]=0;
	for(i=0;i<nr;i++) for(j=0;j<nr;j++) if(mat[i][j]==1) nr_muchii[0]++;
	nr_muchii[1]=nr_muchii[0];
	y[contor]=0;y1[contor]=0;
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
				if(temp>nr) { cout<<"ceva este in neregula \n";cout.flush();}
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
}

void  arbore::ciclic()
{
	//verify if the tree is ciclique.
	stiva stack;
	int i,j,contor,*grad,extras;
	grad=(int *)calloc(nr,sizeof(int));
   //calculez gradele
   for(i=0;i<nr;i++)
   for(j=0;j<nr;j++) if(mat1[j][i]==1) grad[i]++;
   contor=nr;
	for(i=0;i<nr;i++) if(grad[i]==1)
   {
   	stack.push(i);
      grad[i]--;
   }
   extras=stack.pop();
   while(extras!=-1)
   {
		contor--;
      for(i=0;i<nr;i++) if(mat1[extras][i]==1)
      {
      	grad[i]--;
         if(grad[i]==1)
         {
         	stack.push(i);
            grad[i]--;
         }
      }
      extras=stack.pop();
   }
   if(contor!=0) rezultat=1;
   else rezultat=0;
}
int arbore::este()
{
	conex();
	if(rezultat==0)	ciclic();
	if(rezultat==1) return 1;
	return 0;
}
int **introducere_matrice1(int *nr)
{
	//test ciclique graph
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

int **introducere_matrice2(int *nr)
{
	//test not ciclique graph
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
int **introducere_matrice3(int *nr)
{
	//graph not connex
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

void main(void)
{
	int **mat,nr;
	arbore *arb;
	mat=introducere_matrice2(&nr);
	arb=new arbore(mat,nr);
	arb->conex();
	if(arb->rezultat==0) cout<<"not connex graph"<<endl;
	else cout<<"graf conex"<<endl;
	arb->ciclic();
	if(arb->rezultat==0) cout<<"not ciclique graph"<<endl;
	else cout<<"graf ciclic"<<endl;
	if(arb->este()==0) cout<<"This graph is't a tree\n";
	else cout<<"This graph is a tree\n";
	cout.flush();
	free(*mat);
	free(mat);
}
