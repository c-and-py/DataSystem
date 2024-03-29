#pragma once
#include"pch.h"
#include <sql.h> 
#include <sqlext.h> 
#include <sqltypes.h>
#include "Tools.h"
bool ConnectSQL(std::string datasource, std::string username, std::string password) {
    SQLHENV henv; // 环境句柄
    SQLHDBC hdbc; // 数据库连接句柄
    SQLRETURN ret; // 返回值

    // 申请环境句柄
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cout << "无法申请环境句柄" << std::endl;
        return false;
    }

    // 设置环境属性
    ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cout << "无法设置环境属性" << std::endl;
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
        return false;
    }

    // 申请数据库连接句柄
    ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cout << "无法申请数据库连接句柄" << std::endl;
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
        return false;
    }

    // 连接数据库,数据源名称，用户标识，密码，
    // 注意不要使用unicode字符集，否则连接不上，字符集改成未设置即可
    ret = SQLConnect(hdbc, (SQLTCHAR*)(datasource.c_str()), SQL_NTS, (SQLTCHAR*)(username.c_str()), SQL_NTS, (SQLTCHAR*)(password.c_str()), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "数据库连接成功!" << std::endl;
    }
    else {
        std::cout << "数据库连接失败！" << std::endl;
    }

    // 释放句柄
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        return true;
    }
    else {
        return false;
    }
}