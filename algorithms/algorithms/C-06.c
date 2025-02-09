#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *output;
struct nod
{
	int name;
   int info;
   int nr_fii;
   struct nod **fii;
};
struct node
{
	int name;
   int info;
   struct node *fii[2];
};
struct nod *find_nod(struct nod *baza,int val)
{
	struct nod *temp;
 	int i;
   if(baza->name!=val)
	   for(i=0;i<baza->nr_fii;i++)
      {
      	temp=NULL;
      	if(baza->fii[i]!=NULL) temp=find_nod(baza->fii[i],val);
         if(temp!=NULL) return temp;
      }
   else	return baza;
   return NULL;
}
struct nod *introducere(struct nod *baza)
{
	struct nod *temp,*temp1;
   int tempi,i;
   FILE *fp;
   char name[256];
   printf("Plese input the name of file in whitch is the tree\n");fflush(stdout);
   gets(name);fflush(stdin);
   fp=fopen(name,"r");
   if(baza==NULL)
   {
   	temp=(struct nod *)calloc(1,sizeof(struct nod));
      baza=temp;
      fscanf(fp,"%d ",&tempi);fflush(fp);
      temp->name=tempi;
	   fscanf(fp,"%d ",&tempi);fflush(fp);
   	temp->info=tempi;
      fscanf(fp,"%d ",&tempi);fflush(fp);
	   temp->nr_fii=tempi;
   	temp->fii=(struct nod **)calloc(tempi,sizeof(struct nod *));
      for(i=0;i<temp->nr_fii;i++)
	   {
	   	fscanf(fp,"%d ",&tempi);
   	   temp1=(struct nod *)calloc(1,sizeof(struct nod));
      	temp1->name=tempi;
		   temp1->info=0;
   		temp1->nr_fii=0;
         temp1->fii=NULL;
      	temp->fii[i]=temp1;
   	}
   }
   while(!feof(fp))
   {
      fscanf(fp,"%d ",&tempi);fflush(fp);
      if(feof(fp)) break;
		temp=find_nod(baza,tempi);
	   if(temp==NULL) exit(-1);
		fscanf(fp,"%d ",&tempi);fflush(fp);
	   temp->info=tempi;
   	fscanf(fp,"%d ",&tempi);fflush(fp);
		temp->nr_fii=tempi;
   	temp->fii=(struct nod **)calloc(tempi,sizeof(struct nod *));
	   for(i=0;i<temp->nr_fii;i++)
		{
	   	fscanf(fp,"%d ",&tempi);
   	   temp1=(struct nod *)calloc(1,sizeof(struct nod));
	      temp1->fii=NULL;
   	   temp1->name=tempi;
		   temp1->info=0;
   		temp1->nr_fii=0;
   	   temp->fii[i]=temp1;
	   }
   }
   fclose(fp);
   return baza;
}
void print_tree(struct nod *baza)
{
   int i;
   FILE *fp;
   if(baza!=NULL)
   {
   	fp=fopen("tree.dat","a");
   	fprintf(fp,"%d ",baza->name);fflush(fp);
      fclose(fp);
      for(i=0;i<baza->nr_fii;i++) print_tree(baza->fii[i]);
   }
}
struct node *tbinary(struct node *baza,struct nod *tree,int indice)
{
	struct node *temp;
   temp=(struct node *)calloc(1,sizeof(struct node));
   if(baza==NULL)
   {
	   temp->name=tree->name;
   	temp->info=tree->info;
	   temp->fii[0]=temp->fii[1]=NULL;
		tbinary(temp,tree,0);
   }
   else
   {
   	temp->name=tree->fii[indice]->name;
      temp->info=tree->fii[indice]->info;
      temp->fii[0]=temp->fii[1]=NULL;
      if(tree->fii[indice]->nr_fii!=0) tbinary(temp,tree->fii[indice],0);
   	if(indice==0)	baza->fii[0]=temp;
      else 	baza->fii[1]=temp;
      indice++;
	   if(indice<tree->nr_fii)	tbinary(temp,tree,indice);
   }
   return temp;
}
void print_treeb(struct node *baza)
{
   FILE *fp;
   if(baza!=NULL)
   {
   	fp=fopen("treeb.dat","a");
   	fprintf(fp,"%d ",baza->name);fflush(fp);
      fclose(fp);
      print_treeb(baza->fii[0]);
		print_treeb(baza->fii[1]);
   }
}
void main(void)
{
	struct nod *tree;
   struct node *treeb;
   output=fopen("output.dat","w");
   tree=introducere(NULL);
   print_tree(tree);
   treeb=tbinary(NULL,tree,0);
   print_treeb(treeb);
   fclose(output);
}