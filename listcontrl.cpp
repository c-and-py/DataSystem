// listcontrl.cpp: 实现文件
//

#include "pch.h"
#include "DataSystem.h"
#include "afxdialogex.h"
#include "listcontrl.h"
#include"CAddDlg.h"


// listcontrl 对话框

IMPLEMENT_DYNAMIC(listcontrl, CDialogEx)

listcontrl::listcontrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

listcontrl::~listcontrl()
{
}

void listcontrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTcontrl, m_StuInformation);
}
BOOL listcontrl::OnInitDialog()
{
	m_Menu.LoadMenu(IDR_MENU1);//IDR_MENU1是menu控件的ID
	m_StuInformation.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	// 整行选择、网格线
	m_StuInformation.InsertColumn(0, _T("学号"), LVCFMT_LEFT, 100);	// 插入第2列的列名
	m_StuInformation.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 100);	// 插入第3列的列名
	m_StuInformation.InsertColumn(2, _T("性别"), LVCFMT_LEFT, 100);	// 插入第4列的列名
	//设置行高
	CImageList   m_l;
	m_l.Create(1, 25, TRUE | ILC_COLOR32, 1, 0);   //设置表格的高度 
	m_StuInformation.SetImageList(&m_l, LVSIL_SMALL);
	//设置字体
	CFont m_font;
	m_font.CreatePointFont(140, "新宋体"); //设置标题栏的高度及字体
	m_StuInformation.SetFont(&m_font);

	m_StuInformation.SetColumnWidth(0, 120); //设置列宽
	m_StuInformation.SetColumnWidth(1, 120);
	m_StuInformation.SetColumnWidth(2, 80);
	m_StuInformation.SetColumnWidth(3, 80);
	m_StuInformation.SetColumnWidth(4, 80);
	m_StuInformation.SetColumnWidth(5, 80);

	for (int i = 0; i < 1; i++)
	{ //不断获取下一组结果

		m_StuInformation.InsertItem(i, _T(""));						// 插入行
		m_StuInformation.SetItemText(i, 0, Str_StuId);				// 设置第2列(学号)
		m_StuInformation.SetItemText(i, 1, Str_Name);				// 设置第3列(姓名)
		m_StuInformation.SetItemText(i, 2, Str_Gene);				// 设置第4列(性别)
		list_row++;  //list_row为list Ctrl表格中显示的数据的行数，便于后期操作，在头文件中定义


	}

	if (list_row = 0)
	{
		return false;
	}
	else
	return true;
}
// listcontrl 消息处理程序

BEGIN_MESSAGE_MAP(listcontrl, CDialogEx)
	ON_COMMAND(ID_32773, &listcontrl::On32773charu)
	//ON_COMMAND(ID_32774, &listcontrl::On32774tianjia)
	ON_COMMAND(ID_32778, &listcontrl::On32778xiugai)
	ON_COMMAND(ID_menu, &listcontrl::Onmenushanchu)
END_MESSAGE_MAP()

void listcontrl::On32773charu()//插入函数
{
	// TODO: 在此添加命令处理程序代码
	CAddDlg m;
	m.DoModal();

}


//void listcontrl::On32774tianjia()//添加函数
//{
//	// TODO: 在此添加命令处理程序代码
//}


void listcontrl::On32778xiugai()//修改函数
{
	// TODO: 在此添加命令处理程序代码
}


void listcontrl::Onmenushanchu()//删除函数
{
	// TODO: 在此添加命令处理程序代码
	int i, iState;
	int nItemSelected = m_StuInformation.GetSelectedCount();
	int nItemCount = m_StuInformation.GetItemCount();
	if (nItemSelected < 1)
		return;
	for (i = nItemCount - 1; i >= 0; i--)
	{
		iState = m_StuInformation.GetItemState(i, LVIS_SELECTED);
		if (iState != 0)
		{

			m_StuInformation.DeleteItem(i);
		}
	}

	
}
