#include "stdafx.h"
#include "MemoryBlock.h"


CMemoryBlock::CMemoryBlock()
{
	headBusy = new BlockNode();
	headBusy->next = NULL;
	//headBusy->pre = NULL;
	head = NewMemoryBlock(1);

	/*BlockNode *first = NewMemoryBlock(head);
	BlockNode *second = NewMemoryBlock(first);
	BlockNode *third = NewMemoryBlock(second);
	BlockNode *fourth = NewMemoryBlock(third);*/
	tail = head;
	NewMemoryBlock();
	NewMemoryBlock();
	NewMemoryBlock();
	NewMemoryBlock();
	NewMemoryBlock();
	NewMemoryBlock();
	head = Sort(head);
	
}
void CMemoryBlock::InsertBusy(int addr,int size){
	BlockNode *node = new BlockNode();
	node->size = size;
	node->addr = addr;
	//headBusy->next = node;
	node->next = headBusy->next;
	headBusy->next = node;

}
void CMemoryBlock::DisplayBusy(){
	BlockNode *node = headBusy->next;
	cout << " 被占用的分区 ：" << endl << endl;
	cout << " 起始地址   " << "分区大小" << endl;
	while (node != NULL)
	{

		cout << "   " << node->addr << "         " << node->size << "K" << endl;
		node = node->next;

	}
}
BlockNode* CMemoryBlock::NewMemoryBlock(int i){
	BlockNode *node = new BlockNode();
//	node->blockId = 1;
	node->size = 0;
	node->addr = 100;
	//node->pre = NULL;
	node->next = NULL;
	return node;
}
int CMemoryBlock::RandomNum(){
	int i = 0;
	while (i == 0){
		i = rand() % 100;
	}
	return i;
}
void CMemoryBlock::NewMemoryBlock(int addrr, int size){
	BlockNode *node = new BlockNode();
	//node->blockId = prenode->blockId + 1;
	node->size = size;
	node->addr = addrr;
	//node->pre = tail;
	node->next = NULL;

	tail->next = node;
	tail = node;
	tail->next = NULL;
}
void CMemoryBlock::NewMemoryBlock(){
	BlockNode *node = new BlockNode();
	//node->blockId = prenode->blockId + 1;
	node->size = RandomNum();	
	node->addr = tail->addr + tail->size+RandomNum();
	//node->pre = tail;
	node->next = NULL;

	tail->next = node;
	tail = node;
	

}
void CMemoryBlock::Display(){
	BlockNode *node = head->next;
	cout << " 当前有 " << Size() << " 个分区" << endl<<endl;
	cout << " 起始地址   " << "分区大小" << endl;
	while (node!= NULL)
	{
		
		cout<<"   "<< node->addr << "         " << node->size<<"K" << endl;
		node = node->next;

	}
}
void CMemoryBlock::NewBlock(){
	 NewMemoryBlock();
	
	 head = Sort(head);
}
void CMemoryBlock::RemoveBusy(int addr){
	BlockNode *node = headBusy;
	while (node->next->addr!= addr)
	{
		node = node->next;
	}
	BlockNode *copy = node->next;
	node->next = copy->next;
	free(copy);
}
int CMemoryBlock::Size(){
	int num = 0;
	BlockNode *node = head->next;
	while (node != NULL)
	{
		num++;
		node = node->next;
	}
	return num;
}
void CMemoryBlock::Return(){
	int leap1 = 0;
	int leap2 = 0;
	int re_addr, re_size;
	cout << "输入回收的地址和大小" << endl;
	cin >> re_addr >> re_size;
	BlockNode *node = new BlockNode();
	node->size = re_size;
	node->addr = re_addr;
	RemoveBusy(re_addr);
	int add = node->size + node->addr;
	BlockNode *node1 = head->next;
	while (node1 != NULL){
		
		if (add == node1->addr){
			/*node1->addr = node->addr;
			node1->size = node->size + node1->size;*/
			leap1 = 1;
		}
		if (node->addr == node1->addr + node1->size){
			/*node1->size = node->size + node1->size;*/
			leap2 = 1;
		}
		node1 = node1->next;
	}
	/*cout << "leap1 = " << leap1 << endl;
	cout << "leap2 = " << leap2 << endl;*/
	if (leap1 == 1&&leap2 == 1){
		BlockNode *node2 = head->next;
		while (node2 != NULL)
		{
			if (node->addr == node2->addr + node2->size){
				node2->size = node2->size + node->size;
				break;
			}
			node2 = node2->next;
		}
		BlockNode *node3 = head->next;
		while (node3 != NULL){
			if (add == node3->addr){
				/*node2->size = node2->size + node->size + node2->next->size;*/
				break;
			}
			node3 = node3->next;
		}
		node2->size = node2->size + node3->size;
		RemoveNode(node3);
	}
	else if (leap1 == 1 && leap2 != 1){
		BlockNode *node2 = head->next;
		while (node2 != NULL){
			if (add == node2->addr){
				node2->addr = node->addr;
				node2->size = node->size + node2->size;
				break;
			}
			node2 = node2->next;
		}
	}
	else if (leap1 != 1 && leap2 == 1){
		BlockNode *node2 = head->next;
		while (node2 != NULL){
			if (node->addr == node2->addr + node2->size){
				//node2->addr = node->addr;
				node2->size = node->size + node2->size;
				break;
			}
			node2 = node2->next;
		}
	}
	else{
		/*NewMemoryBlock(node->addr, node->size);
		head = Sort(head);*/
		Insert(head, node);
	}
	head  = Sort(head);

}
void CMemoryBlock::Insert(BlockNode *head, BlockNode *node){
	BlockNode *NODE = head;
	while (NODE->next->size < node->size||NODE->next->size==node->size){
		NODE = NODE->next;	
	}
	if (NODE->next != NULL){
	node->next = NODE->next;
	//node->pre = NODE->pre;
	NODE->next = node;
	}
	else
	{
		NODE->next = node;
	}
}


