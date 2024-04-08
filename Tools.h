//#pragma once

#include "pch.h"
#include <iostream>
#include <sql.h> 
#include <sqlext.h> 
#include<sqltypes.h>
#include <string>
#include <vector>

#ifndef TOOLS_H
#define TOOLS_H

struct Column {
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
bool CreateTable(std::string tablename, std::vector<Column> columns);

//��ѯ���б�
//δ���
bool ShowTables();

//����һ������
//δ���
bool Insert();

//ɾ������
//δ���
bool Delete();

//��������
//δ���
bool Update();

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
template<typename T>
inline void ChangeWindow(CDialogEx* context, int cstatic, int winid);

//��std::stringתΪCString
CString Str2Cstr(std::string str);
#endif // !TOOLS_H
