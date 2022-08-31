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
		genManager.ShowMenu();
		cout << "메뉴를 선택하세요: ";
		cin >> choice;

		while (choice < 1 || choice > 4)
		{
			if (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			cout << "다시 입력하세요: ";
			cin >> choice;
		}

		switch (choice)
		{
		case 1:
			system("cls");
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
		}
	}

	return 0;
}