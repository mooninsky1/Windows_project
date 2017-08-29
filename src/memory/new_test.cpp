#include "new_test.h"
#include "stdio.h"
#include <string.h>

void CNewTest::Test()
{
	while (true)
	{
		CNewTest* p = (CNewTest*)new char[sizeof(CNewTest)+1024];
		memset(p,1,sizeof(CNewTest)+1024);
		int a=sizeof(*p);
		delete p;
		p = 0;
	}
}