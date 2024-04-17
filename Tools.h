//#pragma once

#include "pch.h"
#include <iostream>
#include <sql.h> 
#include <sqlext.h> 
#include<sqltypes.h>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>

#ifndef TOOLS_H
#define TOOLS_H

struct Column {
	Column();
	Column(std::string columnname, std::string datatype);
	std::string columnname;
	std::string datatype;
};

//�������ݿ�
//datasource:����Դ
//username:�û���
//password:����
//ע�ⲻҪʹ��unicode�ַ���
bool ConnectSQL(std::string datasource,std::string username,std::string password);

//ִ��SQL���
//sql:Ҫִ�е����
bool ExecuteSQL(std::string sql);

//������
//tablename:����
//columns:������
bool CreateTable(std::string tablename, std::vector<Column> columns ,int keynum = 1);

//����ͼ���
bool CreateBookTable(std::string tablename);
//�������߱�
bool CreateReaderTable(std::string tablename);
//���������
bool CreateBorrowTable(std::string tablename);
//ͼ�������߱�ISBNԼ��
bool ForeignKeyISBN();
//����֤Լ��
bool ForeignKeyReaderid();
//������������
bool CreateBorrowTrigger();
//������������
bool CreateReturnTrigger();
//�����������½���
bool CreateUpdateTrigger();
//��������Ա��ͼ
bool CreateAdminView();
//����������ͼ
bool CreateReaderTable();

//��ѯ���б�
//δ���
bool ShowTables();

//����һ������
//δ���
bool Insert();

//������
bool InsertBook(std::string ISBN, std::string name, std::string author, int remainnum, int num, std::string intime, std::string press);
//ɾ����
bool DeleteBook(std::string ISBN);
//������
bool UpdateBook(std::string ISBN, std::string name, std::string author, int remainnum, int num, std::string intime, std::string press);
//�������
bool InsertReader(int readerID, std::string name, int phone);
//ɾ������
bool DeleteReader(int readerID);
//���¶���
bool UpdateReader(int readerID, std::string name, int phone);

//����
bool InsertBorrow(int readerID, std::string ISBN, std::string borrowtime,int duration);

bool DeleteBorrow(int readerID,std::string isbn);
bool UpdateBorrow(int readerID, std::string ISBN, int duration);
//bool BorrowBook(int readerID, std::string ISBN,int borrowDuration);
//���ٿ��
bool DecreaseBookNum(std::string ISBN, int decreaseNum);

//ɾ������
//δ���
bool Delete();

//��������
//δ���
bool Update();

//��ȡһ�в�ѯ���
//rets:������
bool GetResult(std::vector<SQLCHAR*> rets, const int& row);
bool FetchData(std::vector<std::string>& rets, const int& row);

//��ָ��λ�û�ͼ
//pdc:��GetDc()��ȡ
//imageResourceId:ͼ��id
//x:X���꣬���Ͻ�
//y:Y���꣬���Ͻ�
void DrawResourceImage(CDC* pDC, int imageResourceId, int x, int y);
//��ָ��λ�û�ͼ
//pdc:��GetDc()��ȡ
//imageResourceId:ͼ��id
//x:X���꣬���Ͻ�
//y:Y���꣬���Ͻ�
//width:ͼƬ��
//height:ͼƬ��
void DrawResourceImage(CDC* pDC, int imageResourceId, int x, int y, int width, int height);

std::vector<CString> ReadTxt(CString filepath);

//��context�е�cstatic�����л���winid���ڣ����ڽ���ת��
// T:����id��Ӧ����
//context:����picturecontrol���࣬һ����this
//cstatic:picturecontrol��id
//winid:����id
//������.h��
template<typename T>
void ChangeWindow(CDialogEx* context, int cstatic, int winid)
{
	T* dlg = new T();
	//��������
	dlg->Create(winid, context);
	//��ȡCStatic��λ�ô���
	CRect re;
	((CStatic*)(context->GetDlgItem(cstatic)))->GetWindowRect(&re);
	//����ϵת��
	context->ScreenToClient(re);
	//�ƶ�
	dlg->MoveWindow(re);
	//��ʾ
	dlg->ShowWindow(SW_SHOW);

	dlg->ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	//return dlg;
}

//��std::stringתΪCString
CString Str2Cstr(std::string str);
#endif // !TOOLS_H
