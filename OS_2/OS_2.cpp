// OS_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MemoryBlock.h"

//�����Ӧ�㷨


int _tmain(int argc, _TCHAR* argv[])
{
	int num = 1;
	CMemoryBlock *memory = new CMemoryBlock();
	while (num != 0){
		cout << " ������Ӧ�Ĳ����õ���Ӧ�Ľ��" << endl;
		cout << " 1  �����ڴ�ռ�" << endl;
		cout << " 2  �鿴�ڴ����" << endl;
		cout << " 3  ����" << endl;
		cout << " 0  �˳�" << endl;
		
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

