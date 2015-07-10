// heoilDlg.h : header file
//

#if !defined(AFX_HEOILDLG_H__73AD308E_D942_44CF_B15A_68F7CA43E95B__INCLUDED_)
#define AFX_HEOILDLG_H__73AD308E_D942_44CF_B15A_68F7CA43E95B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHeoilDlg dialog

class CHeoilDlg : public CDialog
{
// Construction
public:
	CHeoilDlg(CWnd* pParent = NULL);	// standard constructor
	CString srcfilename,dstfilename,dftdstfilename;
	CString FileExt,FileName;
	long int srckb;
	char s[50];
// Dialog Data
	//{{AFX_DATA(CHeoilDlg)
	enum { IDD = IDD_HEOIL_DIALOG };
	CProgressCtrl	MyCtrl;
	CString	m_dstfilename;
	CString	m_srcfilename;
	int		m_Byte;
	long	m_Time;
	double	m_Ratio;
	double	m_DeCompressedFileM;
	double	m_SourceFileKB;
	BOOL	m_check;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeoilDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHeoilDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadio1();
	afx_msg void OnOpenfile();
	afx_msg void OnChangeDirectory();
	afx_msg void OnCompress();
	afx_msg void OnDecompress();
	afx_msg void OnCheck1();
	afx_msg void OnUpdateEditdestinationfile();
	afx_msg void OnCopyright();
	afx_msg void OnEncrypt();
	afx_msg void OnDecode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEOILDLG_H__73AD308E_D942_44CF_B15A_68F7CA43E95B__INCLUDED_)
