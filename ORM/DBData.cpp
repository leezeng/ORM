#include "DBData.h"
#include <sstream>
using std::stringstream;
#include <algorithm>
using std::for_each;
#include <utility>
using std::pair;
IMPLEMNT_FACTORY_CLASS(CDBData)
CDBData::CDBData(void):m_OperatType(E_INVALID)
{
}
CDBData::~CDBData(void)
{
}
CDBData::SFieldInfo::SFieldInfo(const string& strTableName,const string& strFieldName,void* pFiledAddress,EFieldType eType,bool bIsPrimaryKey):\
	m_strTableName(strTableName),\
	m_strFieldName(strFieldName),\
	m_pFiledAddress(pFiledAddress),\
	m_eType(eType),\
	m_bIsPrimaryKey(bIsPrimaryKey)
{
}

void CDBData::ReflectFiledToDB(const string& strTableName,const string& strFieldName,void* pFiledAddress,EFieldType eType,bool bIsPrimaryKey)
{
	m_lstFiled.push_back(new SFieldInfo(strTableName,strFieldName,pFiledAddress,eType,bIsPrimaryKey));
}

void CDBData::Reflect()
{

}

void CDBData::UnReflect()
{

}

void CDBData::SetOperatType(EOperatType eType)
{
	m_OperatType=eType;
}

CDBData::EOperatType CDBData::GetOperatType()
{
	return m_OperatType;
}

void CDBData::GetSQL(list<string>& lstSQL)
{
	map<const string,string> conditions;
	map<const string,string> values;
	switch(m_OperatType)
	{
	case E_SELECT:
		{

		}
		break;
	case E_INSERT:
		{

		}
		break;
	case E_DELETE:
		{

		}
		break;
	case E_UPDATE:
		{
			GetBuildSQLParam(conditions,values);
			for_each(conditions.begin(),conditions.end(),[&values,&lstSQL](const pair<const string, string>& condition){
			 	string strSQL="update "+condition.first+" set "+values[condition.first]+" where "+condition.second;
				lstSQL.push_back(strSQL);
			});
		}
		break;
	case E_INVALID:
	default:
		break;
	}
}
void CDBData::GetBuildSQLParam(map<const string,string>& conditions,map<const string,string>& values)
{
	list<string> lstTableName;
	
	FieldInfoIterator fieldInfoIterator=m_lstFiled.begin();
	while(fieldInfoIterator!=m_lstFiled.end())
	{
		if ((*fieldInfoIterator)->m_bIsPrimaryKey)
		{	 
			lstTableName.push_back((*fieldInfoIterator)->m_strTableName);
		}
		++fieldInfoIterator;
	}
	lstTableName.unique();

	fieldInfoIterator=m_lstFiled.begin();
	for (list<string>::const_iterator iter=lstTableName.begin();iter!=lstTableName.end();iter++)
	{
		string value;
		string condition;
		bool bValueFlag=false;
		bool bConditionFlag=false;
		while(fieldInfoIterator!=m_lstFiled.end())
		{	
			if ((*iter)==(*fieldInfoIterator)->m_strTableName)
			{
				if(((*fieldInfoIterator)->m_bIsPrimaryKey))
				{
					string str=((*fieldInfoIterator)->m_strTableName)+"."+(*fieldInfoIterator)->m_strFieldName+\
						"="+FieldValueToString(fieldInfoIterator);
					bConditionFlag?condition+="and"+str:condition+=str,bConditionFlag=true;
				}
				else
				{
					string str=(*fieldInfoIterator)->m_strFieldName+"="+FieldValueToString(fieldInfoIterator);
					bValueFlag?value+=","+str:value+=str,bValueFlag=true;
				}
			}
			++fieldInfoIterator;
		}
		values[*iter]=value;
		conditions[*iter]=condition;
	}
}
 

string CDBData::FieldValueToString(const FieldInfoIterator& fieldInfo)
{
	string strValue;
	stringstream ss;
	switch((*fieldInfo)->m_eType)
	{
	case EINT:
		{
			int nValue=*(int*)((*fieldInfo)->m_pFiledAddress);
			ss<<nValue;
			strValue=ss.str();
		}
		break;
	case EFLAOT:
		{
			float fValue=*(float*)((*fieldInfo)->m_pFiledAddress);
			ss<<fValue;
			strValue=ss.str();
		}
		break;
	case ESTRING:
		{
			strValue=*(string*)((*fieldInfo)->m_pFiledAddress);
		}
		break;
	case EBOOL:
		break;
	case EDATETIME:
		break;
	default:
		break;
	}
	return strValue;
}
bool CDBData::Save(IOperation* pIOperation)
{
	
	return false;
}

void* CDBData::GetFieldValueAddress(const string& fieldName)
{
	for (FieldInfoIterator iter=m_lstFiled.begin();iter!=m_lstFiled.end();iter++)
	{
		if ((*iter)->m_strFieldName==fieldName)
		{
			return (*iter)->m_pFiledAddress;
		}
	}
	return nullptr;
}
