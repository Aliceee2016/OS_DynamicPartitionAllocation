#pragma once
#include <stdlib.h>
class CBlockNode
{
public:
	CBlockNode();
	CBlockNode(CBlockNode *pre);
	~CBlockNode();
	int size;
	int addr;
	CBlockNode *pre;
	CBlockNode *next;
	const int addr_first = 100;
};

