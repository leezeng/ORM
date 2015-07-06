#pragma once
class IQuery
{
public:
	IQuery(){};
	virtual ~IQuery(){};
	virtual int numFields() = 0;
	virtual int fieldIndex(const char* szField) = 0;
	virtual const char* fieldName(int nCol) = 0;
	virtual const char* fieldDeclType(int nCol) = 0;
	virtual int fieldDataType(int nCol) = 0;
	virtual const char* fieldValue(int nField) = 0;
	virtual const char* fieldValue(const char* szField) = 0;
	virtual int getIntField(int nField, int nNullValue=0) = 0;
	virtual int getIntField(const char* szField, int nNullValue=0) = 0;
	virtual double getFloatField(int nField, double fNullValue=0.0) = 0;
	virtual double getFloatField(const char* szField, double fNullValue=0.0) = 0;
	virtual const char* getStringField(int nField, const char* szNullValue="") = 0;
	virtual const char* getStringField(const char* szField, const char* szNullValue="") = 0;
	virtual const unsigned char* getBlobField(int nField, int& nLen) = 0;
	virtual const unsigned char* getBlobField(const char* szField, int& nLen) = 0;
	virtual bool fieldIsNull(int nField) = 0;
	virtual bool fieldIsNull(const char* szField) = 0;
	virtual bool eof() = 0;
	virtual void nextRow() = 0;
	virtual void finalize() = 0;
}; 