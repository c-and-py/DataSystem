#pragma once
#include "pch.h"
#include <iostream>
#include <sql.h> 
#include <sqlext.h> 
#include<sqltypes.h>

SQLRETURN ret = NULL;//������Ϣ
SQLHENV henv = NULL;//�������
SQLHDBC hdbc = NULL;//���Ӿ��
SQLHSTMT hstmt = NULL;//�����

void connect();