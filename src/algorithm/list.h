//lihf 2019/03/03 单向链表反转

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
//lihf 2019/03/03 就地反转，
void Reverge(sNode* h)
{
	sNode* pre = h->pNext;
	if (pre)
	{
		//lihf 2019/03/03 pcur是需要反转的节点
		sNode* pcur = pre->pNext;
		while (pcur)
		{
			pre->pNext = pcur->pNext;	//保证链表不断裂
			pcur->pNext = h->pNext;			//反转
			h->pNext = pcur;			//接上头

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