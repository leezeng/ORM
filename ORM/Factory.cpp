#include "Factory.h"
map<const string,FactoryFunction>* CFactory::m_pMapFunction=nullptr;
CFactory::CFactory(void)
{ 
}


CFactory::~CFactory(void)
{
}

bool CFactory::Register(const char* pChClassName, FactoryFunction pFun)
{	
	 string strClassName(pChClassName);
	 map<const string,FactoryFunction>::iterator iter=m_pMapFunction->find(strClassName);
	 if (iter==m_pMapFunction->end())
	 {
		(*m_pMapFunction)[strClassName]=pFun;
		return true;
	 }
	 return false;
}

void CFactory::ReleaseFactory()
{
	m_pMapFunction->clear();
	delete m_pMapFunction;
	m_pMapFunction=nullptr;
}

bool CFactory::InitializeFactory()
{
	if (nullptr==m_pMapFunction)
	{
		m_pMapFunction=new map<const string,FactoryFunction>();
	}
	return true;
}

CFactory* CFactory::CreateInstance(const char* pChClassName)
{
	string strClassName(pChClassName);
	map<const string ,FactoryFunction>::iterator iter=m_pMapFunction->find(strClassName);
	if (iter!=m_pMapFunction->end())
	{
		return	(iter->second)();
	}
	return nullptr;
}
