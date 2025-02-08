// reducere.h: interface for the reducere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REDUCERE_H__8832D32D_D648_4827_A3C3_EEBEFE7D4CCD__INCLUDED_)
#define AFX_REDUCERE_H__8832D32D_D648_4827_A3C3_EEBEFE7D4CCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<fstream.h>
class reducere  
{
public:
	float operatie(int beg,int fin);
	int nr;
	reducere();
	virtual ~reducere();
	float *valori;
};

#endif // !defined(AFX_REDUCERE_H__8832D32D_D648_4827_A3C3_EEBEFE7D4CCD__INCLUDED_)
