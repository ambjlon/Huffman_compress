// heoilDlg.cpp : implementation file
//

#include "stdafx.h"
#include <afxcmn.h>
#include "heoil.h"
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "heoilDlg.h"
#include "HuffmanTreeNode.h"
#include "HCompress.h"
#include "HDeCompress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeoilDlg dialog

CHeoilDlg::CHeoilDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHeoilDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHeoilDlg)
	m_dstfilename = _T("");
	m_srcfilename = _T("");
	m_Byte = 0;
	m_Time = 0;
	m_Ratio = 0.0;
	m_DeCompressedFileM = 0.0;
	m_SourceFileKB = 0.0;
	m_check = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	dftdstfilename = "orgin";
	srckb = 0;
}

void CHeoilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHeoilDlg)
	DDX_Control(pDX, IDC_PROGRESS2, MyCtrl);
	DDX_Text(pDX, IDC_EDITDESTINATIONFILE, m_dstfilename);
	DDX_Text(pDX, IDC_EDITSOURCEFILE, m_srcfilename);
	DDX_Text(pDX, IDC_EDITByte, m_Byte);
	DDX_Text(pDX, IDC_EDITTime, m_Time);
	DDX_Text(pDX, IDC_EDITRatio, m_Ratio);
	DDX_Text(pDX, IDC_EDITKB, m_DeCompressedFileM);
	DDX_Text(pDX, IDC_EDITKB1, m_SourceFileKB);
	DDX_Check(pDX, IDC_CHECK1, m_check);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHeoilDlg, CDialog)
