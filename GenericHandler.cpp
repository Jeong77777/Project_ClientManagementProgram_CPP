#include "GenericHandler.h"
#include "Line.h"


void GenericHandler::ShowMenu() const
{
	cout << LINE80 << endl;
	cout << "\t\t\t�� ���� �� ��ǰ ���� ���α׷�" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  �� ���� ����" << endl;
	cout << "\t\t\t\t2.  ��ǰ ���� ����" << endl;
	cout << "\t\t\t\t3.  �Ǹ� ���� ����" << endl;
	cout << "\t\t\t\t4.  ���α׷� ����" << endl;
	cout << LINE80 << endl;
}

void GenericHandler::CltMenu()
{
	while (1)
	{		
		int sel;
		cltManager.ShowMenu();
		cout << "�޴��� �����ϼ���: ";	cin >> sel;

		if (sel == 1)	// �ű԰����
		{
			system("cls");
			cltManager.AddClientMenu();
		}			
		else if (sel == 2)	// ������ȸ��������
		{
			system("cls");
			cltManager.SearchClientMenu();
		}			
		else if (sel == 3)	// ó������
		{
			system("cls");
			break;
		}
		else
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
	}
}