#pragma once
#include "afxdialogex.h"


// listcontrl 对话框

class listcontrl : public CDialogEx
{
	DECLARE_DYNAMIC(listcontrl)

public:
	listcontrl(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~listcontrl();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_StuInformation;
	CString Str_StuId, Str_Name, Str_Gene;
	int list_row;
	CMenu m_Menu;
	  virtual BOOL OnInitDialog();
	  afx_msg void On32773charu();
	 // afx_msg void On32774tianjia();
	  afx_msg void On32778xiugai();
	  afx_msg void Onmenushanchu();
};
