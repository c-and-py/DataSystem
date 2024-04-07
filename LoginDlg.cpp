// LoginDlg.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "Tools.h"

// LoginDlg 对话框

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{
	//可删，在初始化时直接进行数据库连接
	if (ConnectSQL("SQL", "ZDAdmin", "123456")) {
		MessageBox(_T("连接数据库成功"));
	}
	else {
		MessageBox(_T("连接数据库失败"));
	};
}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
END_MESSAGE_MAP()


// LoginDlg 消息处理程序
