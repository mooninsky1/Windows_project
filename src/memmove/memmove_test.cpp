#include "memmove_test.h"
#include <stdio.h>
#include <string.h>

void CMemMoveTest::Test()
{
	if(1)
	{
		char sz[]= "hello world";
		memmove(sz,sz+4,3);
		printf("%s\n",sz); //��֤�ǲ��� " wo      rld"  ʵ�ʴ�ӡ: "o wlo world"
		//����memmove�ǲ������dst �� src��ε�ַ,Ҳ���ǲ�������Ļ���0�ڽ�src����3���ֽڣ�����һ�㿽����ʼ����src
	}
	
}

