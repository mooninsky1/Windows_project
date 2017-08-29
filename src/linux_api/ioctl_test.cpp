#include "ioctl_test.h"
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/fcntl.h>

void CIoctl::Test()
{
	SetSocketNonblock();
}

	//����socet������
void CIoctl::SetSocketNonblock()
	{
		int fd = socket(AF_INET,SOCK_STREAM,0);
		int flag =0;//0: clear 1: set
		flag = fcntl(fd,F_GETFL,0);
		printf("flag is:%d before ioctl\n",flag);
		/*FIONBIO �� ����ioctl�ĵ���������ָ��һ��0 ���0 ֵ�ֱ���������ñ��׽ӿڵķ�������־��
		�������O_NONBLOCK �ļ�״̬��־��Ч�����ñ�־ͨ��fcntl ��F_SETFL ������������á�*/
		ioctl(fd,FIONBIO,flag);
		flag = fcntl(fd,F_GETFL,0);
		printf("flag is:%d after ioctl\n",flag);
	}

