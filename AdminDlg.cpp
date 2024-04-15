// AdminDlg.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "AdminDlg.h"
#include "Tools.h"
#include "LoginDlg.h"
#include "ListDlg.h"
#include"AddBookDlg.h"
#include"AddReaderDlg.h"
// AdminDlg 对话框

IMPLEMENT_DYNAMIC(AdminDlg, CDialogEx)

AdminDlg::AdminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGADMIN, pParent)
{
}

AdminDlg::~AdminDlg()
{
	//ChangeWindow<LoginDlg>((CDialogEx*)(this->GetParent()), IDC_STATICMAIN, IDD_LOGIN);
}

void AdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, adminlist);
}


BEGIN_MESSAGE_MAP(AdminDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &AdminDlg::OnNMRClickListAdmin)
	ON_BN_CLICKED(IDC_BUTTONQUERYALLBOOK, &AdminDlg::OnBnClickedButtonqueryallbook)
	ON_BN_CLICKED(IDC_BUTTONALLREADER, &AdminDlg::OnBnClickedButtonallreader)
	ON_BN_CLICKED(IDC_BUTTONADDBOOK, &AdminDlg::OnBnClickedButtonaddbook)
	ON_BN_CLICKED(IDC_BUTTONADDREADER, &AdminDlg::OnBnClickedButtonaddreader)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, &AdminDlg::OnBnClickedButtonclear)
END_MESSAGE_MAP()



//重写函数，防止回车时窗口消失
void AdminDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void AdminDlg::OnNMRClickListAdmin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		CPoint pt;
		GetCursorPos(&pt);
		CMenu menu;
		menu.LoadMenu(IDR_MENU1);
		CMenu* popmenu;
		popmenu = menu.GetSubMenu(0);
		popmenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}


void AdminDlg::OnBnClickedButtonqueryallbook()
{
	// TODO: 在此添加控件通知处理程序代码
	SetListBookMode();
	std::vector<std::string> rets;
	int row = 7;
	ExecuteSQL("select * from Books;");
	//ExecuteSQL("select * from Books;");
	int i = 0;
	while (FetchData(rets, row)) {
		adminlist.InsertItem(i, _T(""));
		adminlist.SetItemText(i,0, Str2Cstr(rets[0]));
		adminlist.SetItemText(i,1, Str2Cstr(rets[1]));
		adminlist.SetItemText(i,2, Str2Cstr(rets[2]));
		adminlist.SetItemText(i,3, Str2Cstr(rets[3]));
		adminlist.SetItemText(i,4, Str2Cstr(rets[4]));
		adminlist.SetItemText(i,5, Str2Cstr(rets[5]));
		adminlist.SetItemText(i,6, Str2Cstr(rets[6]));
		i++;
	}
}

void AdminDlg::SetListBookMode()
{
	adminlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	adminlist.InsertColumn(0, _T("ISBN"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("名称"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("作者"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("余量"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("总量"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("入库日期"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("出版社"), LVCFMT_LEFT, 100);


	CImageList   m_l;
	m_l.Create(1, 25, TRUE | ILC_COLOR32, 1, 0);   //设置表格的高度 
	adminlist.SetImageList(&m_l, LVSIL_SMALL);
}

void AdminDlg::SetListReaderMode()
{
	adminlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	adminlist.InsertColumn(0, _T("读者证号"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("电话"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("借书ISBN"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("借书日期"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("借书时长"), LVCFMT_LEFT, 100);

	CImageList   m_l;
	m_l.Create(1, 25, TRUE | ILC_COLOR32, 1, 0);   //设置表格的高度 
	adminlist.SetImageList(&m_l, LVSIL_SMALL);
}


void AdminDlg::OnBnClickedButtonallreader()
{
	// TODO: 在此添加控件通知处理程序代码
	SetListReaderMode();
	std::vector<std::string> rets;
	int row = 6;
	ExecuteSQL("select * from Readers;");
	//ExecuteSQL("select * from Books;");
	int i = 0;
	while (FetchData(rets, row)) {
		adminlist.InsertItem(i, _T(""));
		adminlist.SetItemText(i, 0, Str2Cstr(rets[0]));
		adminlist.SetItemText(i, 1, Str2Cstr(rets[1]));
		adminlist.SetItemText(i, 2, Str2Cstr(rets[2]));
		adminlist.SetItemText(i, 3, Str2Cstr(rets[3]));
		adminlist.SetItemText(i, 4, Str2Cstr(rets[4]));
		adminlist.SetItemText(i, 5, Str2Cstr(rets[5]));
		i++;
	}
}


void AdminDlg::OnBnClickedButtonaddbook()
{
	// TODO: 在此添加控件通知处理程序代码
	AddBookDlg dlg;
	dlg.DoModal();
}


void AdminDlg::OnBnClickedButtonaddreader()
{
	// TODO: 在此添加控件通知处理程序代码
	AddReaderDlg dlg;
	dlg.DoModal();
}


void AdminDlg::OnBnClickedButtonclear()
{
	// TODO: 在此添加控件通知处理程序代码
	try {
		while (true) {
			adminlist.DeleteColumn(0);
		}
	}
	catch (...) {
		return;
	}
}
