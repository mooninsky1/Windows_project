#include <sys/mman.h>
/*
1.mmap ʹ��MAP_SHARED���Ը�д���ļ� ��MAP_PRIVATE�޷�д���ļ�
*/
class Cmmap
{
public:
	static void Test();

	//���ļ��ڴ�ӳ�䣬ֱ�ӷ����ڴ棬�޸��ļ�
	static void mmap_other();
	static void mmap_my();
};
