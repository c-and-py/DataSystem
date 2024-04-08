#pragma once
#include "afxdialogex.h"
// LoginDlg 对话框
//登录界面
class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedWizfinish();
	// 数据源
	CString datasource;
	// 用户名
	CString username;
	// 密码
	CString password;
};
