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
//避免出现，在其他类调用，CFactory的静态函数，CFactory的静态成员没有被初始化的情况。
//也可以按照该办法，控制类静态成员的初始化顺序。
const static bool bNoUse=CFactory::InitializeFactory();
