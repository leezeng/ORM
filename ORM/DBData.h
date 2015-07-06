#pragma once
#include "common.h"
#include <list>
class CDatabaseOperation;
class IOperation;
//#include "DatabaseOperation.h"
using std::list;
class CDBData :public CCommon
{
public:
	DECALRE_FACTORY_CLASS(CDBData)
	CDBData(void);
	virtual ~CDBData(void);
	enum EFieldType{
		EINT,
		EFLAOT,
		ESTRING,
		EBOOL,
		EDATETIME
	};
	enum EOperatType
	{
		E_SELECT,
		E_INSERT,
		E_DELETE,
		E_UPDATE,
		E_INVALID
	};
	struct SFieldInfo
	{
		string m_strTableName;
		string m_strFieldName;
		void*  m_pFiledAddress;
		EFieldType m_eType;
		bool m_bIsPrimaryKey;
		SFieldInfo(const string& strTableName,const string& strFieldName,void* pFiledAddress,EFieldType eType,bool bIsPrimaryKey);
	};
	typedef list<SFieldInfo*>::const_iterator FieldInfoIterator;

	void SetOperatType(EOperatType eType);
	inline EOperatType GetOperatType();
	void GetSQL(list<string>& lstSQL);
	void* GetFieldValueAddress(const string& fieldName);
	virtual bool Save(IOperation* pDBOperation);
	virtual void Reflect();
	virtual void UnReflect();
protected:
	void ReflectFiledToDB(const string& strTableName,const string& strFieldName,void* pFiledAddress,EFieldType eType,bool bIsPrimaryKey);
	void GetBuildSQLParam(map<const string,string>& condition,map<const string,string>& values);
	string FieldValueToString(const FieldInfoIterator& fieldInfo);
private:
	
	list<SFieldInfo*> m_lstFiled;
	EOperatType m_OperatType;
};