//按进程优先级对队列中的进程进行排序
BlockNode *CMemoryBlock::Sort(BlockNode *head)
{
	BlockNode *temp, *q, *p;
	for (q = head; q->next != NULL; q = q->next)
		for (p = q->next; p->next != NULL; p = p->next)
		{
			if (((p->next)->size) < ((q->next)->size) || ((p->next)->size) == ((q->next)->size))
				if (q->next == p)
				{
					temp = p->next;
					p->next = p->next->next;
					temp->next = p;
					q->next = temp;
					p = temp;
				}
				else
				{
					temp = p->next;
					p->next = q->next;
					q->next = temp;
					temp = p->next->next;
					p->next->next = q->next->next;
					q->next->next = temp;
				}
		}
	return head;
}
int CMemoryBlock::Dynamic_allocation(){
	cout <<endl<< "当前最大分区为 " << MaxSize() << "K" << endl;
	cout << "请输入需要分配的分区大小：" << endl;
	int needSize;
	cin >> needSize;
	cout << endl << endl;
	BlockNode *node = Allocation(needSize);
	if (node == NULL){
		cout << "当前无合适的分区可分配" << endl;
		return 0;
	}
	cout << "分配的分区起始地址为 ：" << node->addr << endl;
	int differece = abs(needSize - node->size);
	if (differece < 1 || differece == 1){
		cout << "分配的分区大小为 ：" << node->size << endl;
		InsertBusy(node->addr, node->size);
		RemoveNode(node);
	}
	else
	{
		cout << "分配的分区大小为 ：" << needSize << endl;
		InsertBusy(node->addr, needSize);
		ChangeNode(node,needSize);
	}
	head = Sort(head);
	return 1;

}
void CMemoryBlock::RemoveNode(BlockNode *node){
	BlockNode *linknode = head;
	while (linknode->next != node)
	{
		linknode = linknode->next;
	}
	if (linknode->next != NULL){
		
		linknode->next = node->next;
		if (linknode->next == NULL){
			tail = linknode;
		}
	}

}
void CMemoryBlock::ChangeNode(BlockNode *node,int needsize){
	BlockNode *linknode = head;
	while (linknode != node)
	{
		linknode = linknode->next;
	}
	if (linknode != NULL){
		//cout << linknode->size << " " << linknode->addr << endl;
		linknode->size = linknode->size - needsize;
		linknode->addr = linknode->addr + needsize;
		//cout << linknode->size << " " << linknode->addr << endl;
	}

}
BlockNode* CMemoryBlock::Allocation(int needsize){
	BlockNode *node = head->next;
	while (node != NULL){
		if (node->size > needsize || node->size == needsize){
			return node;
		}
		node = node->next;
	}
	return NULL;
}
int CMemoryBlock::MaxSize(){
	int max = 0;
	BlockNode *node = head->next;
	while (node!=NULL)
	{
		if (node->size > max)
			max = node->size;
		node = node->next;
	}
	return max;
}
void CMemoryBlock::Delete(){
	BlockNode *node = head;
	while (node->next != NULL)
	{
		BlockNode *copy = node;
		node = node->next;
		delete(copy);
	}
}
CMemoryBlock::~CMemoryBlock()
{
	Delete();
	//cout << "Run at ~CMemoryBlock" << endl;
}
