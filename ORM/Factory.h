#pragma once
#include <string>
#include <map>
using std::map;
using std::string;
class CFactory;
typedef CFactory *(*FactoryFunction)();
#define IMPLEMNT_FACTORY_CLASS(CLASS) static const bool NoUse##CLASS=CFactory::Register(#CLASS, (CFactory*(*)())&CLASS::CreateInstance);
#define DECALRE_FACTORY_CLASS(CLASS) static CLASS* CreateInstance(){return new CLASS();}

class CFactory
{
public:
	CFactory(void);
	virtual ~CFactory(void);
	static bool Register(const char* pChClassName, FactoryFunction pFun);
	static void ReleaseFactory();
	static bool InitializeFactory();
	static CFactory* CreateInstance(const char* pChClassName);
private:
	static map<const string,FactoryFunction>* m_pMapFunction;
};
//������֣�����������ã�CFactory�ľ�̬������CFactory�ľ�̬��Աû�б���ʼ���������
//Ҳ���԰��ոð취�������ྲ̬��Ա�ĳ�ʼ��˳��
const static bool bNoUse=CFactory::InitializeFactory();
