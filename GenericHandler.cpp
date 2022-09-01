#include "GenericHandler.h"
#include "Line.h"
#include "GetInteger.h"


void GenericHandler::ShowGenMenu() const
{
	cout << LINE80 << endl;
	cout << "\t\t\t�� ���� �� ��ǰ ���� ���α׷�" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  �� ���� ����" << endl;
	cout << "\t\t\t\t2.  ��ǰ ���� ����" << endl;
	cout << "\t\t\t\t3.  �ֹ� ���� ����" << endl;
	cout << "\t\t\t\t4.  ���α׷� ����" << endl;
	cout << LINE80 << endl;
}

void GenericHandler::CltMenu()
{
	while (1)
	{		
		int sel;
		cltManager.ShowClientMenu();
		cout << "�޴��� �����ϼ���: ";
		sel = GetInt::GetIntger(1, 3);

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
		else				// ó������
		{
			system("cls");
			break;
		}
	}
}

void GenericHandler::ProdMenu()
{
	while (1)
	{
		int sel;
		prodManager.ShowProdMenu();
		cout << "�޴��� �����ϼ���: ";
		sel = GetInt::GetIntger(1, 3);

		if (sel == 1)	// ��ǰ���
		{
			system("cls");
			prodManager.AddProdMenu();
		}
		else if (sel == 2)	// ������ȸ��������
		{
			system("cls");
			prodManager.SearchProdMenu();
		}
		else				// ó������
		{
			system("cls");
			break;
		}
	}
}