/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and C.
	This is the implementation of operation for a crowd of bidimensional points.

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
#include<math.h>

struct elem
{
	double x;
	double y;
	double distanta;
	struct elem *apres;
	struct elem *avant;
};
struct elem *baze[2],*finale[2];
struct elem *temp;
struct elem *reubaza,*reufinal;
struct elem *intbaza,*intfinal;
struct elem *diffbaza,*difffinal;
void introducere(struct elem *element,struct elem **baza,struct elem **final)
{
	//input an element into list
	int flag=0;
	element->distanta=sqrt(pow(element->x,2.0)+pow(element->y,2.0));
	printf("%lf\n",element->distanta);fflush(stdout);
	if(*baza==NULL)
	{
		*baza=*final=element;
		element->apres=NULL;
		element->avant=NULL;
		return;
	}
	else
	{
		if(element->distanta<=(*baza)->distanta)
		{
			(*baza)->avant=element;
			element->avant=NULL;
			element->apres=*baza;
			*baza=element;
			return;
		}
		if((*baza)->apres==NULL) temp=*baza;
		else	temp=(*baza)->apres;
		while(flag==0)
		{
			if(element->distanta<=temp->distanta)
			{
				temp->avant->apres=element;
				element->avant=temp->avant;
				element->apres=temp;
				temp->avant=element;
				return;
			}
			if(temp->apres==NULL)
			{
				temp->apres=element;
				element->avant=temp;
				element->apres=NULL;
				*final=element;
				return;
			}
			temp=temp->apres;
		}
	}
}
void reuniune(struct elem **interior,struct elem **superior,struct elem **baza,struct elem **final)
{
	//reunion of lists
	int i,flag;
	struct elem *temp1,*temp2;
	for(i=0;i<2;i++)
	{
		temp1=interior[i];
		if(*baza==NULL)
		{
			temp2=(struct elem *)calloc(1,sizeof(struct elem));
			temp2->x=temp1->x;
			temp2->y=temp1->y;
			temp2->distanta=temp1->distanta;
			*baza=*final=temp2;
			temp2->apres=NULL;
			temp2->avant=NULL;
			temp1=temp1->apres;
		}
		while(temp1!=NULL)
		{
			if((temp1->x==(*baza)->x) && (temp1->y==(*baza)->y)) ;
			else
			{
				if(temp1->distanta<=(*baza)->distanta)
				{
					temp2=(struct elem *)calloc(1,sizeof(struct elem));
					temp2->x=temp1->x;
					temp2->y=temp1->y;
					temp2->distanta=temp1->distanta;
					(*baza)->avant=temp2;
					temp2->avant=NULL;
					temp2->apres=*baza;
					*baza=temp2;
				}
				else
				{
					if((*baza)->apres==NULL) temp=*baza;
					else	temp=(*baza)->apres;
					flag=0;
					while(flag==0)
					{
						if((temp1->x==temp->x) && (temp1->y==temp->y)) flag=1;
						else
						{
							if(temp1->distanta<=temp->distanta)
							{
								temp2=(struct elem *)calloc(1,sizeof(struct elem));
								temp2->x=temp1->x;
								temp2->y=temp1->y;
								temp2->distanta=temp1->distanta;
								temp->avant->apres=temp2;
								temp2->avant=temp->avant;
								temp2->apres=temp;
								temp->avant=temp2;
								flag=1;
							}
							else 
							{
								if(temp->apres==NULL)
								{
									temp2=(struct elem *)calloc(1,sizeof(struct elem));
									temp2->x=temp1->x;
									temp2->y=temp1->y;
									temp2->distanta=temp1->distanta;
									temp->apres=temp2;
									temp2->avant=temp;
									temp2->apres=NULL;
									(*final)=temp2;
									flag=1;
								}
								else	temp=temp->apres;
							}
						}
					}
				}	
			}
			temp1=temp1->apres;
		}
	}
}

