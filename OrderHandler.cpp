#include "OrderHandler.h"
#include "GetInteger.h"
#include "Line.h"
#include <iostream>
#include <iomanip>

OrderHandler::OrderHandler(ClientHandler& cltRef, ProductHandler& prodRef)
	:cltManager(cltRef), prodManager(prodRef)
{
}

void OrderHandler::ShowOrderMenu() const
{
	/*** �ֹ� ���� ���� �޴� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t�ֹ� ���� ����" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  �ֹ� ���� ���" << endl;
	cout << "\t\t\t\t2.  �ֹ� ���� ��ȸ(����, ����)" << endl;
	cout << "\t\t\t\t3.  ó������" << endl;
	cout << LINE80 << endl;
}

void OrderHandler::AddOrderMenu()
{
	/*** �ֹ� ���� ��� �޴� ***/
	int num;		// �ֹ���ȣ
	string date;	// �ֹ���¥
	int cltID;		// ��ID
	int prodID;		// ��ǰID
	int prodNum;	// �ֹ�����

	/*** �ֹ� ���� �Է� �ޱ� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t�ֹ� ���� ���" << endl;
	cout << LINE80 << endl;

	date = GetDateString();
	cltID = GetCltID();
	prodID = GetProdID();
	cout << "�ֹ� ����: ";
	prodNum = GetInt::GetInteger();
	num = MakeOrderNum();

	/*** �ֹ� ���� ��� ***/
	Order* newOrder = new Order(num, date, cltID, prodID, prodNum);
	orderList.insert({ num, newOrder });
	cout << "\n�ֹ� ���� ��� �Ϸ�!" << endl;
	cout << "�ֹ���ȣ�� " << num << "�Դϴ�.\n" << endl;

	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}

void OrderHandler::SearchOrderMenu()
{
	int sel;

	/*** ��ǰ ��ȸ �޴� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t�ֹ� ���� ��ȸ(����, ����)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  �ֹ���ȣ�� ��ȸ" << endl;
	cout << "\t\t\t\t2.  ��ID�� ��ȸ" << endl;
	cout << "\t\t\t\t3.  ��ǰID�� ��ȸ" << endl;
	cout << "\t\t\t\t4.  ��¥�� ��ȸ" << endl;
	cout << "\t\t\t\t5.  ��ü �ֹ� ���� ��ȸ" << endl;
	cout << "\t\t\t\t6.  ���� �޴�" << endl;
	cout << LINE80 << endl;

	/*** ��ǰ ��ȸ �޴� ���� ***/
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 5);

	if (sel == 1)
		SearchOrderUsingNumMenu();
	else if (sel == 2)
		;//SearchOrderUsingNameMenu();
	else if (sel == 3)
		;//SearchOrderUsingClasMenu();
	else if (sel == 4)
		;//ShowAllOrderInfoMenu();
	else if (sel == 5)
		;//ShowAllOrderInfoMenu();
	else
		system("cls");
}

void OrderHandler::SearchOrderUsingNumMenu()
{
	/*** �ֹ���ȣ�� �˻� ***/
	int num;
	Order* order;
	cout << "�ֹ���ȣ�� �Է��ϼ���: ";
	num = GetInt::GetInteger();
	order = SearchOrderUsingNum(num);
	ShowSearchResult(order);

	/*** ����/���� �޴� ȣ�� ***/
	if (order != nullptr)
		;//ProdDeleteModifyMenu(product);
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}

Order* OrderHandler::SearchOrderUsingNum(int num) const
{
	/*** �ֹ���ȣ�� �˻� ***/
	auto i = orderList.find(num);

	if (i != orderList.end())
		return i->second;
	else
		return nullptr;
}

void OrderHandler::ShowSearchResult(Order* order) const
{
	/*** �ֹ���ȣ�� �˻��� ��� ��� ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE80 << endl;
	cout << setw(16) << left << "�ֹ���ȣ";
	cout << setw(14) << left << "�ֹ���¥";
	cout << setw(30) << left << "��ǰID(��ǰ��)";
	cout << setw(12) << left << "�ֹ�����";
	cout << setw(10) << left << "�ֹ��ݾ�" << endl;
	cout << setw(16) << left << "��ID(�̸�)";
	cout << setw(14) << left << "��ȭ��ȣ";
	cout << setw(30) << left << "�ּ�" << endl;
	cout << LINE80 << endl;
	
	if (order != nullptr) {
		ShowOrderInfoRow1(order);
		ShowOrderInfoRow2(order);
		cout << endl;
	}
	else {
		cout << "\n�������� �ʴ� �ֹ���ȣ�Դϴ�.\n" << endl;
	}
	system("pause");
}

void OrderHandler::ShowOrderInfoRow1(Order* order) const
{
	/*** �ֹ� ���� 1�� ��� ***/

	/*** �ֹ���ȣ ***/
	cout << setw(16) << left << order->GetOrderNum();

	/*** �ֹ���¥ ***/
	cout << setw(14) << left << order->GetOrderDate();

	/*** ��ǰID(��ǰ��) ***/
	Product* product = prodManager.SearchProdUsingId(order->GetOrderProdID());
	if (product != nullptr) {
		cout << setw(30) << left << to_string(product->GetProdID()) + \
			'(' + product->GetProdName() + ')';
	}
	else {
		cout << setw(30) << left << "��ǰ ���� ����";
	}

	/*** �ֹ����� ***/
	cout << setw(12) << left << order->GetOrderProdNum();

	/*** �ֹ��ݾ� ***/
	if (product != nullptr) {
		cout << setw(10) << left << order->GetOrderProdNum() * product->GetProdPrice() << endl;
	}
	else {
		cout << setw(10) << left << "��ǰ ���� ����" << endl;
	}
}

