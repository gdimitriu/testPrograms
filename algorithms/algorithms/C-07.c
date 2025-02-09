#include<stdio.h>
#include<stdlib.h>
FILE *output;
struct nod
{
	int name;
   struct nod *leg[3]; //leg[0]=first son leg[1]=brother leg[2]=father
};
struct nod *find_nod(struct nod *baza,int info)
{
	struct nod *work;
   if(baza==NULL) return NULL;
  	if(baza->name==info) return baza;
  	work=find_nod(baza->leg[0],info);
	if(work!=NULL) return work;
   work=find_nod(baza->leg[1],info);
   return work;
}


struct nod *create_tree(void)
{
	FILE *fp;
   struct nod *temp,*work,*baza;
   int i,tempi,nr;
	char name[256];
   printf("Input the file\n");fflush(stdout);
  	gets(name);
   fp=fopen(name,"r");
	baza=(struct nod *)calloc(1,sizeof(struct nod));
   fscanf(fp,"%d ",&baza->name);fflush(fp);
   baza->leg[0]=NULL;
  	baza->leg[1]=baza->leg[2]=NULL;
   fscanf(fp,"%d ",&nr);fflush(fp);
   work=baza;
   for(i=0;i<nr;i++)
   {
   	temp=(struct nod *)calloc(1,sizeof(struct nod));
      fscanf(fp,"%d ",&temp->name);fflush(fp);
      if(i==0) work->leg[0]=temp;
      else work->leg[1]=temp;
		temp->leg[0]=NULL;
      temp->leg[1]=NULL;
      if(i==0) temp->leg[2]=work;
      else temp->leg[2]=work->leg[2];
      work=temp;
   }
   while(!feof(fp))
   {
   	fscanf(fp,"%d ",&tempi);fflush(fp);
      fprintf(output,"before=%d ",tempi);fflush(output);
      work=find_nod(baza,tempi);
      fprintf(output,"after=%d ",tempi);fflush(output);
      fscanf(fp,"%d ",&nr);fflush(fp);
	   for(i=0;i<nr;i++)
   	{
	   	temp=(struct nod *)calloc(1,sizeof(struct nod));
         fscanf(fp,"%d ",&temp->name);fflush(fp);
         if(i==0) work->leg[0]=temp;
         else work->leg[1]=temp;
			temp->leg[0]=NULL;
	      temp->leg[1]=NULL;
         fprintf(output,"son=%d ",i);fflush(output);
   	   if(i==0) temp->leg[2]=work;
	      else temp->leg[2]=work->leg[2];
   	   work=temp;
   	}
		fprintf(output,"final=%d ",tempi);fflush(output);
   }
   fclose(fp);
	return baza;
}
void print_tree(struct nod *baza)
{
   FILE *fp;
   fp=fopen("treesbf.dat","a");
   if(baza!=NULL)
   {
		fprintf(fp,"%d ",baza->name);
      print_tree(baza->leg[0]);
      print_tree(baza->leg[1]);
   }
}


void main(void)
{
	struct nod *baza;
	output=fopen("output.dat","w");
   baza=create_tree();
   print_tree(baza);
   fclose(output);
}
