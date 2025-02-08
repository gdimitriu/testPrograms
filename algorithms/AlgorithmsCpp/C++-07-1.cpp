#include<iostream.h>
class element
{
	int *oint; //value type int 
	double *odouble; //value de type double
	int type;
public:
	element *suivant;
	element(int v)
	{
		oint=new int(v);
		type=1;
		suivant=NULL;
	}
	element(double v)
	{
		odouble=new double(v);
		type=2;
		suivant=NULL;
	}
	void print()
	{
		if(type==1)	cout<<*oint<<endl;
		if(type==2)	cout<<*odouble<<endl;
	}
	~element()
	{
		if(type=1) delete oint;
		else delete odouble;
	}
};

class lista
{
	element *temp,*base,*fin;
public:
	lista(int v) {base=fin=new element(v);}
	lista(double v)	{base=fin=new element(v);}
	template<class stip> void adaug(stip v);
	void print(){ for(temp=base;temp!=NULL;temp=temp->suivant) temp->print();}
};
template<class stip> void lista::adaug(stip v)
{
	temp=new element(v);
	fin->suivant=temp;
	fin=temp;
};
int main()
{
	lista *liste;
	liste=new lista(10);
	liste->adaug(10.23);
	liste->adaug(100);
	liste->adaug(0.234);
	liste->print();
}