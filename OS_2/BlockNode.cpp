#include "stdafx.h"
#include "BlockNode.h"


CBlockNode::CBlockNode()
{
	size = rand() % 100;
	addr = 100;
	pre = NULL;
	next = NULL;
}
CBlockNode::CBlockNode(CBlockNode *prenode)
{
	size = rand() % 100;
	addr = pre->addr + pre->size;
	pre = prenode;
	
	next = NULL;
}


CBlockNode::~CBlockNode()
{
}
