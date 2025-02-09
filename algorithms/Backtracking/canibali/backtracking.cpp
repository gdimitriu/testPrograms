// backtracking.cpp: implementation of the backtraking class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "backtracking.h"
#include <fstream.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

backtracking::backtracking()
{
	cout<<"Misionari ";cout.flush();
	cin>>m;
	cout<<"Canibali ";cout.flush();
	cin>>c;
	final[0][0]=-1;
	backup=-1;
	final[0][1]=m;
	final[0][2]=c;
	final[0][3]=0;
	final[0][4]=0;
	calcul(0);
}

backtracking::~backtracking()
{
}

void backtracking::Final(int k)
{
	int i;
	cout<<"Saving data\n";cout.flush();
	ofstream fp("data.dat",ios::app);
	if(!fp)
	{
		cout<<"Eroare la deschidere fisier";
		exit(-1);
	}
	for(i=0;i<=k;i++) fp<<final[i][1]<<' '<<final[i][2]<<' '<<final[i][3]<<' '<<final[i][4]<<endl;
	fp<<"valori ";
	fp<<nm1<<' '<<nc1<<' '<<nm2<<' '<<nc2<<endl;
	fp.flush();
	fp.close();
}

void backtracking::init(int k)
{
	backup=-1;
	final[k][1]=nm1;
	final[k][2]=nc1; 
    final[k][3]=nm2;
	final[k][4]=nc2;        
}


bool backtracking::solutie(int k)
{
	return ((nc1==0)&&(nm1==0));
}

bool backtracking::conditii_interne(int k)
{
	nm1=final[k][1];
	nc1=final[k][2];
	nm2=final[k][3];
	nc2=final[k][4];
	if (k%2==0)
	{
		switch(backup)
		{
	    case 0:
		   nm1=nm1-2;
		   nm2=nm2+2;
		   break;
	    case 1:
		   nc1=nc1-2;
		   nc2=nc2+2;
		   break;
		case 2:
			nm1--;
			nc1--;
			nm2++;
			nc2++;
			break;
		case 3:
			nm1--;
			nm2++;
			break;
		case 4:
			nc1--;
			nc2++;
			break;
		}
	}
	else
	{
		switch(backup)
		{
		case 0:
			nm2=nm2-2;
			nm1=nm1+2;
			break;
		case 1:
			nc2=nc2-2;
			nc1=nc1+2;
			break;
		case 2:
			nm2--;
			nc2--;
			nm1++;
			nc1++;
			break;
		case 3:
			nm2--;
			nm1++;
			break;
		case 4:
			nc2--;
			nc1++;
			break;
		}
	}
	bool ev;
	ev=true;
	if((nm1<0 || nm2<0 || nc1<0 || nc2<0)
		|| (nc1>nm1 && nm1>0) || (nc2>nm2 && nm2>0)) ev=false;
	if (k!=0) if(backup==final[k-1][0]) ev=false;
	for(int i=0;i<k;i++) if((final[i][1]==nm1) &&(final[i][2]==nc1) 
		&& ((k-i)%2==1)) ev=false;
	return ev;
}

bool backtracking::succesor(int *a)
{
	if((*a)<4)
	{
		(*a)++;
		return true;
	}
	else return false;
}

void backtracking::calcul(int k)
{
	bool found,inainte;
	k=0;
	while(k>=0)
	{
		while(1)
		{
			found=succesor(&backup);
			inainte=false;
			if(found) inainte=conditii_interne(k);
			if(inainte) final[k][0]=backup;
			if(inainte || !found) break;
		}
		if(found)
		{
			if(solutie(k)) Final(k);
			else { k++; init(k);}
		}
		else { k--;backup=final[k][0];}
	}
}
