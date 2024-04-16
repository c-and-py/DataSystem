#pragma once
#include "afxdialogex.h"


// AddBorrowDlg 对话框

class AddBorrowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddBorrowDlg)

public:
	AddBorrowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddBorrowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGADDBORROW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	int readerID;
	CString ISBN;
	CString borrowtime;
	int duration;
};
