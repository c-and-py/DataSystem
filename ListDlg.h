#pragma once
#include "afxdialogex.h"


// ListDlg 对话框

class ListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ListDlg)

public:
	ListDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ListDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl table;
	afx_msg void OnNMRClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsert();
	afx_msg void OnUpdate();
	afx_msg void OnDelete();
};
