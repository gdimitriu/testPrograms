// backtracking.h: interface for the backtracking class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKTRACKING_H__6FF7C131_4D4E_40C5_848A_A1B4128EBC12__INCLUDED_)
#define AFX_BACKTRAKING_H__6FF7C131_4D4E_40C5_848A_A1B4128EBC12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class backtracking  
{
public:
	backtracking();
	backtracking(int nr);
	virtual ~backtracking();

private:
	bool solutie(int k);
	int * final;
	int init(int k);
	void calcul(int k);
	int backup;
	bool conditii_interne(int k);
	int nr_dame;
	bool succesor(int *a,int k);
	void Final(void);
};

#endif // !defined(AFX_BACKTRACKING_H__6FF7C131_4D4E_40C5_848A_A1B4128EBC12__INCLUDED_)