//{{AFX_MSG_MAP(CHeoilDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(ID_OPENFILE, OnOpenfile)
ON_BN_CLICKED(IDC_CHANGE, OnChangeDirectory)
ON_BN_CLICKED(ID_COMPRESS, OnCompress)
ON_BN_CLICKED(ID_DECOMPRESS, OnDecompress)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_EN_UPDATE(IDC_EDITDESTINATIONFILE, OnUpdateEditdestinationfile)
	ON_BN_CLICKED(ID_COPYRIGHT, OnCopyright)
	ON_BN_CLICKED(ID_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(ID_Decode, OnDecode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeoilDlg message handlers

BOOL CHeoilDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHeoilDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHeoilDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHeoilDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHeoilDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	
}

void CHeoilDlg::OnOpenfile() 
{
	// TODO: Add your control notification handler code here
	unsigned char i;
	int k;
	FILE *temp;
	CString tmp;
	CFileDialog filedlg(true);
	if(filedlg.DoModal() == IDOK)
	{
		srcfilename = filedlg.GetPathName();
		FileExt = filedlg.GetFileExt();
		FileName = filedlg.GetFileName();
	}
	m_srcfilename = srcfilename;
	this->UpdateData(false);
	if(FileExt != "huff")
	{
		tmp = srcfilename;
		srcfilename.Replace((LPCTSTR)FileExt,"huff");
		dstfilename = dftdstfilename = srcfilename;
		srcfilename = tmp;
		m_dstfilename = dftdstfilename;
		this->UpdateData(false);
		
	}
	else
	{
		tmp = srcfilename;
		k = srcfilename.ReverseFind('.');
		
		srcfilename.Delete(k,5);
		
		temp = fopen((LPCTSTR)tmp,"rb");
		fread(& i,1,1,temp);
		s[0] = '.';
		for(k = 1;k <= i;k ++)
			fread(& s[k],1,1,temp);
		s[k] = 0;
		fclose(temp);
		
		srcfilename.Insert(100000,s);
		dstfilename = dftdstfilename = srcfilename;
		srcfilename = tmp;
		m_dstfilename = dftdstfilename;
		this->UpdateData(false);
		
	}
}

void CHeoilDlg::OnChangeDirectory() 
{
	// TODO: Add your control notification handler code here
	CString tmp;
	int i;
	i = FileName.Find(FileExt);
	FileName.Delete(i - 1,FileExt.GetLength() + 1);
	FileName.Insert(100000,s);
	CFileDialog filedlg(false,NULL,FileName);
	if(filedlg.DoModal() == IDOK)
		tmp = filedlg.GetPathName();

	m_dstfilename = dstfilename = tmp;
	this->UpdateData(false);
	this->UpdateData(true);
}

void CHeoilDlg::OnCompress() 
{
	// TODO: Add your control notification handler code here
	int k;
	unsigned char i;
	signed char j;
	
	
	
	if(! srcfilename.IsEmpty())
	{
		if(FileExt == "huff")
			MessageBox("source file name is invalid (postfix shouldn't be'.huff'),fill up again!");
		else
		{
			HCompress huffman((LPCTSTR)srcfilename,(LPCTSTR)dstfilename,this);
			FILE *temp = fopen((LPCTSTR)dstfilename,"wb");
			i = FileExt.GetLength();
			fwrite(& i,1,1,temp);
			for(k = 0;k < i;k ++)
			{
				j = FileExt.GetAt(k);
				fwrite(& j,1,1,temp);
			}
			fclose(temp);
			
			
			huffman.IniateHTree();
			
			m_SourceFileKB = (float)huffman.content / 1024;
			
			huffman.BulidHTree();
			huffman.EditCode();
			huffman.BulidFHTree();
			huffman.WriteDisk();
			if(huffman.numint == 0)
				m_DeCompressedFileM = ( float )huffman.totalbits / (8 * 1024);
			else
			{
				m_DeCompressedFileM = m_DeCompressedFileM + huffman.numint * (LONG_MAX / (8 * 1024));
				m_DeCompressedFileM = m_DeCompressedFileM + (float)huffman.totalbits / (8 *1024);
			}
			m_Byte = huffman.leafnum;
			m_Ratio = (m_DeCompressedFileM / m_SourceFileKB) * 100;
			
			this->UpdateData(false);
			MessageBox("Compress task is completed!");
		}
	}
	else
		MessageBox("source file name is empty ,fill up again!");
}

void CHeoilDlg::OnDecompress() 
{
	// TODO: Add your control notification handler code here
	int i;
	
	
	if(! srcfilename.IsEmpty())
	{
		if(FileExt != "huff")
			MessageBox("source file name is invalid (postfix is '.huff'),fill up again!");
		else
		{
			HDeCompress huffman((LPCTSTR)srcfilename,(LPCTSTR)dstfilename,this);
			huffman.DeCompress();
			CFile tmpp((LPCTSTR) dstfilename,1);
			srckb = tmpp.GetLength();
			m_Byte = -1;
			m_Ratio = -1;
			m_SourceFileKB = (double)srckb / 1024;
			if(huffman.numint == 0)
				m_DeCompressedFileM = ( float )huffman.totalbits / (8 * 1024);
			else
			{
				m_DeCompressedFileM = m_DeCompressedFileM + huffman.numint * (LONG_MAX / (8 * 1024));
				m_DeCompressedFileM = m_DeCompressedFileM + (float)huffman.totalbits / (8 *1024);
			}
			this->UpdateData(false);
			MessageBox("DeCompress task is completed!");
		}
	}
	else
		MessageBox("source file name is empty ,fill up again!");
}

void CHeoilDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	if(!m_check)
	m_check = true;
	else
		m_check = false;
}



void CHeoilDlg::OnUpdateEditdestinationfile() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	this->UpdateData(true);
	dstfilename = m_dstfilename;
	
}



void CHeoilDlg::OnCopyright() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CHeoilDlg::OnEncrypt() 
{
	// TODO: Add your control notification handler code here
	MessageBox("No this founction in this version!");
}

void CHeoilDlg::OnDecode() 
{
	// TODO: Add your control notification handler code here
	MessageBox("No this founction in this version!");
}
