// LoginDlg.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "Tools.h"
#include"AdminDlg.h"
#include "ListDlg.h"

// LoginDlg 对话框

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, datasource(_T(""))
	, username(_T(""))
	, password(_T(""))
{
	//可删，在初始化时直接进行数据库连接
//	if (ConnectSQL("SQL", "ZDAdmin", "123456")) {
//		MessageBox(_T("连接数据库成功"));
//		if (ExecuteSQL("create table testtable(id int,value int);")) {
//			MessageBox(_T("创建成功"));
//		};
//	}
//	else {
//		MessageBox(_T("连接数据库失败"));
//	};
}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, datasource);
	DDX_Text(pDX, IDC_EDIT1, username);
	DDX_Text(pDX, IDC_EDIT2, password);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(ID_WIZFINISH, &LoginDlg::OnBnClickedWizfinish)
END_MESSAGE_MAP()


// LoginDlg 消息处理程序


void LoginDlg::OnBnClickedWizfinish()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (ConnectSQL(datasource.GetBuffer(), username.GetBuffer(), password.GetBuffer())) {
		ChangeWindow<AdminDlg>((CDialogEx*)(this->GetParent()), IDC_STATICMAIN, IDD_DIALOGADMIN);
		MessageBox(_T("登录成功"));
		//ExecuteSQL("select * from Books;");
		//std::vector<SQLCHAR*> rets;
		//int row = 1;
		//GetResult(rets,row);
		delete this;
	}
	else {
		MessageBox(_T("登录失败，请检查数据源、用户名和密码！"));
	};
}


//回车时调用
void LoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
	UpdateData(TRUE);
	if (ConnectSQL(datasource.GetBuffer(), username.GetBuffer(), password.GetBuffer())) {
		ChangeWindow<AdminDlg>((CDialogEx*)(this->GetParent()), IDC_STATICMAIN, IDD_DIALOGADMIN);
		MessageBox(_T("登录成功"));
		delete this;
	}
	else {
		MessageBox(_T("登录失败，请检查数据源、用户名和密码！"));
	};
}
