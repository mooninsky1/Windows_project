#include "Fcntl_test.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
void CFcntl::Test()
{
//	Fcntl1();
//	Fcntl2();
	FcntlToSocket();
}

void CFcntl::Fcntl1()
{
	const char *test_file = "test_lock.txt";
	int file_desc = -1;
	int byte_count = 0;
	const char *byte_to_write = "A";
	struct flock region_1;
	struct flock region_2;
	int res = 0;

	//��һ���ļ�������	
	file_desc = open(test_file, O_RDWR|O_CREAT, 0666);
	if(!file_desc)
	{
		fprintf(stderr, "Unable to open %s for read/write\n", test_file);
		exit(EXIT_FAILURE);
	}
	//���ļ����100����A���ַ�������
	for(byte_count = 0; byte_count < 100; ++byte_count)
	{
		write(file_desc, byte_to_write, 1);
	}
	//���ļ��ĵ�10��29�ֽ����ö�������������
	region_1.l_type = F_RDLCK;
	region_1.l_whence = SEEK_SET;
	region_1.l_start = 10;
	region_1.l_len = 20;
	//���ļ���40��49�ֽ�����д������ռ����
	region_2.l_type = F_WRLCK;
	region_2.l_whence = SEEK_SET;
	region_2.l_start = 40;
	region_2.l_len = 10;

	printf("Process %d locking file\n", getpid());
	//�����ļ�
	res = fcntl(file_desc, F_SETLK, &region_1);
	if(res == -1)
	{
		fprintf(stderr, "Failed to lock region 1\n");
	}
	res = fcntl(file_desc, F_SETLK, &region_1);
	if(res == -1)
	{
		fprintf(stderr, "Failed to lock region 2\n");
	}
	//�ó������߶����ӣ����ڲ���
	sleep(120);
	printf("Process %d closing file\n", getpid());
	close(file_desc);
	exit(EXIT_SUCCESS);
}


void CFcntl::Fcntl2()
{
	const char *test_file = "test_lock.txt";
	int file_desc = -1;
	int res = 0;
	//�������ļ�
	file_desc = open(test_file, O_RDWR|O_CREAT, 0666);
	if(!file_desc)
	{
		fprintf(stderr, "Unable to open %s for read/write\n", test_file);
		exit(EXIT_FAILURE);
	}
	//��������1��������
	struct flock region_test1;
	region_test1.l_type = F_RDLCK;
	region_test1.l_whence = SEEK_SET;
	region_test1.l_start = 10;
	region_test1.l_len = 20;
	region_test1.l_pid = -1;
	//��������2��������
	struct flock region_test2;
	region_test2.l_type = F_RDLCK;
	region_test2.l_whence = SEEK_SET;
	region_test2.l_start = 40;
	region_test2.l_len = 10;
	region_test2.l_pid = -1;
	//������1���Ƿ���Լ�һ���������в���
	res = fcntl(file_desc, F_GETLK, &region_test1);
	if(res == -1)
	{
		fprintf(stderr, "Failed to get RDLCK\n");
	}
	if(region_test1.l_pid == -1)
	{
		//���Լ�һ������
		printf("test: Possess %d could lock\n", getpid());
	}
	else
	{
		//�������һ������
		printf("test:Prossess %d  get lock failure\n", getpid());
	}

	//������2�Ƿ���Լ�һ���������в���
	res = fcntl(file_desc, F_GETLK, &region_test2);
	if(res == -1)
	{
		fprintf(stderr, "Failed to get RDLCK\n");
	}
	if(region_test2.l_pid == -1)
	{
		//���Լ�һ������
		printf("test: Possess %d could lock\n", getpid());
	}
	else
	{
		//�������һ������
		printf("test:Prossess %d  get lock failure\n", getpid());
	}
	exit(EXIT_SUCCESS);
}

//����socketģʽ
void CFcntl::FcntlToSocket()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	int nFlag = fcntl(fd,F_GETFL,0);
	printf("fd flag is:%d before set\n",nFlag);
	nFlag = fcntl(fd,F_SETFL,nFlag|O_NONBLOCK);
	printf("ret is:%d\n",nFlag);
	nFlag = fcntl(fd,F_GETFL,0);
	printf("fd flag is:%d after set\n",nFlag);
	
}