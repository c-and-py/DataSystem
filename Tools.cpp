//#pragma once
#include"pch.h"
#include "Tools.h"

SQLRETURN returnmsg = NULL;//返回信息
SQLHENV handleenv = NULL;//环境句柄
SQLHDBC handledbc = NULL;//连接句柄
SQLHSTMT handlestmt = NULL;//语句句柄

bool ConnectSQL(std::string datasource, std::string username, std::string password) {

    // 申请环境句柄
    returnmsg = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handleenv);
    if (returnmsg != SQL_SUCCESS && returnmsg != SQL_SUCCESS_WITH_INFO) {
        std::cout << "无法申请环境句柄" << std::endl;
        return false;
    }

    // 设置环境属性
    returnmsg = SQLSetEnvAttr(handleenv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if (returnmsg != SQL_SUCCESS && returnmsg != SQL_SUCCESS_WITH_INFO) {
        std::cout << "无法设置环境属性" << std::endl;
        SQLFreeHandle(SQL_HANDLE_ENV, handleenv);
        return false;
    }

    // 申请数据库连接句柄
    returnmsg = SQLAllocHandle(SQL_HANDLE_DBC, handleenv, &handledbc);
    if (returnmsg != SQL_SUCCESS && returnmsg != SQL_SUCCESS_WITH_INFO) {
        std::cout << "无法申请数据库连接句柄" << std::endl;
        SQLFreeHandle(SQL_HANDLE_ENV, handleenv);
        return false;
    }

    // 连接数据库,数据源名称，用户标识，密码，
    // 注意不要使用unicode字符集，否则连接不上，字符集改成未设置即可
    returnmsg = SQLConnect(handledbc, (SQLTCHAR*)(datasource.c_str()), SQL_NTS, (SQLTCHAR*)(username.c_str()), SQL_NTS, (SQLTCHAR*)(password.c_str()), SQL_NTS);
    if (returnmsg == SQL_SUCCESS || returnmsg == SQL_SUCCESS_WITH_INFO) {
        std::cout << "数据库连接成功!" << std::endl;
    }
    else {
        std::cout << "数据库连接失败！" << std::endl;
    }

    // 释放句柄
    //SQLFreeHandle(SQL_HANDLE_DBC, handledbc);
    //SQLFreeHandle(SQL_HANDLE_ENV, handleenv);
    if (returnmsg == SQL_SUCCESS || returnmsg == SQL_SUCCESS_WITH_INFO) {
        return true;
    }
    else {
        return false;
    }
}

