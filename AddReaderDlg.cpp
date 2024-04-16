// AddReaderDlg.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "AddReaderDlg.h"
#include "Tools.h"

// AddReaderDlg 对话框

IMPLEMENT_DYNAMIC(AddReaderDlg, CDialogEx)

AddReaderDlg::AddReaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGADDREADER, pParent)
	, readerid(0)
	, readername(_T(""))
	, phone(0)
{

}

AddReaderDlg::~AddReaderDlg()
{
}

void AddReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, readerid);
	DDX_Text(pDX, IDC_EDIT2, readername);
	DDX_Text(pDX, IDC_EDIT3, phone);
}


BEGIN_MESSAGE_MAP(AddReaderDlg, CDialogEx)
END_MESSAGE_MAP()


// AddReaderDlg 消息处理程序
