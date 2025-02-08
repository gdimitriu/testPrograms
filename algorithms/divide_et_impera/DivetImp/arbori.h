// arbori.h: interface for the arbori class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARBORI_H__F23F1F0E_DF19_4E02_929F_AA01C8DD869D__INCLUDED_)
#define AFX_ARBORI_H__F23F1F0E_DF19_4E02_929F_AA01C8DD869D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "nod.h"
#include<stdlib.h>
#include <fstream.h>
class arbori  
{
public:
	ofstream fp;
	int stergere(int info);
	int adaug1(struct nod *intr);
	void SRD(struct nod *test);
	void DRS(struct nod *test);
	int adaugare(int info);
	struct nod *baza,*temp,*temp1;
	arbori();
	virtual ~arbori();

};

#endif // !defined(AFX_ARBORI_H__F23F1F0E_DF19_4E02_929F_AA01C8DD869D__INCLUDED_)
