// AdminDlg.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "AdminDlg.h"
#include "Tools.h"
#include "LoginDlg.h"
// AdminDlg 对话框

IMPLEMENT_DYNAMIC(AdminDlg, CDialogEx)

AdminDlg::AdminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGADMIN, pParent)
{

}

AdminDlg::~AdminDlg()
{
	ChangeWindow<LoginDlg>((CDialogEx*)(this->GetParent()), IDC_STATIC, IDD_LOGIN);
}

void AdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AdminDlg, CDialogEx)
END_MESSAGE_MAP()



//重写函数，防止回车时窗口消失
void AdminDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
