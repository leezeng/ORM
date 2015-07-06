#pragma once
#include "sqlite3.h" 
#include "SQLITEQuery.h"
class CSQLiteStatement 
{
public:
	CSQLiteStatement();
	CSQLiteStatement(sqlite3* pDB,sqlite3_stmt* pVM);
	virtual ~CSQLiteStatement();
 
	

	virtual int execDML();

	virtual IQuery* execQuery();

	virtual void bind(int nParam, const char* chValue);

	virtual void bind(int nParam, const int nValue);

	virtual void bind(int nParam, const double dwValue);

	virtual void bind(int nParam, const unsigned char* blobValue, int nLen);

	virtual void bindNull(int nParam);

	virtual void reset();

	virtual void finalize();
private:
	sqlite3_stmt* m_pVM;
	sqlite3*	m_pDB;
};