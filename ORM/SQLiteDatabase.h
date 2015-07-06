#pragma once
#include "sqlite3.h"
#include "Database.h"
#include "SQLiteStatement.h"
#include "SQLiteVFS.h"
void SivInstallSQLiteVFS();
class CSQLiteDatabase:public IDatabase
{
public:
	CSQLiteDatabase();
	virtual ~CSQLiteDatabase();
	virtual bool Open(const char* conninfo);

	virtual void Close();

	virtual int ExecScalar(const char* szSQL);

	virtual int CommitBegin();

	virtual int CommitEnd();

	virtual int RollBack();

	virtual bool TableExists(const char* szTable);

	virtual void Bind(int nParam, const char* szValue);

	virtual void Bind(int nParam, const double dValue);

	virtual void Bind(int nParam, const unsigned char* blobValue, int nLen);

	virtual void BindNull(int nParam);

	virtual bool compileStatement(const char* szSQL);
	
	virtual void ResetStatement();

	virtual void FinalizeStatement();

	virtual void StatementSQL(const char* szSQL);

	virtual int ExecDML();

	virtual int ExecDML(const char* szSQL);

	virtual int LastRowId();

	virtual void setBusyTimeout(int nMillisecs);
	 
	virtual int ExecDML(int& nRow);
	virtual IQuery* ExecQuery();
	virtual IQuery* ExecQuery(const char* szSQL);

private:
	sqlite3_stmt* compile(const char* szSQL);

private:
	sqlite3* m_pDB;
	CSQLiteStatement m_Statement;
};