// OS_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MemoryBlock.h"

//最佳适应算法


int _tmain(int argc, _TCHAR* argv[])
{
	int num = 1;
	CMemoryBlock *memory = new CMemoryBlock();
	while (num != 0){
		cout << " 输入相应的操作得到相应的结果" << endl;
		cout << " 1  分配内存空间" << endl;
		cout << " 2  查看内存情况" << endl;
		cout << " 3  回收" << endl;
		cout << " 0  退出" << endl;
		
		cin >> num;
		switch (num)
		{
		/*case 3:
			memory->NewBlock();
			memory->Display();
			break;*/
		case 2:
			memory->Display();
			break;
		case 1:
			memory->Dynamic_allocation();
			memory->Display();
			break;
		case 3:
			memory->DisplayBusy();
			memory->Return();
			memory->Display();
			break;
		case 0:
			break;
		default:
			break;
		}
		cout << "------------------------------------------" << endl;
	}
	/*memory->Display();
	memory->Dynamic_allocation();
	memory->Display();*/
	delete(memory);
	system("pause");
	return 0;
}

