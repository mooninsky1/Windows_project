#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

class CFcntl
{
public:
	static void Test();

	//���ļ��������
	static void Fcntl1();
	static void Fcntl2();

	//����socketģʽ
	static void FcntlToSocket();
};