void intersectie(struct elem **interior,struct elem **superior,struct elem **baza,struct elem **final)
{
	//intersection of list
	int i;
	struct elem *temp1,*temp2;
	temp1=interior[1];
	temp=interior[0];
	while(temp1!=NULL)
	{
		temp=interior[0];
		while(temp!=NULL)
		{
			if((temp1->x==temp->x) && (temp1->y==temp->y))
			{
				temp2=(struct elem *)calloc(1,sizeof(struct elem));
				temp2->x=temp1->x;
				temp2->y=temp1->y;
				temp2->distanta=temp1->distanta;
				temp2->apres=NULL;
				if(*baza==NULL)
				{
					*baza=*final=temp2;
					temp2->avant=NULL;
				}
				else
				{
					(*final)->apres=temp2;
					temp2->avant=*final;
					*final=temp2;
				}
				temp=NULL;
			}
			else	temp=temp->apres;
		}
		temp1=temp1->apres;
	}
}


void diferenta(struct elem **interior,struct elem **superior,struct elem **baza,struct elem **final)
{
	//diference of lists
	int i;
	struct elem *temp1,*temp2;
	temp1=interior[0];
	temp=interior[1];
	while(temp1!=NULL)
	{
		temp=interior[1];
		while(temp!=NULL)
		{
			if((temp1->x==temp->x) && (temp1->y==temp->y)) break;
			else temp=temp->apres;
		}
		if(temp==NULL)
		{
			temp2=(struct elem *)calloc(1,sizeof(struct elem));
			temp2->x=temp1->x;
			temp2->y=temp1->y;
			temp2->distanta=temp1->distanta;
			temp2->apres=NULL;
			if(*baza==NULL)
			{
				*baza=*final=temp2;
				temp2->avant=NULL;
			}
			else
			{
				(*final)->apres=temp2;
				temp2->avant=*final;
				*final=temp2;
			}
		}
		temp1=temp1->apres;
	}
}
int main()
{
	int i,j;
	int nr;
	for(j=0;j<2;j++)
	{
		baze[j]=NULL;
		printf("Input how many numbers do you have in the list nr=");fflush(stdout);
		scanf("%d",&nr);fflush(stdin);
		for(i=0;i<nr;i++)
		{
			temp=(struct elem *)calloc(1,sizeof(struct elem));
			printf("\nInput numbers");fflush(stdout);
			scanf("%lf",&temp->x);
			scanf("%lf",&temp->y);fflush(stdin);
			introducere(temp,&baze[j],&finale[j]);
		}
	}
	printf("Elements before operations\n");fflush(stdout);
	for(j=0;j<2;j++)
	{
		temp=baze[j];
		while(temp!=NULL)
		{
			printf("%lf\n",temp->distanta);
			temp=temp->apres;
		}
	}
	reubaza=reufinal=NULL;
	reuniune(baze,finale,&reubaza,&reufinal);
	printf("reunion\n");fflush(stdout);
	temp=reubaza;
	while(temp!=NULL)
	{
		printf("%lf %lf %lf\n",temp->x,temp->y,temp->distanta);
		fflush(stdout);
		temp=temp->apres;
	}
	intbaza=intfinal=NULL;
	intersectie(baze,finale,&intbaza,&intfinal);
	printf("Intersection\n");fflush(stdout);
	temp=intbaza;
	while(temp!=NULL)
	{
		printf("%lf %lf %lf\n",temp->x,temp->y,temp->distanta);
		fflush(stdout);
		temp=temp->apres;
	}
	diffbaza=difffinal=NULL;
	diferenta(baze,finale,&diffbaza,&difffinal);
	printf("Diference\n");fflush(stdout);
	temp=diffbaza;
	while(temp!=NULL)
	{
		printf("%lf %lf %lf\n",temp->x,temp->y,temp->distanta);
		fflush(stdout);
		temp=temp->apres;
	}
}
