#include "ProductHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>

void ProductHandler::ShowMenu() const
{
	/*** ��ǰ ���� ���� �޴� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ǰ ���� ����" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ǰ ���" << endl;
	cout << "\t\t\t\t2.  ��ǰ ��ȸ(����, ����)" << endl;
	cout << "\t\t\t\t3.  ó������" << endl;
	cout << LINE80 << endl;
}

void ProductHandler::AddProdMenu()
{
	/*** ��ǰ ��� �޴� ***/
	int id;       // ��ǰID
	int classif;  // ��ǰ�з�
	string name;  // ��ǰ��
	int stock;    // ������
	int price;    // ��ǰ����

	/*** ��ǰ ���� �Է� �ް� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ǰ ���" << endl;
	cout << LINE80 << endl;
	cout << "��ǰID: ";
	id = MakeProdId();
	cout << "��ǰ�з�(1. ġ�����  2. ġ�����  3. ������ǰ): ";
	classif = GetInt::GetIntger(1, 3);
	cout << "��ǰ��: ";	cin >> name;
	cout << "������: ";
	stock = GetInt::GetIntger();
	cout << "����: ";
	price = GetInt::GetIntger();
	Product* newProduct = new Product(id, classif, name, stock, price);
	ProductList.insert({ id, newProduct });
	cout << "\n��ǰ ��� �Ϸ�!\n" << endl;

	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}

void ProductHandler::SearchProdMenu()
{
	int sel;

	/*** ��ǰ ��ȸ �޴� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ǰ ��ȸ(����, ����)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ǰID�� ��ȸ" << endl;
	cout << "\t\t\t\t2.  ��ǰ������ ��ȸ" << endl;
	cout << "\t\t\t\t3.  ��ǰ ������ ��ȸ" << endl;
	cout << "\t\t\t\t4.  ��ü ��ǰ ��ȸ" << endl;
	cout << "\t\t\t\t5.  ���� �޴�" << endl;
	cout << LINE80 << endl;

	/*** �� ��ȸ �޴� ���� ***/
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetIntger(1, 5);

	if (sel == 1)
		SearchProdUsingIdMenu();
	//else if (sel == 2);
	////SearchCltUsingNameMenu();
	//else if (sel == 3);
	////SearchProdUsingClasMenu();
	//else if (sel == 4);
	//	//ShowAllProdInfoMenu();
	//else if (sel == 4);
	//	system("cls");
}

void ProductHandler::SearchProdUsingIdMenu()
{
	/*** ��ǰID�� �˻� ***/
	int id;
	Product* product;
	cout << "��ǰID�� �Է��ϼ���(1001���� 9999������ ����): ";
	id = GetInt::GetIntger(1001, 9999);
	product = SearchProdUsingId(id);
	ShowSearchResult(product);
	system("pause");
	/*** ����/���� �޴� ***/
	if (product != nullptr)
		;//ProdDeleteModifyMenu(product);
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}

void ProductHandler::ShowSearchResult(Product* client) const
{
	/*** ID�� �˻��� ��� ��� ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE80 << endl;
	cout << setw(8) << left << "��ǰID";
	cout << setw(10) << left << "��ǰ�з�";
	cout << setw(20) << left << "��ǰ��";
	cout << setw(10) << left << "������";
	cout << setw(10) << left << "����" << endl;
	cout << LINE80 << endl;

	if (client != nullptr) {
		client->ShowProdInfo();
		cout << endl;
	}
	else {
		cout << "\n�������� �ʴ� ��ID�Դϴ�.\n" << endl;
	}
}

Product* ProductHandler::SearchProdUsingId(int id) const
{
	/*** ��ǰID�� �˻� ***/
	auto i = ProductList.find(id);

	if (i != ProductList.end())
		return i->second;
	else
		return nullptr;
}



int ProductHandler::MakeProdId()
{
	/*** �ߺ����� �ʴ� ID ���� ***/
	int id;
	while (1) {
		id = GetInt::GetIntger();

		if (id < 1000 || id > 10000) {
			cout << "1001���� 9999������ ���ڸ� �Է��ϼ���: ";
		}
		else if (ProductList.find(id) != ProductList.end())
			cout << "�ߺ��� ��ǰID�Դϴ�. �ٽ� �Է��ϼ���. ";
		else
			break;
	}
	return id;
}