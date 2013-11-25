// CheckDlg.h : header file
//

#if !defined(AFX_CHECKDLG_H__D8CC479B_C7F1_4375_B6DF_EEBD55FFD140__INCLUDED_)
#define AFX_CHECKDLG_H__D8CC479B_C7F1_4375_B6DF_EEBD55FFD140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg dialog

class CCheckDlg : public CDialog
{
// Construction
public:
	int CreateLogFile(CString LogMessage);
	int CRC(CString path,DWORD *pCS);
	int BrowseAndCompareCheckSum(CString RootPath);
	int CCheckDlg::CalculateCheckSum(CString path,DWORD *pCS); 
	int BrowseAndCalculateCheckSum(CString RootPath);
	CString ChooseFolder(CString lpszTitle);
	CCheckDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckDlg)
	enum { IDD = IDD_CHECK_DIALOG };
	CButton	m_CheckBoxCreateLogCtrl;
	CRichEditCtrl	m_RichEditControl;
	CString	m_RichEditMessage;
	BOOL	m_CheckBoxCreateLog;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCheckDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartChooseDestinationFolder();
	afx_msg void OnStartChooseSourceFolder();
	afx_msg void OnButtonWriteReport();
	afx_msg void OnButtonCheckArchive();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKDLG_H__D8CC479B_C7F1_4375_B6DF_EEBD55FFD140__INCLUDED_)
