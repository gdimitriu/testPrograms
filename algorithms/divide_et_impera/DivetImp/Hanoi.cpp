// Hanoi.cpp: implementation of the DetI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Hanoi.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Hanoi::Hanoi()
{
	fp.open("Hanoi.dat",ios::out);
	cout<<"Turnul din Hanoi.Dati Nr de discuri"<<endl;
	cin>>nr_discuri;
	calculeaza(nr_discuri,1,2);
}

Hanoi::~Hanoi()
{
	fp.close();
}

void Hanoi::calculeaza(int n, int ts, int td)
{
	if(n==1)
	{
		fp<<ts<<' '<<n<<"->"<<td<<endl;
		fp.flush();
	}
	else
	{
		calculeaza(n-1,ts,6-ts-td);
		fp<<ts<<' '<<n<<"->"<<td<<endl;
		fp.flush();
		calculeaza(n-1,6-ts-td,td);
	}
}
