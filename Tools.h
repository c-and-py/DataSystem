#pragma once
#include "pch.h"
#include <iostream>
#include <sql.h> 
#include <sqlext.h> 
#include<sqltypes.h>

SQLRETURN ret = NULL;//返回信息
SQLHENV henv = NULL;//环境句柄
SQLHDBC hdbc = NULL;//连接句柄
SQLHSTMT hstmt = NULL;//语句句柄

void connect();