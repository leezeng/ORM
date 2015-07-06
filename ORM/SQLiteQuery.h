#pragma once 
#include "sqlite3.h"
#include "Query.h"
class CSQLiteQuery:public IQuery
{
 
public:
	CSQLiteQuery();
	CSQLiteQuery(sqlite3* pDB,sqlite3_stmt* pVM,bool bEof);
	virtual ~CSQLiteQuery();
	virtual int numFields();

	virtual int fieldIndex(const char* szField);

	virtual const char* fieldName(int nCol);

	virtual const char* fieldDeclType(int nCol);

	virtual int fieldDataType(int nCol);

	virtual const char* fieldValue(int nField);

	virtual const char* fieldValue(const char* szField);

	virtual int getIntField(int nField, int nNullValue=0);

	virtual int getIntField(const char* szField, int nNullValue=0);

	virtual double getFloatField(int nField, double fNullValue=0.0);

	virtual double getFloatField(const char* szField, double fNullValue=0.0);

	virtual const char* getStringField(int nField, const char* szNullValue="");

	virtual const char* getStringField(const char* szField, const char* szNullValue="");

	virtual const unsigned char* getBlobField(int nField, int& nLen);

	virtual const unsigned char* getBlobField(const char* szField, int& nLen);

	virtual bool fieldIsNull(int nField);

	virtual bool fieldIsNull(const char* szField);

	virtual bool eof();

	virtual void nextRow();

	virtual void finalize();
private:
	sqlite3* m_pDB;
	sqlite3_stmt* m_pVM;
	bool m_eof;
};