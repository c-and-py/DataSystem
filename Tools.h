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
bool CreateTable(std::string tablename, std::vector<Column> columns);

//查询所有表
//未完成
bool ShowTables();

//插入一条数据
//未完成
bool Insert();

//删除数据
//未完成
bool Delete();

//更新数据
//未完成
bool Update();

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
template<typename T>
inline void ChangeWindow(CDialogEx* context, int cstatic, int winid);

//将std::string转为CString
CString Str2Cstr(std::string str);
#endif // !TOOLS_H
