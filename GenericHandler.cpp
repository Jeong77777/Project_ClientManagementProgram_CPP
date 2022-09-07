#include "GenericHandler.h"
#include "Line.h"
#include "GetInteger.h"


/**
* @brief orderHandler ��ü�� �� ����, ��ǰ ������ ���� ���ؼ�
*	 �ʱ�ȭ �ϴµ� ClientHandler, ProductHandler ��ü�� ���̰� �ִ�.
*/
GenericHandler::GenericHandler(): cltHandler(), prodHandler(), orderHandler(cltHandler, prodHandler)
{
}


/**
* @brief ���� �޴� ���
*/
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


/**
* @brief �� ���� ���� �޴�
*/
void GenericHandler::CltMenu()
{
	while (1) {
		int sel;
		cltHandler.ShowClientMenu();
		cout << "�޴��� �����ϼ���: ";
		sel = GetInt::GetInteger(1, 3);

		if (sel == 1) {	// �ű԰����
			system("cls");
			cltHandler.AddClientMenu();
		}
		else if (sel == 2) {	// ������ȸ��������
			system("cls");
			cltHandler.SearchClientMenu();
		}
		else {				// ó������
			system("cls");
			break;
		}
	}
}


/**
* @brief ��ǰ ���� ���� �޴�
*/
void GenericHandler::ProdMenu()
{
	while (1) {
		int sel;
		prodHandler.ShowProdMenu();
		cout << "�޴��� �����ϼ���: ";
		sel = GetInt::GetInteger(1, 3);

		if (sel == 1) {	// ��ǰ���
			system("cls");
			prodHandler.AddProdMenu();
		}
		else if (sel == 2) {	// ������ȸ��������
			system("cls");
			prodHandler.SearchProdMenu();
		}
		else {			// ó������
			system("cls");
			break;
		}
	}
}


/**
* @brief �ֹ� ���� ���� �޴�
*/
void GenericHandler::OrderMenu()
{
	while (1) {
		int sel;
		orderHandler.ShowOrderMenu();
		cout << "�޴��� �����ϼ���: ";
		sel = GetInt::GetInteger(1, 3);

		if (sel == 1) {	// �ֹ��������
			system("cls");
			orderHandler.AddOrderMenu();
		}
		else if (sel == 2) {	// ������ȸ��������
			system("cls");
			orderHandler.SearchOrderMenu();
		}
		else {			// ó������
			system("cls");
			break;
		}
	}
}