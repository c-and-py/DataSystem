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

//链接数据库
//datasource:数据源
//username:用户名
//password:密码
//注意不要使用unicode字符集
bool ConnectSQL(std::string datasource,std::string username,std::string password);

//执行SQL语句
//sql:要执行的语句
bool ExecuteSQL(std::string sql);

//创建表
//tablename:表名
//columns:列数组
bool CreateTable(std::string tablename, std::vector<Column> columns ,int keynum = 1);

//创建图书表
bool CreateBookTable(std::string tablename);
//创建读者表
bool CreateReaderTable(std::string tablename);
//创建借书表
bool CreateBorrowTable(std::string tablename);
//图书表与读者表ISBN约束
bool ForeignKeyISBN();
//读者证约束
bool ForeignKeyReaderid();
//触发器，借书
bool CreateBorrowTrigger();
//触发器，还书
bool CreateReturnTrigger();
//触发器，更新借书
bool CreateUpdateTrigger();
//创建管理员视图
bool CreateAdminView();
//创建读者视图
bool CreateReaderTable();

//查询所有表
//未完成
bool ShowTables();

//插入一条数据
//未完成
bool Insert();

//插入书
bool InsertBook(std::string ISBN, std::string name, std::string author, int remainnum, int num, std::string intime, std::string press);
//删除书
bool DeleteBook(std::string ISBN);
//更新书
bool UpdateBook(std::string ISBN, std::string name, std::string author, int remainnum, int num, std::string intime, std::string press);
//插入读者
bool InsertReader(int readerID, std::string name, int phone);
//删除读者
bool DeleteReader(int readerID);
//更新读者
bool UpdateReader(int readerID, std::string name, int phone);

//借书
bool InsertBorrow(int readerID, std::string ISBN, std::string borrowtime,int duration);

bool DeleteBorrow(int readerID,std::string isbn);
bool UpdateBorrow(int readerID, std::string ISBN, int duration);
//bool BorrowBook(int readerID, std::string ISBN,int borrowDuration);
//减少库存
bool DecreaseBookNum(std::string ISBN, int decreaseNum);

//删除数据
//未完成
bool Delete();

//更新数据
//未完成
bool Update();

//获取一行查询结果
//rets:数据列
bool GetResult(std::vector<SQLCHAR*> rets, const int& row);
bool FetchData(std::vector<std::string>& rets, const int& row);

//在指定位置画图
//pdc:用GetDc()获取
//imageResourceId:图像id
//x:X坐标，左上角
//y:Y坐标，左上角
void DrawResourceImage(CDC* pDC, int imageResourceId, int x, int y);
//在指定位置画图
//pdc:用GetDc()获取
//imageResourceId:图像id
//x:X坐标，左上角
//y:Y坐标，左上角
//width:图片宽
//height:图片高
void DrawResourceImage(CDC* pDC, int imageResourceId, int x, int y, int width, int height);

std::vector<CString> ReadTxt(CString filepath);

//将context中的cstatic窗口切换成winid窗口，用于界面转换
// T:窗口id对应的类
//context:包含picturecontrol的类，一般填this
//cstatic:picturecontrol的id
//winid:窗口id
//定义在.h中
template<typename T>
void ChangeWindow(CDialogEx* context, int cstatic, int winid)
{
	T* dlg = new T();
	//创建窗口
	dlg->Create(winid, context);
	//获取CStatic的位置窗口
	CRect re;
	((CStatic*)(context->GetDlgItem(cstatic)))->GetWindowRect(&re);
	//坐标系转换
	context->ScreenToClient(re);
	//移动
	dlg->MoveWindow(re);
	//显示
	dlg->ShowWindow(SW_SHOW);

	dlg->ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	//return dlg;
}

//将std::string转为CString
CString Str2Cstr(std::string str);
#endif // !TOOLS_H
