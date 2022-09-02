#include "OrderHandler.h"
#include "GetInteger.h"
#include "Line.h"
#include <iostream>

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
	cout << "�ֹ� ������ �Է��ϼ���: ";
	prodNum = GetInt::GetInteger();
	num = MakeOrderNum();

	/*** �ֹ� ���� ��� ***/
	Order* newOrder = new Order(num, date, cltID, prodID, prodNum);
	orderList.insert({ num, newOrder });
	cout << "\n�ֹ� ���� ��� �Ϸ�!\n" << endl;

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
		;//SearchOrderUsingIdMenu();
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

string OrderHandler::GetDateString()
{
	/*** string������ ��¥ �Է¹ޱ� ***/
	string strDate;	// ��¥
	int intDate;
	int day, month, year;

	cout << "�ֹ���¥ �Է�(ex 20220907): ";

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

	cout << "��ID�� �Է��ϼ���: ";
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

	cout << "��ǰID�� �Է��ϼ���: ";
	while (1) {
		id = GetInt::GetInteger();
		if (cltManager.SearchCltUsingId(id) != nullptr)
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
		return 1001;
	}
	else {
		int num = (--key)->first;
		return ++num;
	}
}