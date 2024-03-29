#pragma once
#include "Tools.h"

void connect()//数据库连接函数
{
    SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//申请环境
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//设置环境
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//申请数据库连接
    ret = SQLConnect(hdbc, (SQLTCHAR*)("SQL SERVER"), SQL_NTS, (SQLTCHAR*)("sa"), SQL_NTS, (SQLTCHAR*)("72580."), SQL_NTS);
    if ((ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO))
    {
        std::cout << "数据库连接成功!" << std::endl;
    }
    else
    {
        std::cout << "数据库连接失败！" << std::endl;
    }
}