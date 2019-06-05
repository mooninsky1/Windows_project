#pragma  once
#include <iostream>
//lihanfeng 2019/05/17 结论：
/*
如果只实现了const 构造函数会调用const构造函数，如果实现了非const构造函数优化调用非const构造函数
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
			//lihanfeng 2019/05/17 验证拷贝构造函数是const引用，还是非const引用
			CTestStruct b(a);
			CTestStruct c(CTestStruct(11));
		}
		
		
	}
protected:
private:
	int *d;
};