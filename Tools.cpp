//#pragma once
#include"pch.h"
#include "Tools.h"

static SQLRETURN returnmsg = NULL;//返回信息
static SQLHENV handleenv = NULL;//环境句柄
static SQLHDBC handledbc = NULL;//连接句柄
static SQLHSTMT handlestmt = NULL;//语句句柄

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
	if (handlestmt != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, handlestmt);
	}

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
		SQLCHAR SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
		SQLINTEGER NativeError;
		SQLSMALLINT MsgLen;
		SQLGetDiagRec(SQL_HANDLE_STMT, handlestmt, 1, SqlState, &NativeError, Msg, sizeof(Msg), &MsgLen);
		std::cout << reinterpret_cast<const char*>(Msg);
		throw(reinterpret_cast<const char*>(Msg));
		return false;
	}
}

bool CreateTable(std::string tablename, std::vector<Column> columns, int keynum)
{
	//拼装create语句
	std::string sql = "create table " + tablename + " (";
	for (int i = 0; i < columns.size(); i++) {
		sql += columns[i].columnname + " " + columns[i].datatype;
		if (i != columns.size() - 1) {
			sql += ", ";
		}
	}
	sql += ", PRIMARY KEY (";
	for (int i = 0; i < keynum; i++) {
		sql += columns[i].columnname;
		if (i != keynum - 1) {
			sql += ", ";
		}
	}
	sql += "));";
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
//Books
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
//Readers
bool CreateReaderTable(std::string tablename)
{
	std::vector<Column> columns;
	columns.push_back(Column("读者证号", "int"));
	columns.push_back(Column("姓名", "nchar(20)"));
	columns.push_back(Column("电话", "int"));
	if (CreateTable(tablename, columns)) {
		return true;
	}
	return false;
}
//Borrows
bool CreateBorrowTable(std::string tablename)
{
	std::vector<Column> columns;
	columns.push_back(Column("读者证号", "int"));
	columns.push_back(Column("借书ISBN", "nchar(20)"));
	columns.push_back(Column("借书日期", "datetime"));
	columns.push_back(Column("借书时长", "int"));
	if (CreateTable(tablename, columns,2)) {
		return true;
	}
	return false;
}

bool ForeignKeyISBN()
{
	if (ExecuteSQL("alter table Borrows add constraint ISBNrefer foreign key(借书ISBN) references Books(ISBN);")) {
		return true;
	}
	return false;
}

bool ForeignKeyReaderid()
{
	if (ExecuteSQL("alter table Borrows add constraint readerid foreign key(读者证号) references Readers(读者证号);")) {
		return true;
	}
	return false;
}

bool CreateBorrowTrigger()
{
	std::string sql = R"(create trigger addborrow on Borrows instead of insert as 
		begin
			declare @@readerid int
			declare @@isbn nchar(20)
			declare @@borrowtime datetime
			declare @@duration int
			declare @@num int
			select @@readerid=读者证号,@@isbn=借书ISBN,@@borrowtime=借书日期,@@duration=借书时长 from inserted;
			select @@num=余量 from Books where ISBN=@@isbn;
			if @@num>0
				begin
					insert into Borrows values (@@readerid,@@isbn,@@borrowtime,@@duration);
					update Books set 余量=@@num-1 where ISBN=@@isbn;
				end
		end)";

	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool CreateReturnTrigger()
{
	std::string sql = R"(create trigger ondeleteborrow on Borrows instead of delete as
				begin
					declare @@readerid int;
					declare @@isbn nchar(20)
					select @@readerid=读者证号,@@isbn=借书ISBN from deleted;
					update Books set 余量=余量+1 where ISBN=@@isbn;
					delete from Borrows where 读者证号=@@readerid and 借书ISBN=@@isbn
				end;)";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool CreateUpdateTrigger()
{
	std::string sql = R"(CREATE TRIGGER onupdateborrow ON Borrows
		INSTEAD OF UPDATE AS 
		BEGIN
			DECLARE @@isbn nchar(20)
			DECLARE @@oldisbn nchar(20)
			DECLARE @@readerID int
			DECLARE @@borrowtime datetime
			DECLARE @@borrowDuration int
			SELECT @@isbn=借书ISBN, @@readerID=读者证号, @@borrowDuration=借书时长,@@borrowtime=借书日期 FROM inserted;
			SELECT @@oldisbn=借书ISBN FROM deleted;
			IF @@isbn != @@oldisbn
			BEGIN
				UPDATE Books
				SET 余量 = 余量 - 1
				WHERE ISBN = @@isbn;

				UPDATE Books
				SET 余量 = 余量 + 1
				WHERE ISBN = @@oldisbn;
			END
			UPDATE Borrows SET 借书ISBN=@@isbn,借书日期=@@borrowtime,借书时长=@@borrowDuration WHERE 读者证号=@@readerID
		END)";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool CreateBorrowView()
{
	std::string sql = "create view borrowview as select 姓名,名称,借书日期,借书日期+借书时长 as 还书日期,电话 from Books,Readers,Borrows where Books.ISBN=Borrows.借书ISBN and Readers.读者证号=Borrows.读者证号;";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool CreateReaderTable()
{
	std::string sql = "create view ReaderView  as(select 读者证号, 姓名, Books.名称, 借书日期, 借书日期 + 借书时长 as 还书日期, 借书时长 from Readers, Books where Readers.借书ISBN = Books.ISBN); ";
	if(ExecuteSQL(sql)){
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

bool InsertBook(std::string ISBN, std::string name, std::string author, int remainnum, int num, std::string intime, std::string press)
{
	std::string sql;
	sql = "insert into Books values ('" + ISBN + "', '" + name + "', '" + author + "', " + std::to_string(remainnum) + ", " + std::to_string(num) + ", '" + intime + "', '" + press + "');";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool DeleteBook(std::string ISBN) {
	std::string sql;
	sql = "delete from Books where ISBN='" + ISBN + "';";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool UpdateBook(std::string ISBN, std::string name, std::string author, int remainnum, int num, std::string intime, std::string press)
{
	std::string sql;
	sql = "update  Books set 名称='" + name + "',作者='" + author + "',余量=" + std::to_string(remainnum) + ",总量="+ std::to_string(num) +
		",入库日期='"+ intime +"',出版社='"+ press +"' where ISBN='" + ISBN + "';";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool InsertReader(int readerID, std::string name, int phone)
{
	std::string sql;
	sql = "insert into Readers values (" + std::to_string(readerID) + ", N'" + name + "', " + std::to_string(phone) +  ");";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool DeleteReader(int readerID)
{
	std::string sql;
	sql = "delete from Readers where 读者证号=" + std::to_string(readerID) + ";";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool UpdateReader(int readerID, std::string name, int phone)
{
	std::string sql;
	sql = "update  Readers set 姓名='" + name + "',电话=" + std::to_string(phone) + " where 读者证号=" + std::to_string(readerID) + ";";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool InsertBorrow(int readerID, std::string ISBN, std::string borrowtime, int duration)
{
	// 获取当前时间
	std::time_t now = std::time(nullptr);
	std::tm tm;
	localtime_s(&tm, &now);
	std::stringstream ss;
	ss << std::put_time(&tm, "%Y.%m.%d");

	std::string sql;
	sql = "insert into Borrows values (" + std::to_string(readerID) + ", '" + ISBN + "', '" + ss.str() + "', " + std::to_string(duration) + ");";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool DeleteBorrow(int readerID,std::string isbn)
{
	std::string sql;
	sql = "delete from Borrows where 读者证号=" + std::to_string(readerID) + " and 借书ISBN="+isbn+";";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool UpdateBorrow(int readerID, std::string ISBN, int duration)
{
	// 获取当前时间
	std::time_t now = std::time(nullptr);
	std::tm tm;
	localtime_s(&tm, &now);
	std::stringstream ss;
	ss << std::put_time(&tm, "%Y.%m.%d");

	std::string sql;
	sql = "update Borrows set  借书日期='" + ss.str() + "', 借书时长=" + std::to_string(duration) + " where 读者证号=" + std::to_string(readerID) + " and 借书ISBN='" + ISBN + "';";
	if (ExecuteSQL(sql)) {
		return true;
	}
	return false;
}

bool DecreaseBookNum(std::string ISBN, int decreaseNum)
{
	std::string sql;
	sql = "update book set 余量 = 余量 - " + std::to_string(decreaseNum) + " where ISBN = '" + ISBN + "';";
	if (ExecuteSQL(sql)) {
		return true;
	}
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

bool GetResult(std::vector<SQLCHAR*> rets,const int& row)
{
	//SQLLEN cbData;
	//for (int i = 0; i < row; i++) {
	//	ret[i] = new SQLCHAR[30];
	//	SQLBindCol(handlestmt, i, SQL_C_CHAR, ret[i], 30, &cbData);
	//}
	//for (int i = 0; i < row; i++) {
	//	if (SQLFetch(handlestmt) == SQL_SUCCESS) {
	//		std::cout << ret[i];
	//	}
	//}
	SQLLEN cb;
	SQLCHAR* d = new SQLCHAR[30];
	SQLBindCol(handlestmt, 4, SQL_C_CHAR, d, 30, &cb);
	if (SQLFetch(handlestmt) == SQL_SUCCESS) {
		int a = 0;
	}

	SQLCHAR** datas = new SQLCHAR*[30];
	for (int i = 0; i < row; i++) {
		datas[i] = new SQLCHAR[30];
	}
	SQLLEN cbData;
	for (int i = 0; i < row; i++) {
		SQLBindCol(handlestmt, i + 1, SQL_C_CHAR, datas[i], 30, &cbData);
	}
	if (SQLFetch(handlestmt) == SQL_SUCCESS) {
		for (int i = 0; i < row; i++) {
			rets.push_back(datas[i]);
		}
	}
	else {
		return false;
	}
	return true;
}

bool FetchData(std::vector<std::string>& rets, const int& col) {
	rets.clear();
	SQLCHAR** datas = new SQLCHAR * [col];
	SQLLEN cbData;
	for (int i = 0; i < col; i++) {
		datas[i] = new SQLCHAR[30];
		SQLBindCol(handlestmt, i + 1, SQL_C_CHAR, datas[i], 30, &cbData);
	}

	//SQLFetchScroll(handlestmt, SQL_FETCH_FIRST, 0);
	// Fetch data
	if (SQLFetch(handlestmt) == SQL_SUCCESS) {
		for (int i = 0; i < col; i++) {
			rets.push_back(reinterpret_cast<const char*>(datas[i]));
		}
	}
	else {
		// Release memory in case of failure
		for (int i = 0; i < col; i++) {
			delete[] datas[i];
		}
		delete[] datas;
		return false;
	}

	// Release memory
	for (int i = 0; i < col; i++) {
		delete[] datas[i];
	}
	delete[] datas;
	return true;
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
