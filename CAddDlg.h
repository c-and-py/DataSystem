#pragma once
#include "afxdialogex.h"


// CAddDlg 对话框

class CAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDlg)

public:
	CAddDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGadd };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString xuehao;
	CString name;
	CString sex;

	afx_msg void OnBnClickedOk();//确定键的响应函数
};
