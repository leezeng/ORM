#pragma once
#include "Operation.h"
#include "Database.h"
#include "Factory.h"
#include "DBData.h"
#include <string>
#include <list>

using std::string;
using std::list;
class CDatabaseOperation:public IOperation
{
public:
	CDatabaseOperation();
	virtual ~CDatabaseOperation();
	virtual bool Open(const char* chPath);
	bool Select(CDBData*& pDBData);
	bool ExcuteSQLQuery(list<CDBData*>& lstDBData,const char* chTableName);
	bool ExcuteSQLQueryByPrimayKey(CDBData*& pDBData);
	bool CompileStatement(const string& strSQL);
	bool ExcuteDML(int& nRow);
private:
	IDatabase* m_pDatabase;
	IQuery*	m_pQuery;
};