// AddBorrowDlg.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "AddBorrowDlg.h"


// AddBorrowDlg 对话框

IMPLEMENT_DYNAMIC(AddBorrowDlg, CDialogEx)

AddBorrowDlg::AddBorrowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGADDBORROW, pParent)
	, readerID(0)
	, ISBN(_T(""))
	, borrowtime(_T(""))
	, duration(0)
	, durationtext(_T("借书时长"))
{

}

AddBorrowDlg::~AddBorrowDlg()
{
}

void AddBorrowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, readerID);
	DDX_Text(pDX, IDC_EDIT4, ISBN);
	DDX_Text(pDX, IDC_EDIT5, borrowtime);
	DDX_Text(pDX, IDC_EDIT6, duration);
	DDX_Text(pDX, IDC_STATICDRRATION, durationtext);
}


BEGIN_MESSAGE_MAP(AddBorrowDlg, CDialogEx)
END_MESSAGE_MAP()


// AddBorrowDlg 消息处理程序


