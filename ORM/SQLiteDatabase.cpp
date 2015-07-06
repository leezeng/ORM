#include "SQLiteDatabase.h"
#include <stdexcept>


bool CSQLiteDatabase::Open(const char* conninfo)
{
	int ret=sqlite3_open(conninfo,&m_pDB);
	if (ret!=SQLITE_OK)
	{
		throw std::logic_error("The method or operation is not implemented.");
	} 
	return true;
}

void CSQLiteDatabase::Close()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteDatabase::ExecScalar(const char* szSQL)
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteDatabase::CommitBegin()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteDatabase::CommitEnd()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteDatabase::RollBack()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CSQLiteDatabase::TableExists(const char* szTable)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteDatabase::Bind(int nParam, const char* szValue)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteDatabase::Bind(int nParam, const double dValue)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteDatabase::Bind(int nParam, const unsigned char* blobValue, int nLen)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteDatabase::BindNull(int nParam)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CSQLiteDatabase::compileStatement(const char* szSQL)
{ 
	sqlite3_stmt* pVM= compile(szSQL);
	m_Statement=CSQLiteStatement(m_pDB,pVM);
	return true;
}

sqlite3_stmt* CSQLiteDatabase::compile(const char* szSQL)
{
	const char* pzTail;
	sqlite3_stmt* pVM;
	int ret=sqlite3_prepare_v2(m_pDB,szSQL,-1,&pVM,&pzTail);
	if (ret!=SQLITE_OK)
	{
		const char* pCh=sqlite3_errmsg(m_pDB);
		throw std::logic_error(pCh);
	} 
	return pVM;
}

void CSQLiteDatabase::ResetStatement()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteDatabase::FinalizeStatement()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteDatabase::StatementSQL(const char* szSQL)
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteDatabase::ExecDML()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteDatabase::ExecDML(const char* szSQL)
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteDatabase::LastRowId()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteDatabase::setBusyTimeout(int nMillisecs)
{
	throw std::logic_error("The method or operation is not implemented.");
}

/************************************************************************/
/* 已经编译成Statement的SQL通过m_statement对象得到查询对象                                                                     */
/************************************************************************/
IQuery* CSQLiteDatabase::ExecQuery()
{
	IQuery* sqlQuery=m_Statement.execQuery();
	return sqlQuery;
}

IQuery* CSQLiteDatabase::ExecQuery(const char* szSQL)
{
	sqlite3_stmt* pVM=compile(szSQL);
	int ret=sqlite3_step(pVM);
	if (ret==SQLITE_DONE||ret==SQLITE_ROW)
	{
		return new CSQLiteQuery(m_pDB,pVM,false);
	}
	else if (ret==SQLITE_ERROR)
	{
	}
	else
	{

	}
	return nullptr;
}

 

CSQLiteDatabase::CSQLiteDatabase():m_pDB(nullptr)
{
	SivInstallSQLiteVFS();
}

CSQLiteDatabase::~CSQLiteDatabase()
{

}

int CSQLiteDatabase::ExecDML(int& nRow)
{
	 return m_Statement.execDML();
}

 