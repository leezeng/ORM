#include "DatabaseOperation.h"
#include "Test.h"
int main(int argc, char* argv[])
{
	CDatabaseOperation operation;
	operation.Open(".\\test.db");
	CTest test;
	test.Reflect();
	test.Save(&operation);
	list<CDBData*> lstTest;
	operation.ExcuteSQLQuery(lstTest,"test"); 
	return 0;
}
