
// putVerifyFileDlg.h: 头文件
//

#pragma once


// CputVerifyFileDlg 对话框
class CputVerifyFileDlg : public CDialogEx
{
// 构造
public:
	CputVerifyFileDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUTVERIFYFILE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString FicowGetDirectory();
	CString m_EditPath;
	afx_msg void OnBnClickedButton2();
	CString RetThisPath(void);
	static UINT workThread(LPVOID lParam);
};
