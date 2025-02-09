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
	int nr_reusite;
	int contor;
	int nr_combinatii;
	int combinari(int n,int p);
	int Nr_elem;
	bool solutie(int k);
	bool first;
	int ** final;
	int init(int k);
	void calcul(int k);
	bool conditii_interne(int k);
	int nr_max;
	bool succesor(int *a);
	void Final(void);
};

#endif // !defined(AFX_BACKTRACKING_H__6FF7C131_4D4E_40C5_848A_A1B4128EBC12__INCLUDED_)
