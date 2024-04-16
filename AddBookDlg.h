#pragma once
#include "afxdialogex.h"


// AddBookDlg 对话框

class AddBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddBookDlg)

public:
	AddBookDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddBookDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGADDBOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString bookname;
	CString isbn;
	CString author;
	CString intime;
	CString num;
	CString press;
	CString totalnum;
};
