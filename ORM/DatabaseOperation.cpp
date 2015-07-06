#include "DatabaseOperation.h"
#include "SQLiteDatabase.h"
bool CDatabaseOperation::Open(const char* chPath)
{
	 if (nullptr!=m_pDatabase)
	 {
		 delete m_pDatabase;
		 m_pDatabase=nullptr;
	 }
	 m_pDatabase=new CSQLiteDatabase();
	 return m_pDatabase->Open(chPath);
}

bool CDatabaseOperation::Select(CDBData*& pDBData)
{
	return false;
}

CDatabaseOperation::CDatabaseOperation():m_pDatabase(nullptr),m_pQuery(nullptr)
{

}

CDatabaseOperation::~CDatabaseOperation()
{

}

bool CDatabaseOperation::ExcuteSQLQuery(list<CDBData*>& lstDBData,const char* chTableName)
{
	if (nullptr!=m_pQuery)
	{
		m_pQuery->finalize();
		delete m_pQuery;
		m_pQuery=nullptr;
	}
#if 0  //不利用 Statement对象 直接通过 CSQLiteQuery的虚拟机指针 pVM
	m_pDatabase->compileStatement("select * from test");
	
	m_pQuery=m_pDatabase->ExecQuery();
#endif
	m_pQuery=m_pDatabase->ExecQuery("select * from test");
	while (!m_pQuery->eof())
	{
		CDBData* pDBData=(CDBData*)(CFactory::CreateInstance("CTest"));
		pDBData->Reflect();
		for (int i=0;i<m_pQuery->numFields();i++)
		{
			const char* chFieldName=m_pQuery->fieldName(i);
			
			void* pValueAddress=pDBData->GetFieldValueAddress(string(chFieldName));
			
			int nType=m_pQuery->fieldDataType(i);
			switch(nType)
			{
			case SQLITE_INTEGER:
				{
					
					*(int*)(pValueAddress)=m_pQuery->getIntField(i);
				}
				break;
			case SQLITE_FLOAT:
				{
					*(float*)(pValueAddress)=(float)m_pQuery->getFloatField(i);
				}
				break;
			case SQLITE_TEXT:
				{
					const char* pChValue=m_pQuery->getStringField(i,nullptr);
					*(string*)pValueAddress=string(pChValue);
				}
				break;
			default:
				break;
			}
		}
		pDBData->UnReflect();
		m_pQuery->nextRow();
		lstDBData.push_back(pDBData);
	}
	return false;
}

bool CDatabaseOperation::ExcuteSQLQueryByPrimayKey(CDBData*& pDBData)
{
	return false;
}

bool CDatabaseOperation::CompileStatement(const string& strSQL)
{
	m_pDatabase->compileStatement(strSQL.c_str());
	return false;
}

bool CDatabaseOperation::ExcuteDML(int& nRow)
{
	nRow=m_pDatabase->ExecDML(nRow);
	return true;
}

