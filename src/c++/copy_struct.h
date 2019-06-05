#pragma  once
#include <iostream>
//lihanfeng 2019/05/17 ���ۣ�
/*
���ֻʵ����const ���캯�������const���캯�������ʵ���˷�const���캯���Ż����÷�const���캯��
*/
class CTestStruct
{
public:
	CTestStruct():d(0){}
	CTestStruct(int val):d(new int(val)){}
	CTestStruct(CTestStruct & ref){
		std::cout<<"not const struct"<<std::endl;
	}
	CTestStruct(const CTestStruct& ref)
	{
		d= new int(*ref.d);
		std::cout<<"const struct"<<std::endl;
	}
	~CTestStruct()
	{
		delete d;
		d=0;
	}
public:
	static void Test()
	{
		{
			CTestStruct a(10);
			//lihanfeng 2019/05/17 ��֤�������캯����const���ã����Ƿ�const����
			CTestStruct b(a);
			CTestStruct c(CTestStruct(11));
		}
		
		
	}
protected:
private:
	int *d;
};