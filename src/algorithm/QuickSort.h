//lihf 2012/11/26 ��������
/*
���Ļ���˼���ǣ�
ͨ��һ������Ҫ��������ݷָ�ɶ����������֣�
����һ���ֵ��������ݶ�������һ���ֵ��������ݶ�ҪС��
Ȼ���ٰ��˷����������������ݷֱ���п�������
����������̿��Եݹ���У�
�Դ˴ﵽ�������ݱ���������С�

*/
 //int arry[8] = {2,8,7,1,3,5,6,4};
 
 int arry[8] = {1,2,3,4,5,6,7,8};

 /*
 ��Ҫ�����������A[0]����A[N-1]��
 ��������ѡȡһ�����ݣ�ͨ��ѡ������ĵ�һ��������Ϊ�ؼ����ݣ�
 Ȼ�����б���С�������ŵ���ǰ�棬
 ���б�����������ŵ������棬
 ������̳�Ϊһ�˿�������

 */
// int Partion( int* a,int p, int r)
// {
// 	//��С���򻬶����ڵ�ָ��
// 	int i = p;
// 
// 	//��Ԫ
// 	int x = a[r];
// 
// 	//�ƶ�����ָ��
// 	int j = i;
// 	for (; j < r; j++)
// 	{
// 		if (a[j] < x && j != i)
// 		{
// 			int nTemp = a[i];
// 			a[i] = a[j];
// 			a[j] = nTemp;
// 			i++;
// 			
// 		}
// 	}
// 	//��󽻻���Ԫ p �� i ��С�� x 
// 	int nTemp = a[i];
// 	a[i] = a[j];
// 	a[j] = nTemp;
// 	return i;
// }

 // algorithm 2
 int  Partion( int* a,int nStart, int nEnd)
 {
	 //ȷ����Ԫ��λ��
	 int x = a[nStart];

	 int i = nStart;
	 int j = nEnd;
	 while (i<j)
	 {
		 //�Ӻ���ǰ�ҵ���һ��С����Ԫ������ǰ����ʱλ��i����
		 while(a[j]>x && j != i)
			 j--;
		 if (j != i)
		 {
			 a[i++] = a[j];
		 }
		  //��ǰ����ҵ���һ��������Ԫ������������ʱλ��j����
		 while(a[i] < x && j != i)
			i++;
		 if (j != i)
		 {
			 a[j--] = a[i];
		 }
	 }
	 //���ȷ����Ԫ��λ��
	 a[i] = x;
	 return i;
 }
void QuickSort(int* a,int p, int r)
{
	if (p < r)
	{
		int i = Partion(a,p,r);
		QuickSort(a,p,i-1);
		QuickSort(a,i+1,r);
	}
	
}
void Disp()
{
	for (int i=0; i<8; i++)
	{
		std::cout<<arry[i]<<" ";
	}
}
void Test()
{
	QuickSort(arry,0,7);
	Disp();
}


