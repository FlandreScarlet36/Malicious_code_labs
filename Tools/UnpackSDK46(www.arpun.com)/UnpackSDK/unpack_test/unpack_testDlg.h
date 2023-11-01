// unpack_testDlg.h : header file
//

#if !defined(AFX_UNPACK_TESTDLG_H__5DF2217D_5C0F_483B_B4A8_741B7114E5E0__INCLUDED_)
#define AFX_UNPACK_TESTDLG_H__5DF2217D_5C0F_483B_B4A8_741B7114E5E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUnpack_testDlg dialog

class CUnpack_testDlg : public CDialog
{
// Construction
public:
	CUnpack_testDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUnpack_testDlg)
	enum { IDD = IDD_UNPACK_TEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnpack_testDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUnpack_testDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton();
	afx_msg void OnDropFiles(HDROP hDrop);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int unpack(char *pInputFile, char *pOutputFile);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNPACK_TESTDLG_H__5DF2217D_5C0F_483B_B4A8_741B7114E5E0__INCLUDED_)
