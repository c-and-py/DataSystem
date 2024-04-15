// ListDlg.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "ListDlg.h"


// ListDlg 对话框

IMPLEMENT_DYNAMIC(ListDlg, CDialogEx)

ListDlg::ListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGLIST, pParent)
{
	table.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

ListDlg::~ListDlg()
{
}

void ListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, table);
}


BEGIN_MESSAGE_MAP(ListDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &ListDlg::OnNMRClickList)
	ON_COMMAND(ID_32771, &ListDlg::OnInsert)
	ON_COMMAND(ID_32772, &ListDlg::OnUpdate)
	ON_COMMAND(ID_32773, &ListDlg::OnDelete)
END_MESSAGE_MAP()


// ListDlg 消息处理程序


void ListDlg::OnNMRClickList(NMHDR* pNMHDR, LRESULT* pResult)
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


void ListDlg::OnInsert()
{
	// TODO: 在此添加命令处理程序代码
}


void ListDlg::OnUpdate()
{
	// TODO: 在此添加命令处理程序代码
}


void ListDlg::OnDelete()
{
	// TODO: 在此添加命令处理程序代码
}
