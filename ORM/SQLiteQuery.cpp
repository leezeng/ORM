#include "SQLiteQuery.h"
#include <stdexcept>
int CSQLiteQuery::numFields()
{
	return sqlite3_column_count(m_pVM);
}

int CSQLiteQuery::fieldIndex(const char* szField)
{
	throw std::logic_error("The method or operation is not implemented.");
}

const char* CSQLiteQuery::fieldName(int nCol)
{
	return sqlite3_column_name(m_pVM,nCol);
}

const char* CSQLiteQuery::fieldDeclType(int nCol)
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteQuery::fieldDataType(int nCol)
{
	return sqlite3_column_type(m_pVM,nCol);
}

const char* CSQLiteQuery::fieldValue(int nField)
{
	throw std::logic_error("The method or operation is not implemented.");
}

const char* CSQLiteQuery::fieldValue(const char* szField)
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteQuery::getIntField(int nField, int nNullValue/*=0*/)
{
	return sqlite3_column_int(m_pVM,nField);
	//throw std::logic_error("The method or operation is not implemented.");
}

int CSQLiteQuery::getIntField(const char* szField, int nNullValue/*=0*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

double CSQLiteQuery::getFloatField(int nField, double fNullValue/*=0.0*/)
{
	return sqlite3_column_double(m_pVM,nField);
}

double CSQLiteQuery::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

const char* CSQLiteQuery::getStringField(int nField, const char* szNullValue/*=""*/)
{
	return (const char*)sqlite3_column_text(m_pVM,nField);
}

const char* CSQLiteQuery::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

const unsigned char* CSQLiteQuery::getBlobField(int nField, int& nLen)
{
	throw std::logic_error("The method or operation is not implemented.");
}

const unsigned char* CSQLiteQuery::getBlobField(const char* szField, int& nLen)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CSQLiteQuery::fieldIsNull(int nField)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CSQLiteQuery::fieldIsNull(const char* szField)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CSQLiteQuery::eof()
{
	return m_eof;
}

void CSQLiteQuery::nextRow() 
{
	int ret=sqlite3_step(m_pVM);
	if (ret==SQLITE_ROW)
	{
		m_eof=false;
	}
	else
	{
		m_eof=true;
	}
}

void CSQLiteQuery::finalize()
{
	sqlite3_finalize(m_pVM);
}

CSQLiteQuery::CSQLiteQuery():m_pDB(nullptr),m_pVM(nullptr),m_eof(false)
{
	 
}

CSQLiteQuery::CSQLiteQuery(sqlite3* pDB,sqlite3_stmt* pVM,bool bEof):m_pDB(pDB),m_pVM(pVM),m_eof(bEof)
{

}

CSQLiteQuery::~CSQLiteQuery()
{

}

