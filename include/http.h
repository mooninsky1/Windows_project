#include "stdafx.h"

#include <iostream>

#include <string>
#include "http_request.h"
using namespace std;

void Test()
{
	Request myRequest;      //��ʼ����

	string sHeaderSend;     //����httpͷ

	string sHeaderReceive;  //����ͷ

	string sMessage="";     //����ҳ������

	bool IsPost=false;  //�Ƿ�Post�ύ


	int i =myRequest.SendRequest(IsPost, "http://neeao.com", sHeaderSend, sHeaderReceive, sMessage);

	if (i)

	{

		cout<<"Httpͷ:"<<endl;

		cout<< sHeaderSend <<endl;

		cout<<"��Ӧͷ"<<endl;

		cout<< sHeaderReceive <<endl;

		cout<<"��ҳ����"<<endl;

		cout<< sMessage <<endl;

	}
	else

	{

		cout<<"���粻�ɵ���"<<endl;

	}

	system("pause");
}