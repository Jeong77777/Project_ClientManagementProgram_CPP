#include "GenericHandler.h"


void GenericHandler::ShowMenu() const
{
	cout << "-----��ǰ ���� ���α׷�------" << endl;
	cout << "1. �� ���� ����" << endl;
	cout << "2. ��ǰ ���� ����" << endl;
	cout << "3. �Ǹ� ���� ����" << endl;
	cout << "4. ���α׷� ����" << endl;
}

void GenericHandler::CltMenu()
{
	while (1)
	{
		//system("cls");
		int sel;
		cltManager.ShowMenu();
		cout << "����: ";	cin >> sel;

		if (sel == 1)
			cltManager.AddClient();
		else if (sel == 2)
			cltManager.SearchClient();
		else if (sel == 3)
		{
			int id;
			cout << "\n������ ��ID�� �Է��Ͻÿ�: " << endl;
			cin >> id;
			cltManager.DeleteClient(id);
		}
		else if(sel==4)
			break;			
		else
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
	}
}