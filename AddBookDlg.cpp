// AddBookDlg.cpp: 实现文件
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
{

}

AddBookDlg::~AddBookDlg()
{
}

void AddBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddBookDlg, CDialogEx)
END_MESSAGE_MAP()


// AddBookDlg 消息处理程序
