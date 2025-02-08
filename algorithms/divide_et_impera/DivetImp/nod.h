// nod.h: interface for the nod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOD_H__A05C6561_8E99_4022_9EF1_7CA12A98B5BB__INCLUDED_)
#define AFX_NOD_H__A05C6561_8E99_4022_9EF1_7CA12A98B5BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct nod  
{
public:
	nod();
	virtual ~nod();
	int info;
	struct nod *fii[2];
};

#endif // !defined(AFX_NOD_H__A05C6561_8E99_4022_9EF1_7CA12A98B5BB__INCLUDED_)
