#include "GenericHandler.h"
#include "GetInteger.h"


int main()
{
	GenericHandler genHandler;
	int choice;

	while (1)
	{
		/* ���� �޴� ��� */
		genHandler.ShowGenMenu();
		cout << "�޴��� �����ϼ���: ";
		choice = GetInt::GetInteger(1, 4);

		switch (choice)
		{
		case 1: // �� ���� ���� �޴�
			system("cls");
			genHandler.CltMenu();
			break;
		case 2: // ��ǰ ���� ���� �޴�
			system("cls");
			genHandler.ProdMenu();
			break;
		case 3: // �ֹ� ���� ���� �޴�
			system("cls");
			genHandler.OrderMenu();
			break;
		case 4:	//exit
			return 0;	
		}
	}

	return 0;
}