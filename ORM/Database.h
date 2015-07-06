#pragma once
#include "Query.h"
class IDatabase
{
public:
	IDatabase(void){};
	virtual ~IDatabase(void){}; 
	virtual bool Open(const char* conninfo) = 0;
	virtual void Close()=0;
	virtual int ExecScalar(const char* szSQL) = 0;
	virtual int ExecDML(int& nRow)=0;
	virtual int CommitBegin() = 0;
	virtual int CommitEnd() = 0;
	virtual int RollBack() = 0;
	virtual bool TableExists(const char* szTable) = 0;
	virtual void Bind(int nParam, const char* szValue) = 0;
	virtual void Bind(int nParam, const double dValue) = 0;
	virtual void Bind(int nParam, const unsigned char* blobValue, int nLen) = 0;
	virtual void BindNull(int nParam) = 0;
	virtual bool compileStatement(const char* szSQL) = 0;
	virtual void ResetStatement() = 0;
	virtual void FinalizeStatement() = 0;
	virtual void StatementSQL(const char* szSQL) = 0;
	virtual int ExecDML() = 0;
	virtual int ExecDML(const char* szSQL) = 0;
	virtual int LastRowId() = 0;
	virtual void setBusyTimeout(int nMillisecs) = 0;
	virtual IQuery* ExecQuery(const char* szSQL) = 0;
	virtual IQuery* ExecQuery() = 0;
}; 