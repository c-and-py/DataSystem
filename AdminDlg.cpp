// AdminDlg.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "AdminDlg.h"
#include "Tools.h"
#include "LoginDlg.h"
#include"AddBookDlg.h"
#include"AddReaderDlg.h"
// AdminDlg 对话框

IMPLEMENT_DYNAMIC(AdminDlg, CDialogEx)

AdminDlg::AdminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGADMIN, pParent)
{
	mode = 0;
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
	ON_COMMAND(ID_32771, &AdminDlg::OnInsert)
	ON_COMMAND(ID_32772, &AdminDlg::OnUpdate)
	ON_COMMAND(ID_32773, &AdminDlg::OnDelete)
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
	OnBnClickedButtonclear();
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
	mode = BOOK;
	adminlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	adminlist.InsertColumn(0, _T("出版社"), LVCFMT_LEFT, 100);;
	adminlist.InsertColumn(0, _T("入库日期"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("总量"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("余量"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("作者"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("名称"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("ISBN"), LVCFMT_LEFT, 100);

	CImageList   m_l;
	m_l.Create(1, 25, TRUE | ILC_COLOR32, 1, 0);   //设置表格的高度 
	adminlist.SetImageList(&m_l, LVSIL_SMALL);
}

void AdminDlg::SetListReaderMode()
{
	mode = READER;
	adminlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	adminlist.InsertColumn(0, _T("借书时长"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("借书日期"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("借书ISBN"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("电话"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, 100);
	adminlist.InsertColumn(0, _T("读者证号"), LVCFMT_LEFT, 100);
	CImageList   m_l;
	m_l.Create(1, 25, TRUE | ILC_COLOR32, 1, 0);   //设置表格的高度 
	adminlist.SetImageList(&m_l, LVSIL_SMALL);
}


void AdminDlg::OnBnClickedButtonallreader()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonclear();
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
	INT_PTR nResponse;
	nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
		if (InsertBook(dlg.isbn.GetBuffer(), dlg.bookname.GetBuffer(), dlg.author.GetBuffer(), _ttoi(dlg.num), _ttoi(dlg.totalnum),
			dlg.intime.GetBuffer(), dlg.press.GetBuffer())) {
			MessageBox("添加成功");
		}
		else {
			MessageBox("添加失败");
		}
	}
}


void AdminDlg::OnBnClickedButtonaddreader()
{
	// TODO: 在此添加控件通知处理程序代码
	AddReaderDlg dlg;
	INT_PTR nResponse;
	nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
		if (InsertReader(dlg.readerid, dlg.readername.GetBuffer(), dlg.phone, dlg.isbn.GetBuffer(),
			dlg.borrowtime.GetBuffer(), dlg.borrowduration)) {
			MessageBox("添加成功");
		}
		else {
			MessageBox("添加失败");
		}
	}
}


void AdminDlg::OnBnClickedButtonclear()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取列数
	int nColumns = adminlist.GetHeaderCtrl()->GetItemCount();

	// 逐列删除
	for (int i = 0; i < nColumns; ++i) {
		adminlist.DeleteColumn(0);
	}
	// 清除所有行
	adminlist.DeleteAllItems();

	mode = NONE;
}


void AdminDlg::OnInsert()
{
	// TODO: 在此添加命令处理程序代码
	AddBookDlg addbookdlg;
	AddReaderDlg addreaderdlg;
	INT_PTR nResponse;
	int nSelectedItem = adminlist.GetNextItem(-1, LVNI_SELECTED);
	if (nSelectedItem != -1) {
		switch (mode)
		{
		case 0:
			break;
		case 1:
			OnBnClickedButtonaddbook();
			break;
		case 2:
			OnBnClickedButtonaddreader();
			break;
		default:
			break;
		}
	}
	else {
		// 没有选中的项
	}
}


void AdminDlg::OnUpdate()
{
	// TODO: 在此添加命令处理程序代码
	int nSelectedItem = adminlist.GetNextItem(-1, LVNI_SELECTED);
	if (nSelectedItem != -1) {
		switch (mode)
		{
		case 0: 
			break;
		case 1:{
			AddBookDlg dlg;
			INT_PTR nResponse;
			dlg.isbn = adminlist.GetItemText(nSelectedItem, 0).GetBuffer();
			dlg.bookname = adminlist.GetItemText(nSelectedItem, 1).GetBuffer();
			dlg.author = adminlist.GetItemText(nSelectedItem, 2).GetBuffer();
			dlg.num = adminlist.GetItemText(nSelectedItem, 3).GetBuffer();
			dlg.totalnum = adminlist.GetItemText(nSelectedItem, 4).GetBuffer();
			dlg.intime = adminlist.GetItemText(nSelectedItem, 5).GetBuffer();
			dlg.press = adminlist.GetItemText(nSelectedItem, 6).GetBuffer();
			//dlg.UpdateData(FALSE);
			nResponse = dlg.DoModal();
			if (nResponse == IDOK) {
				if (UpdateBook(dlg.isbn.GetBuffer(), dlg.bookname.GetBuffer(), dlg.author.GetBuffer(), _ttoi(dlg.num), _ttoi(dlg.totalnum),
					dlg.intime.GetBuffer(), dlg.press.GetBuffer())) {
					MessageBox(_T("修改成功"));
				}
				else {
					MessageBox(_T("修改失败"));
				}
			}
		}
			break;
		case 2:
		{
			AddReaderDlg dlg;
			INT_PTR nResponse;
			dlg.readerid = _ttoi(adminlist.GetItemText(nSelectedItem, 0).GetBuffer());
			dlg.readername = adminlist.GetItemText(nSelectedItem, 1).GetBuffer();
			dlg.phone = _ttoi(adminlist.GetItemText(nSelectedItem, 2).GetBuffer());
			dlg.isbn = adminlist.GetItemText(nSelectedItem, 3).GetBuffer();
			dlg.borrowtime = adminlist.GetItemText(nSelectedItem, 4).GetBuffer();
			dlg.borrowduration = _ttoi(adminlist.GetItemText(nSelectedItem, 5).GetBuffer());
			//dlg.UpdateData(FALSE);
			nResponse = dlg.DoModal();
			if (nResponse == IDOK) {
				if (UpdateReader(dlg.readerid, dlg.readername.GetBuffer(), dlg.phone, dlg.isbn.GetBuffer(),
					dlg.borrowtime.GetBuffer(), dlg.borrowduration)) {
					MessageBox(_T("修改成功"));
				}
				else {
					MessageBox(_T("修改失败"));
				}
			}
		}
			break;
		default:
			break;
		}
	}
	else {
		// 没有选中的项
	}
}


void AdminDlg::OnDelete()
{
	// TODO: 在此添加命令处理程序代码
	int nSelectedItem = adminlist.GetNextItem(-1, LVNI_SELECTED);
	if (nSelectedItem != -1) {
		switch (mode)
		{
		case 0:
			break;
		case 1:
		{
			std::string isbn = adminlist.GetItemText(nSelectedItem, 0).GetBuffer();
			if (DeleteBook(isbn)) {
				MessageBox("删除成功");
			}
			else {
				MessageBox("删除失败");
			}
		}
			break;
		case 2:
		{
			int readerid = _ttoi(adminlist.GetItemText(nSelectedItem, 0));
			if (DeleteReader(readerid)) {
				MessageBox("删除成功");
			}
			else {
				MessageBox("删除失败");
			}
		}
			break;
		default:
			break;
		}
	}
	else {
		// 没有选中的项
	}
}
