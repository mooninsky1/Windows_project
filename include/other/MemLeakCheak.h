//lihf 2012/11/22 �ڴ�й©���
#include <crtdbg.h>

void Test()
{
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(156);
	int *a = new int[10];

}