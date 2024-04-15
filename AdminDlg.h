#pragma once
#include "afxdialogex.h"
#include "ListDlg.h"

// AdminDlg 对话框

class AdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AdminDlg)

public:
	AdminDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	afx_msg void OnNMRClickListAdmin(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl adminlist;
	afx_msg void OnBnClickedButtonqueryallbook();
	void SetListBookMode();
	void SetListReaderMode();
	afx_msg void OnBnClickedButtonallreader();
	afx_msg void OnBnClickedButtonaddbook();
	afx_msg void OnBnClickedButtonaddreader();
	afx_msg void OnBnClickedButtonclear();
};
