#include "fork_test.h"
#include <stdio.h>
void CForkTest::Test()
{
	printf("hi fork test now !\n");
	//ForkTest();
	VforkTest();
}
void CForkTest::ForkTest()
{
	int i=0;
	pid_t pid=0;
	pid = fork();
	if(pid < 0)
	{
		printf("fork error\n");
		return;
	}
	else if(0 == pid)
	{//child
		i++;
		printf("I am child pid:%d i:%d\n",getpid(),i);
	}
	else 
	{
		i++;
		printf("I am parent pid:%d i:%d\n",getpid(),i);
	}
}
void CForkTest::VforkTest()
{
	int i=0;
	pid_t pid=0;
	pid = vfork();
	if(pid < 0)
	{
		printf("fork error\n");
		return;
	}
	else if(0 == pid)
	{//child
		i++;
		printf("I am child pid:%d i:%d\n",getpid(),i);
		_exit(0);//vfork ��֤�ӽ�����ִ�У����ӽ��̵���exit�˳��󸸽��̲ż���ִ��
	}
	else 
	{
		i++;
		printf("I am parent pid:%d i:%d\n",getpid(),i);
		//vfork �������ݶΣ���ӡi=2
	}
}


