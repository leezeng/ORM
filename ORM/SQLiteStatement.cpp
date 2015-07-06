#include "SQLiteStatement.h"
#include <stdexcept>
int CSQLiteStatement::execDML()
{
	const char* szError;
	int nRet = sqlite3_step(m_pVM);
	if (nRet == SQLITE_DONE)
	{
		int nRowsChanged = sqlite3_changes(m_pDB);
		nRet = sqlite3_reset(m_pVM);
		if (nRet != SQLITE_OK)
		{
			szError = sqlite3_errmsg(m_pDB);
			throw std::logic_error("The method or operation is not implemented.");
		}
		return nRowsChanged;
	}
	else
	{
		nRet = sqlite3_reset(m_pVM);
		szError = sqlite3_errmsg(m_pDB);
		throw std::logic_error("The method or operation is not implemented."); 
	}
}

IQuery* CSQLiteStatement::execQuery()
{
	int ret=sqlite3_step(m_pVM);
	if (ret==SQLITE_DONE)
	{
		return new CSQLiteQuery(m_pDB,m_pVM,true);
	}
	else if (ret==SQLITE_ROW)
	{
		return new CSQLiteQuery(m_pDB,m_pVM,false);
	}
	else if (ret==SQLITE_ERROR)
	{
	}
	else
	{

	}
	return nullptr;
}

void CSQLiteStatement::bind(int nParam, const char* chValue)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteStatement::bind(int nParam, const int nValue)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteStatement::bind(int nParam, const double dwValue)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteStatement::bind(int nParam, const unsigned char* blobValue, int nLen)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteStatement::bindNull(int nParam)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteStatement::reset()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CSQLiteStatement::finalize()
{
	throw std::logic_error("The method or operation is not implemented.");
}


CSQLiteStatement::CSQLiteStatement(sqlite3* pDB,sqlite3_stmt* pVM):m_pDB(pDB),m_pVM(pVM)
{

}

CSQLiteStatement::CSQLiteStatement()
{

}

CSQLiteStatement::~CSQLiteStatement()
{

} 
