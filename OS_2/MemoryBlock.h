#pragma once
#include <stdlib.h>
using namespace std;
#include <iostream>
#include <iomanip>
#include <cstdlib>
typedef struct NODE{
	
	int size;
	int addr;
	struct NODE *pre;
	struct NODE *next;

}BlockNode;
class CMemoryBlock
{
public:
	CMemoryBlock();
	~CMemoryBlock();
	void NewBlock();
	void Display();
	int Dynamic_allocation();
	
private:
	BlockNode *Sort(BlockNode *head);
	BlockNode *head;
	BlockNode *tail;
	void NewMemoryBlock();
	BlockNode *NewMemoryBlock(int i);
	int RandomNum();
	int Size();
	void Delete();
	int MaxSize();
	BlockNode *Allocation(int needsize);
	void RemoveNode(BlockNode *node);
	void ChangeNode(BlockNode *node,int needsize);
	//void exchangeNode(BlockNode* left, BlockNode* right);
	//void bubbleSort();
	
};

