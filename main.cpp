//#include <iostream>
//#include <vector>
//#include <algorithm>
#include "GenericHandler.h"


int main()
{
	GenericHandler genManager;
	int choice;

	while (1)
	{
		system("cls");
		genManager.ShowMenu();
		cout << "����: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			genManager.CltMenu();
			break;
		case 2:
			//genManager.ProdMenu();
			break;
		case 3:
			//genManager.SalesMenu();
			break;
		case 4:	//exit
			return 0;
		default:
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		}
	}



	return 0;
}