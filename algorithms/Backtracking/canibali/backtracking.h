// backtracking.h: interface for the backtraking class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKTRACKING_H__6FF7C131_4D4E_40C5_848A_A1B4128EBC12__INCLUDED_)
#define AFX_BACKTRACKING_H__6FF7C131_4D4E_40C5_848A_A1B4128EBC12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class backtracking  
{
public:
	backtracking();
	virtual ~backtracking();

private:
	int backup;
	int nm1,nm2,nc1,nc2,m,c;
	bool solutie(int k);
	int final[100][5];
	void init(int k);
	void calcul(int k);
	bool conditii_interne(int k);
	bool succesor(int *a);
	void Final(int k);
};

#endif // !defined(AFX_BACKTRACKING_H__6FF7C131_4D4E_40C5_848A_A1B4128EBC12__INCLUDED_)
