#pragma once
#include "Tools.h"

void connect()//���ݿ����Ӻ���
{
    SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//���뻷��
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//���û���
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//�������ݿ�����
    ret = SQLConnect(hdbc, (SQLTCHAR*)("SQL SERVER"), SQL_NTS, (SQLTCHAR*)("sa"), SQL_NTS, (SQLTCHAR*)("72580."), SQL_NTS);
    if ((ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO))
    {
        std::cout << "���ݿ����ӳɹ�!" << std::endl;
    }
    else
    {
        std::cout << "���ݿ�����ʧ�ܣ�" << std::endl;
    }
}