void OrderHandler::ShowOrderInfoRow2(Order* order) const
{
	/*** �ֹ� ���� 2�� ��� ***/

	/*** ��ID(�̸�), ��ȭ��ȣ, �ּ� ***/
	Client* client = cltManager.SearchCltUsingId(order->GetOrderCltID());
	if (client != nullptr) {
		cout << setw(16) << left << to_string(client->getCltID()) + \
			'(' + client->GetCltName() + ')';
		cout << setw(14) << left << client->GetCltPhoneNumber();
		cout << setw(30) << left << client->GetCltAddress() << endl;
	}
	else {
		cout << setw(16) << left << "�� ���� ����";
	}
}

string OrderHandler::GetDateString()
{
	/*** string������ ��¥ �Է¹ޱ� ***/
	string strDate;	// ��¥
	int intDate;
	int day, month, year;

	cout << "�ֹ���¥(ex 20220907): ";

	while (1) {
		intDate = GetInt::GetInteger();
		year = intDate / 10000;
		month = (intDate - (year * 10000)) / 100;
		day = intDate % 100;
		if (CheckValidDate(year, month, day)) {
			strDate = to_string(year) + '-';
				if (month < 10) strDate += '0';
				strDate += to_string(month) + '-';
				if (day < 10) strDate += '0';
				strDate += to_string(day);
				return strDate;
		}
		else
			cout << "��ȿ���� ���� ��¥�Դϴ�. �ٽ� �Է��ϼ���: ";
	}
}

int OrderHandler::GetCltID()
{
	/*** ��ϵ� ��ID �Է¹ޱ� ***/
	int id;

	cout << "��ID: ";
	while (1) {
		id = GetInt::GetInteger();
		if (cltManager.SearchCltUsingId(id) != nullptr)
			return id;
		else
			cout << "��ϵ��� ���� ��ID�Դϴ�. �ٽ� �Է��ϼ��� : ";		
	}
}

int OrderHandler::GetProdID()
{
	/*** ��ϵ� ��ǰID �Է¹ޱ� ***/
	int id;

	cout << "��ǰID: ";
	while (1) {
		id = GetInt::GetInteger();
		if (prodManager.SearchProdUsingId(id) != nullptr)
			return id;
		else
			cout << "��ϵ��� ���� ��ǰID�Դϴ�. �ٽ� �Է��ϼ���: ";
	}
}

bool OrderHandler::CheckValidDate(int year, int month, int day)
{
	/*** ��¥�� ��ȿ�� �˻� ***/
	/*** �⵵ �˻� ***/
	if (year < 1900 || year>2999) // 1900~2999��
		return false;

	/*** ��,�� �˻� ***/
	if (month < 1 || month>12)  // 1~12
		return false;
	else {
		if ((month & 0x1) == 1) { // odd month
			if (month <= 7) {	// 1, 3, 5, 7
				if (day < 1 || day>31)
					return false;
			}
			else {	// 9, 11
				if (day < 1 || day>30)
					return false;
			}
		}
		else {					// even month
			if (month == 2) {	// 2
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
					if (day < 1 || day>29)	// ����
						return false;
				}
				else {	// ���
					if (day < 1 || day>28)
						return false;
				}
			}
			else if (month <= 6) {	// 4, 6
				if (day < 1 || day>30)
					return false;
			}
			else {	// 8, 10, 12
				if (day < 1 || day>31)
					return false;
			}
		}
	}

	return true;
}

int OrderHandler::MakeOrderNum()
{
	/*** �ߺ����� �ʴ� �ֹ���ȣ ���� ***/
	auto key = orderList.end();
	if (orderList.size() == 0) {
		return 10001;
	}
	else {
		int num = (--key)->first;
		return ++num;
	}
}