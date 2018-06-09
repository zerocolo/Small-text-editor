// 小型文本编辑器Dlg.h : header file
//

#if !defined(AFX_DLG_H__ECF7ECB8_A633_4C46_90DF_AEB858932A60__INCLUDED_)
#define AFX_DLG_H__ECF7ECB8_A633_4C46_90DF_AEB858932A60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

#include "string"

using namespace std;

struct DulNode
{
    char *Node_str;
    DulNode *next;
};

class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

	void Read(CString FilePath);
	void KMP(char *str,  char *ptr);
	void Destory();
	

	CString strFilePath;



// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CString	m_str1;
	CString	m_str2;
	CString	m_str4;
	CString	m_str5;
	CString	m_str6;
	CString	m_str3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	virtual BOOL PreTranslateMessage(MSG *pMsg);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInsert();
	afx_msg void OnNew();
	afx_msg void OnOpen();
	afx_msg void OnKeep();
	afx_msg void OnTotal();
	afx_msg void OnSearch();
	afx_msg void OnDelete();
	afx_msg void OnQuit();
	afx_msg void OnStead();
	//}}AFX_MSG
	DulNode *Text_head;
    int Text_rear;
	bool Debug;



	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__ECF7ECB8_A633_4C46_90DF_AEB858932A60__INCLUDED_)
