#include "stdafx.h"
#include "MemoryBlock.h"


CMemoryBlock::CMemoryBlock()
{
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
BlockNode* CMemoryBlock::NewMemoryBlock(int i){
	BlockNode *node = new BlockNode();
//	node->blockId = 1;
	node->size = 0;
	node->addr = 100;
	node->pre = NULL;
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
void CMemoryBlock::NewMemoryBlock(){
	BlockNode *node = new BlockNode();
	//node->blockId = prenode->blockId + 1;
	node->size = RandomNum();	
	node->addr = tail->addr + tail->size+RandomNum();
	node->pre = tail;
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
		RemoveNode(node);
	}
	else
	{
		cout << "分配的分区大小为 ：" << needSize << endl;
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
