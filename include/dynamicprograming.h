#include <iostream>
#include <stdlib.h>
//lihf 2012/11/20 �㷨����15��

//������ˮ��1��ʱ��
const int e1 = 2;
//������ˮ��2��ʱ��
const int e2 = 4;

//����װ��վ��ʱ��
const int s1[6] = {7,9,3,4,8,4};
const int s2[6] = {8,5,6,4,5,7};

//�л���ˮ��װ��վʱ��
const int t[2][5] = {2,3,1,3,4,
					 2,1,2,2,1};
//�˳���ˮ��ʱ��
const int x1 = 3;
const int x2 = 2;

//��⣺�����һ�������ˮ��

//���������Ž�
int f1[5]={0};
int f2[5];

//���Ž���ٹ��̣���ӡ�����ˮ��·��
int l1[6];
int l2[6];
void Test()
{
	//���������Ž�
	f1[0] = e1 + s1[0];
	f2[0] = e2 + s2[0];
	//FasttestWay();
	for (int i = 1; i < 6; i++)
	{
		if (f1[i-1]+s1[i] < f2[i-1]+t[1][i-1]+s1[i])
		{
			f1[i] = f1[i-1]+s1[i];
			l1[i] = 1;
		}
		else
		{
			f1[i] = f2[i-1]+t[1][i-1]+s1[i];
			l1[i] = 2;
		}

		if ( (f2[i-1]+s2[i]) < (f1[i-1]+t[2][i-1]+s1[i]) )
		{
			f2[i] = f2[i-1]+s2[i];
			l2[i] = 1;
		}
		else
		{
			f2[i] = f1[i-1]+t[2][i-1]+s1[i];
			l2[i] = 2;
		}
	}
	std::cout<<f1[5]<<std::endl;
	std::cout<<f2[5]<<std::endl;
}