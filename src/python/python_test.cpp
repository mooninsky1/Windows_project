#include "python_test.h"


void CPythonTest::Test()
{
	InitPython();
	C_Call_python();
	ClosePython();
}

int CPythonTest::InitPython()
{
	
    // ��ʼ��Python
    //��ʹ��Pythonϵͳǰ������ʹ��Py_Initialize����
    //���г�ʼ������������Python���ڽ�ģ�鲢���ϵͳ·
    //����ģ������·���С��������û�з���ֵ�����ϵͳ
    //�Ƿ��ʼ���ɹ���Ҫʹ��Py_IsInitialized��

    Py_Initialize();

    // ����ʼ���Ƿ�ɹ�
    if ( !Py_IsInitialized() )
    {
        return -1;
    }
}
void CPythonTest::ClosePython()
{
	// �ر�Python
    Py_Finalize();
}
	//
int CPythonTest::C_Call_python()
{
	// ��ӵ�ǰ·��
    //��������ַ�����ΪPython����ֱ�����У�����0
    //��ʾ�ɹ���-1��ʾ�д����ʱ���������Ϊ�ַ���
    //�����﷨����
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyObject *pName,*pModule,*pDict,*pFunc,*pArgs;

    // ������Ϊpytest�Ľű�
    pName = PyString_FromString("sky");
    pModule = PyImport_Import(pName);
    if ( !pModule )
    {
        printf("can't find sky.py");
        getchar();
        return -1;
    }
    pDict = PyModule_GetDict(pModule);
    if ( !pDict )
    {
        return -1;
    }

    // �ҳ�������Ϊadd�ĺ���
    pFunc = PyDict_GetItemString(pDict, "add");
    if ( !pFunc || !PyCallable_Check(pFunc) )
    {
        printf("can't find function [add]");
        getchar();
        return -1;
    }

    // ������ջ
    pArgs = PyTuple_New(2);

    //  PyObject* Py_BuildValue(char *format, ...)
    //  ��C++�ı���ת����һ��Python���󡣵���Ҫ��
    //  C++���ݱ�����Pythonʱ���ͻ�ʹ������������˺���
    //  �е�����C��printf������ʽ��ͬ�����õĸ�ʽ��
    //  s ��ʾ�ַ�����
    //  i ��ʾ���ͱ�����
    //  f ��ʾ��������
    //  O ��ʾһ��Python����

    PyTuple_SetItem(pArgs, 0, Py_BuildValue("l",3));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("l",4));

    // ����Python����
    PyObject_CallObject(pFunc, pArgs);

    //��������ǲ��Һ���foo ��ִ��foo
    pFunc = PyDict_GetItemString(pDict, "foo");
    if ( !pFunc || !PyCallable_Check(pFunc) )
    {
        printf("can't find function [foo]");
        getchar();
        return -1;
    }

    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("l",2)); //

    PyObject_CallObject(pFunc, pArgs);


    Py_DECREF(pName);
    Py_DECREF(pArgs);
    Py_DECREF(pModule);
}
int CPythonTest::Python_Call_C()
{
	//python call c++ ��Ҫ��c++����ɶ�̬��
	return 0;
}

