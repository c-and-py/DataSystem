#pragma once
#include "pch.h"
#include <iostream>
#include <sql.h> 
#include <sqlext.h> 
#include<sqltypes.h>
#include <string>

//SQLRETURN returnmsg = NULL;//������Ϣ
//SQLHENV handleenv = NULL;//�������
//SQLHDBC handledbc = NULL;//���Ӿ��
//SQLHSTMT handlestmt = NULL;//�����

bool ConnectSQL(std::string datasource,std::string username,std::string password);