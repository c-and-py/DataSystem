#pragma once
#include "afxdialogex.h"


// AddReaderDlg 对话框

class AddReaderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddReaderDlg)

public:
	AddReaderDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddReaderDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGADDREADER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