bool ExecuteSQL(std::string sql)
{
	returnmsg = SQLAllocHandle(SQL_HANDLE_STMT, handledbc, &handlestmt);
	if (returnmsg == SQL_SUCCESS || returnmsg == SQL_SUCCESS_WITH_INFO) {
		std::cout << "语句句柄获取成功!" << std::endl;
	}
	else {
		std::cout << "无法获取语句句柄！" << std::endl;
		return false;
	}
    returnmsg = SQLExecDirect(handlestmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    if (returnmsg == SQL_SUCCESS || returnmsg == SQL_SUCCESS_WITH_INFO) {
		std::cout << "已执行" << sql << std::endl;
        return true;
    }
    else {
		std::cout << "执行失败" << sql << std::endl;
        return false;
    }
}

bool CreateTable(std::string tablename, std::vector<Column> columns)
{
	//拼装create语句
	std::string sql = "create table\t" + tablename + "(";
	for (int i = 0; i < columns.size(); i++) {
		sql += columns[i].columnname + "\t" + columns[i].datatype;
		if (i != columns.size() - 1)sql += ",";
	}
	sql += ")";
	//执行语句
	if (ExecuteSQL(sql)) {
		std::cout << "创建" << tablename << "表成功" << std::endl;
		return true;
	}
	else {
		std::cout << "创建" << tablename << "表失败" << std::endl;
		return false;
	}
}

bool CreateBookTable(std::string tablename)
{
	std::vector<Column> columns;
	columns.push_back(Column("ISBN", "nchar(20)"));
	columns.push_back(Column("名称", "nchar(20)"));
	columns.push_back(Column("作者", "nchar(20)"));
	columns.push_back(Column("余量", "int"));
	columns.push_back(Column("总量", "int"));
	columns.push_back(Column("入库日期", "datetime"));
	columns.push_back(Column("出版社", "nchar(20)"));
	if (CreateTable(tablename, columns)) {
		return true;
	}
	return false;
}

bool ShowTables()
{
	ExecuteSQL("select name from sys.tables;");
	return true;
}

bool Insert()
{
	return false;
}

bool Delete()
{
	return false;
}

bool Update()
{
	return false;
}

void DrawResourceImage(CDC* pDC, int imageResourceId, int x, int y)
{
	// 加载位图资源  
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(imageResourceId), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
	if (hBitmap == NULL) {
		AfxMessageBox(_T("Failed to load bitmap resource!"));
		return;
	}

	// 创建CBitmap对象来管理位图资源  
	CBitmap bitmap;
	bitmap.Attach(hBitmap);

	// 获取图像的大小  
	BITMAP bm;
	bitmap.GetBitmap(&bm);
	int imageWidth = bm.bmWidth;
	int imageHeight = bm.bmHeight;

	// 确保图像在视图的边界内  
	if (x + imageWidth > pDC->GetDeviceCaps(HORZRES)) {
		x = pDC->GetDeviceCaps(HORZRES) - imageWidth;
	}
	if (y + imageHeight > pDC->GetDeviceCaps(VERTRES)) {
		y = pDC->GetDeviceCaps(VERTRES) - imageHeight;
	}

	// 创建一个与位图兼容的内存DC  
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	// 将位图绘制到设备上下文上  
	//pDC->BitBlt(x, y, imageWidth, imageHeight, &memDC, 0, 0, SRCCOPY);
	pDC->StretchBlt(x, y, x + imageWidth, y + imageHeight, &memDC, 0, 0, imageWidth, imageHeight, SRCCOPY);

	// 恢复内存DC的原始位图  
	memDC.SelectObject(pOldBitmap);
}
void DrawResourceImage(CDC* pDC, int imageResourceId, int x, int y, int width, int height)
{
	// 加载位图资源  
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(imageResourceId), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
	if (hBitmap == NULL) {
		AfxMessageBox(_T("Failed to load bitmap resource!"));
		return;
	}

	// 创建CBitmap对象来管理位图资源  
	CBitmap bitmap;
	bitmap.Attach(hBitmap);

	// 获取图像的大小  
	BITMAP bm;
	bitmap.GetBitmap(&bm);
	int imageWidth = bm.bmWidth;
	int imageHeight = bm.bmHeight;

	// 确保图像在视图的边界内  
	if (x + imageWidth > pDC->GetDeviceCaps(HORZRES)) {
		x = pDC->GetDeviceCaps(HORZRES) - imageWidth;
	}
	if (y + imageHeight > pDC->GetDeviceCaps(VERTRES)) {
		y = pDC->GetDeviceCaps(VERTRES) - imageHeight;
	}

	// 创建一个与位图兼容的内存DC  
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	// 将位图绘制到设备上下文上  
	//pDC->BitBlt(x, y, imageWidth, imageHeight, &memDC, 0, 0, SRCCOPY);
	pDC->StretchBlt(x, y, width, height, &memDC, 0, 0, imageWidth, imageHeight, SRCCOPY);

	// 恢复内存DC的原始位图  
	memDC.SelectObject(pOldBitmap);
}

std::vector<CString> ReadTxt(CString filepath)
{
	//返回对象
	std::vector<CString> txt;
	CStdioFile FileRead;
	if (!(FileRead.Open(filepath, CFile::modeRead | CFile::typeText)))
	{
		MessageBox(NULL, _T("请选择有效文件"), _T("错误"), 0);
		return txt;
	}
	//一行数据
	CString cstrValue;
	while (FileRead.ReadString(cstrValue))
	{
		txt.push_back(cstrValue);
	}
	FileRead.Close();
	return txt;
}

CString Str2Cstr(std::string str)
{
	return CString(str.c_str());
}

Column::Column(std::string columnname, std::string datatype)
{
	this->columnname = columnname;
	this->datatype = datatype;
}
