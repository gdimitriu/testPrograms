/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and C.
	This is the implementation of operation with polinoms.

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
int mult(double *op1,double *op2,double *rez,int *ord0,int *ord1,int *ordrez)
{
//multiplication of polinoms
int i,j;
	*ordrez=(*ord1)+(*ord0);
	for(i=0;i<(*ord1)+1;i++)
	if(op2[i]!=0)
		for(j=0;j<(*ord0)+1;j++)
			rez[j+i]+=op1[j]*op2[i];
	return 0;
}
int div(double *v0,double *v1,double *cit,double *rest,int *grad0,int *grad1,int *grad2,int *grad3)
{
// division of polinoms
int i;
int grdcit,grdrest,grdv0,grdv1;
	grdv0=*grad0;
	grdv1=*grad1;
	*grad2=grdcit=grdv0-grdv1;
	for(i=0;i<grdv0+1;i++) rest[i]=v0[i];
	while(grdcit>=0)
	{
		cit[grdcit]=rest[grdv0]/v1[*grad1];
		for(i=0;i<*grad1+1;i++)
			rest[grdv0-i]-=v1[grdv1-i]*cit[grdcit];
 		grdcit--;
		grdv0--;
	}
	if(rest[*grad1]==0) *grad3=*grad1-1;
	else	*grad3=*grad1;
	return 0;
}
int add(double *v0,double *v1,double *rez,int *grad0,int *grad1,int *gradrez)
{
//summ of polinoms
int i;
	if(*grad0<*grad1) *gradrez=*grad1;
	else	*gradrez=*grad0;
	for(i=0;i<*grad0+1;i++) rez[i]=v0[i];
	for(i=0;i<*grad1+1;i++) rez[i]+=v1[i];
	return 0;
}
int sus(double *v0,double *v1,double *rez,int *grad0,int *grad1,int *gradrez)
{
//substraction of polinoms
int i;
	if(*grad0<*grad1) *gradrez=*grad1;
	else	*gradrez=*grad0;
	for(i=0;i<*grad0+1;i++) rez[i]=v0[i];
	for(i=0;i<*grad1+1;i++) rez[i]-=v1[i];
	if(rez[*gradrez]==0) gradrez--;
	return 0;
}
int main()
{
double vector1[10],vector2[10];
double vector3[20],vector4[10];
int i,j;
int grad[4];
	printf("\nDegree of first polinom gr0=");fflush(stdout);
	scanf("%d",&grad[0]);fflush(stdin);
	printf("\nDegree of second polinom gr1=");fflush(stdout);
	scanf("%d",&grad[1]);fflush(stdin);
	for(i=0;i<10;i++)
	{
		vector1[i]=vector2[i]=vector3[i]=vector4[i]=0.0;
	}
	for(i=0;i<(grad[0]+1);i++)
	{
		scanf("%lf",&vector1[i]);
		fflush(stdin);
	}
	for(i=0;i<(grad[1]+1);i++)
	{
		scanf("%lf",&vector2[i]);
		fflush(stdin);
	}
	add(vector1,vector2,vector3,&grad[0],&grad[1],&grad[2]);
	printf("\n Rez summ\n");fflush(stdout);
	for(i=0;i<(grad[2]+1);i++)
	{
		printf("%lf ",vector3[i]);fflush(stdout);
	}
	for(i=0;i<grad[2];i++) vector3[i]=0.0;
	sus(vector1,vector2,vector3,&grad[0],&grad[1],&grad[2]);
	printf("\n Rez substraction\n");fflush(stdout);
	for(i=0;i<(grad[2]+1);i++)
	{
		printf("%lf ",vector3[i]);fflush(stdout);
	}
	for(i=0;i<grad[2];i++) vector3[i]=0.0;
	div(vector1,vector2,vector3,vector4,&grad[0],&grad[1],&grad[2],&grad[3]);
	printf("\n Division\n");fflush(stdout);
	for(i=0;i<(grad[2]+1);i++)
	{
		printf("%lf ",vector3[i]);fflush(stdout);
	}
	printf("\n Rest\n");fflush(stdout);
	for(i=0;i<(grad[3]+1);i++)
	{
		printf("%lf ",vector4[i]);fflush(stdout);
	}
	printf("\n");fflush(stdout);
	for(i=0;i<grad[0]+1;i++) vector1[i]=0.0;
	mult(vector3,vector2,vector1,&grad[2],&grad[1],&grad[0]);
	for(i=0;i<grad[3]+1;i++) vector1[i]+=vector4[i];
	printf("\n Multiplication\n");fflush(stdout);
	for(i=0;i<(grad[0]+1);i++)
	{
		printf("%lf ",vector1[i]);fflush(stdout);
	}
	printf("\n");fflush(stdout);
}