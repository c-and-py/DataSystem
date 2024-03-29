#pragma once
#include "pch.h"
#include <iostream>
#include <sql.h> 
#include <sqlext.h> 
#include<sqltypes.h>
#include <string>

//SQLRETURN returnmsg = NULL;//返回信息
//SQLHENV handleenv = NULL;//环境句柄
//SQLHDBC handledbc = NULL;//连接句柄
//SQLHSTMT handlestmt = NULL;//语句句柄

bool ConnectSQL(std::string datasource,std::string username,std::string password);