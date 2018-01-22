// MetaTraderAPIExample2.h : main header file for the METATRADERAPIEXAMPLE2 application
//

#if !defined(AFX_METATRADERAPIEXAMPLE2_H__95562914_7A66_429A_A2B4_D85237CCDEC4__INCLUDED_)
#define AFX_METATRADERAPIEXAMPLE2_H__95562914_7A66_429A_A2B4_D85237CCDEC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMetaTraderAPIExample2App:
// See MetaTraderAPIExample2.cpp for the implementation of this class
//

class CMetaTraderAPIExample2App : public CWinApp
{
public:
	CMetaTraderAPIExample2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetaTraderAPIExample2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMetaTraderAPIExample2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METATRADERAPIEXAMPLE2_H__95562914_7A66_429A_A2B4_D85237CCDEC4__INCLUDED_)
