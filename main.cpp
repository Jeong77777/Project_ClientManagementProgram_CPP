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
		cout << "선택: ";
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
			cout << "잘못 입력하셨습니다." << endl;
		}
	}



	return 0;
}