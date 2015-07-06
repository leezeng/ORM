#pragma once
#include "DBData.h"
#include "DatabaseOperation.h"
class CTest:public CDBData
{
public:
	DECALRE_FACTORY_CLASS(CTest)
	CTest(void);
	virtual ~CTest(void);
	virtual void Reflect(); 
	virtual bool Save(IOperation* pDBOperation);
	string m_strItem;
private:
	int	m_nId;
	
	float	   m_fValue;
};

