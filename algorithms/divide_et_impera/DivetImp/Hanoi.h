// DetI.h: interface for the DetI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANOI_H__730488A1_2433_4722_89A4_58E374622967__INCLUDED_)
#define AFX_HANOI_H__730488A1_2433_4722_89A4_58E374622967__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<fstream.h>
class Hanoi
{
public:
	int nr_discuri;
	Hanoi();
	virtual ~Hanoi();

protected:
	void calculeaza(int n,int ts,int td);
	ofstream fp;
};

#endif // !defined(AFX_HANOI_H__730488A1_2433_4722_89A4_58E374622967__INCLUDED_)
