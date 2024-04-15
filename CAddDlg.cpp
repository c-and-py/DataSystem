// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "CAddDlg.h"
#include"listcontrl.h"


// CAddDlg 对话框

IMPLEMENT_DYNAMIC(CAddDlg, CDialogEx)

CAddDlg::CAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGadd, pParent)
	, xuehao(_T(""))
	, name(_T(""))
	, sex(_T(""))
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITxuehao, xuehao);
	DDX_Text(pDX, IDC_EDITxingming, name);
	DDX_Text(pDX, IDC_EDITsex, sex);
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddDlg 消息处理程序


void CAddDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
	//{
	//	xuehao = ;
	//	name = m_Add_name;
	//	sex = m_Add_gene;
	//	
	//	m_StuInformation.InsertItem(list_row, _T(""));						// 插入行
	//	m_StuInformation.SetItemText(list_row, 0, Str_StuId);				// 设置第2列(学号)
	//	m_StuInformation.SetItemText(list_row, 1, Str_Name);				// 设置第3列(姓名)
	//	m_StuInformation.SetItemText(list_row, 2, Str_Gene);				// 设置第4列(性别)
	//	
	//	list_row++;   //list_row为list Ctrl表格中显示的数据的行数，便于后期操作，在头文件中定义

	//}
	//
}
