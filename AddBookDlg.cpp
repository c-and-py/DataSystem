﻿// AddBookDlg.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "AddBookDlg.h"
#include "Tools.h"

// AddBookDlg 对话框

IMPLEMENT_DYNAMIC(AddBookDlg, CDialogEx)

AddBookDlg::AddBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGADDBOOK, pParent)
	, bookname(_T(""))
	, isbn(_T(""))
	, author(_T(""))
	, intime(_T(""))
	, num(_T(""))
	, press(_T(""))
	, totalnum(_T(""))
	, intimetext(_T("入库时间:"))
	, remainnumtext(_T("余量:"))
	, presstext(_T("出版社:"))
	, totalnumtext(_T("总量:"))
{

}

AddBookDlg::~AddBookDlg()
{
}

void AddBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, bookname);
	DDX_Text(pDX, IDC_EDIT2, isbn);
	DDX_Text(pDX, IDC_EDIT3, author);
	DDX_Text(pDX, IDC_EDIT4, intime);
	DDX_Text(pDX, IDC_EDIT5, num);
	DDX_Text(pDX, IDC_EDIT6, press);
	DDX_Text(pDX, IDC_EDIT7, totalnum);
	DDX_Text(pDX, IDC_STATICINTIMETEXT, intimetext);
	DDX_Text(pDX, IDC_STATICREMAINTEXT, remainnumtext);
	DDX_Text(pDX, IDC_STATICPRESSTEXT, presstext);
	DDX_Text(pDX, IDC_STATICNUMTEXT, totalnumtext);
}


BEGIN_MESSAGE_MAP(AddBookDlg, CDialogEx)
END_MESSAGE_MAP()


// AddBookDlg 消息处理程序
