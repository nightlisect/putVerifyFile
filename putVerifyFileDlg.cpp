
// putVerifyFileDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "putVerifyFile.h"
#include "putVerifyFileDlg.h"
#include "afxdialogex.h"
#include "MD5Checksum.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CputVerifyFileDlg 对话框



CputVerifyFileDlg::CputVerifyFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PUTVERIFYFILE_DIALOG, pParent)
	, m_EditPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CputVerifyFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_EditPath);
}

BEGIN_MESSAGE_MAP(CputVerifyFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CputVerifyFileDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CputVerifyFileDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CputVerifyFileDlg 消息处理程序

BOOL CputVerifyFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_EditPath = L"选择文件夹目录";
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CputVerifyFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CputVerifyFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CputVerifyFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CputVerifyFileDlg::FicowGetDirectory()
{
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	bi.pszDisplayName = (LPWSTR)name;
	bi.lpszTitle = L"选择文件夹目录";
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (idl == NULL)
	{
		return CString();
	}
	CString strDirectoryPath;
	SHGetPathFromIDList(idl, strDirectoryPath.GetBuffer(MAX_PATH));
	strDirectoryPath.ReleaseBuffer();
	if (strDirectoryPath.IsEmpty())
	{
		return CString();
	}
	if (strDirectoryPath.Right(strDirectoryPath.GetLength()) != L"\\")
	{
		strDirectoryPath += L"\\";
	}
	return strDirectoryPath;
}

void CputVerifyFileDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditPath = FicowGetDirectory();
	TRACE(m_EditPath + L"\n");
	UpdateData(FALSE);
}


void CputVerifyFileDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_EditPath == CString(L"选择文件夹目录") || m_EditPath == CString())
	{
		AfxMessageBox(L"未选择文件夹目录");
		return;
	}
	GetDlgItem(IDC_STATIC_PUT)->SetWindowTextW(L"校验开始...OK");
	AfxBeginThread(workThread, this);
}

CString CputVerifyFileDlg::RetThisPath(void)
{
	CString strExePath;
	CString strPath;
	GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH + 1);
	int nPos = strPath.ReverseFind(_T('\\'));
	strExePath = strPath.Left(nPos + 1);
	return strExePath;
}

UINT CputVerifyFileDlg::workThread(LPVOID lParam)
{
	CputVerifyFileDlg* pDlg = (CputVerifyFileDlg*)lParam;
	setlocale(LC_CTYPE, "chs");
	CStdioFile m_File;
	CTime c_Time = CTime::GetCurrentTime();
	CString strVerifyPath = pDlg->m_EditPath + L"Verify.txt";
	if (!m_File.Open(strVerifyPath, CFile::modeCreate | CFile::modeWrite))
	{
		pDlg->GetDlgItem(IDC_STATIC_PUT)->SetWindowTextW(L"打开记录文件失败");
		return 0;
	}
	pDlg->GetDlgItem(IDC_STATIC_PUT)->SetWindowTextW(L"打开记录文件...OK");
	m_File.SeekToEnd();
	m_File.WriteString(c_Time.Format(L"%Y-%m-%d %H:%M:%S") + L"\n");
	CFileFind cFind;
	BOOL bWorking = cFind.FindFile(pDlg->m_EditPath + L"/*", 0);
	while (bWorking)
	{
		bWorking = cFind.FindNextFileW();
		CString strPath = cFind.GetFileName();
		if (cFind.IsDots() || cFind.IsDirectory() || cFind.IsHidden() || cFind.IsSystem() ||
			cFind.IsTemporary() || cFind.IsReadOnly())
		{
			continue;
		}
		else
		{
			TRACE(cFind.GetFileName() + L"\n");
			if (cFind.GetFileName()==CString(L"Verify.txt"))
			{
				continue;
			}
			m_File.SeekToEnd();
			CFile m_CFile;
			CString onlyStr = pDlg->m_EditPath + cFind.GetFileName();
			if (!m_CFile.Open(onlyStr, CFile::shareDenyRead | CFile::shareDenyWrite))
			{
				TRACE(L"%d\n", GetLastError());
				m_File.WriteString(cFind.GetFileName() + L"," + L"\n");
				pDlg->GetDlgItem(IDC_STATIC_PUT)->SetWindowTextW(cFind.GetFileName() + L"...ERROR");
			}
			else
			{
				m_File.WriteString(cFind.GetFileName() + L"," + CMD5Checksum::GetMD5(m_CFile) + L"\n");
				m_CFile.Close();
				pDlg->GetDlgItem(IDC_STATIC_PUT)->SetWindowTextW(cFind.GetFileName() + L"...OK");
			}
		}
		Sleep(1500);
	}
	pDlg->GetDlgItem(IDC_STATIC_PUT)->SetWindowTextW(L"验证完成...OK");
	cFind.Close();
	m_File.Close();
	return 0;
}
