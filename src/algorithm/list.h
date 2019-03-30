//lihf 2019/03/03 ��������ת

struct sNode
{
	int key;
	sNode* pNext;
	sNode()
	{
		key =0;
		pNext = NULL;
	}
};
void InitList(sNode* head)
{
	sNode* node = new sNode;
	node->key = 1;
	head->pNext = node;

	sNode* tail = node;
	for (int i=2; i<=5; i++)
	{
		sNode* node = new sNode;
		node->key = i;
		tail->pNext = node;
		tail = node;
	}
}
void Display(sNode* head)
{
	sNode* p=head;
	while(p)
	{
		std::cout<<p->key;
		p = p->pNext;
	}
}
//lihf 2019/03/03 �͵ط�ת��
void Reverge(sNode* h)
{
	sNode* pre = h->pNext;
	if (pre)
	{
		//lihf 2019/03/03 pcur����Ҫ��ת�Ľڵ�
		sNode* pcur = pre->pNext;
		while (pcur)
		{
			pre->pNext = pcur->pNext;	//��֤��������
			pcur->pNext = h->pNext;			//��ת
			h->pNext = pcur;			//����ͷ

			pcur = pre->pNext;		
		}
			

	}
}
void Test()
{
	int i=0;
	int j=0;
	i++;
	++j;
	sNode* head = new sNode;
	InitList(head);
	Display(head);
	Reverge(head);
	Display(head);
}