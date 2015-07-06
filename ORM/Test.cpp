
#include "Test.h"

IMPLEMNT_FACTORY_CLASS(CTest)
CTest::CTest(void)
{
	m_nId=452432;
	m_strItem="111";
	m_fValue=111.111f;
}


CTest::~CTest(void)
{
}

void CTest::Reflect()
{
	ReflectFiledToDB("test","id",&m_nId,EINT,true);
	ReflectFiledToDB("test","item",&m_strItem,ESTRING,false);
	ReflectFiledToDB("test","value",&m_fValue,EFLAOT,false);
}

bool CTest::Save(IOperation* pIOperation)
{
	CDBData::SetOperatType(E_UPDATE);
	CDatabaseOperation* pDBOperation=(CDatabaseOperation*)pIOperation;
	if (pDBOperation!=nullptr)
	{
		list<string> lstSQL;
		GetSQL(lstSQL);
		for (list<string>::iterator iter=lstSQL.begin();iter!=lstSQL.end();iter++ )
		{
			pDBOperation->CompileStatement(*iter);
			int nRow=0;
			pDBOperation->ExcuteDML(nRow);
		}
	}
	return true;
}


