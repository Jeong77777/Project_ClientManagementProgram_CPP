#include "GenericHandler.h"
#include "GetInteger.h"


int main()
{
	GenericHandler genManager;
	int choice;

	while (1)
	{
		genManager.ShowMenu();
		cout << "메뉴를 선택하세요: ";
		choice = GetInt::GetIntger(1, 4);

		switch (choice)
		{
		case 1:
			system("cls");
			genManager.CltMenu();
			break;
		case 2:
			system("cls");
			genManager.ProdMenu();
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