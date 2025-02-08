// quicksort.h: interface for the quicksort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUICKSORT_H__939AE535_C4F1_4AED_85D8_8A22F09FBBCC__INCLUDED_)
#define AFX_QUICKSORT_H__939AE535_C4F1_4AED_85D8_8A22F09FBBCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<fstream.h>
class quicksort  
{
public:
	quicksort();
	virtual ~quicksort();
protected:
	void poz(int st,int dr);
	int k;
	void quick(int st,int dr);
	float *sir;
	int nr;
	ofstream fp;
};

#endif // !defined(AFX_QUICKSORT_H__939AE535_C4F1_4AED_85D8_8A22F09FBBCC__INCLUDED_)
