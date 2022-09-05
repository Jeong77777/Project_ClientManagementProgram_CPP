#include "OrderHandler.h"
#include "GetInteger.h"
#include "Line.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

OrderHandler::OrderHandler(ClientHandler& cltRef, ProductHandler& prodRef)
	:cltManager(cltRef), prodManager(prodRef)
{
	ifstream file;
	file.open("orderlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int num = stoi(row[0]);
				int cltID = stoi(row[2]);
				int prodID = stoi(row[3]);
				int prodNum = stoi(row[4]);
				Order* o = new Order(num, row[1], cltID, prodID, prodNum);
				orderList.insert({ num, o });
			}
		}
	}
	file.close();
}

OrderHandler::~OrderHandler()
{
	ofstream file;
	file.open("orderlist.txt");
	if (!file.fail()) {
		for (const auto& v : orderList) {
			Order* o = v.second;
			file << o->GetOrderNum() << ", " << o->GetOrderDate() << ", ";
			file << o->GetOrderCltID() << ", " << o->GetOrderProdID() << ", ";
			file << o->GetOrderProdNum() << endl;
			delete o;
		}
	}
	file.close();
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
	string date;	// �ֹ�����
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
	cout << "\t\t\t\t4.  �ֹ����ں� ��ȸ" << endl;
	cout << "\t\t\t\t5.  ��ü �ֹ� ���� ��ȸ" << endl;
	cout << "\t\t\t\t6.  ���� �޴�" << endl;
	cout << LINE80 << endl;

	/*** ��ǰ ��ȸ �޴� ���� ***/
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 6);

	if (sel == 1)
		SearchOrderUsingNumMenu();
	else if (sel == 2)
		SearchOrderUsingCltIdMenu();
	else if (sel == 3)
		SearchOrderUsingProdIdMenu();
	else if (sel == 4)
		SearchOrderUsingDateMenu();
	else if (sel == 5)
		ShowAllOrderInfoMenu();
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
		OrderDeleteModifyMenu(order);
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
	cout << setw(15) << left << "�ֹ�����";
	cout << setw(30) << left << "��ǰID(��ǰ��)";
	cout << setw(12) << left << "�ֹ�����";
	cout << setw(10) << left << "�ֹ��ݾ�" << endl;
	cout << setw(16) << left << "��ID(�̸�)";
	cout << setw(15) << left << "��ȭ��ȣ";
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
}

void OrderHandler::ShowOrderInfoRow1(Order* order) const
{
	/*** �ֹ� ���� 1�� ��� ***/

	/*** �ֹ���ȣ ***/
	cout << setw(16) << left << order->GetOrderNum();

	/*** �ֹ����� ***/
	cout << setw(15) << left << order->GetOrderDate();

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
		cout << setw(15) << left << client->GetCltPhoneNumber();
		cout << setw(30) << left << client->GetCltAddress() << endl;
	}
	else {
		cout << setw(16) << left << "�� ���� ����" << endl;
	}
}

void OrderHandler::OrderDeleteModifyMenu(Order* order)
{
	/*** ����/���� �޴� ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. ����\t\t2. ����\t\t3. ������" << endl;
	cout << LINE80 << endl;
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) {
		DeleteOrderUsingPtr(order);
		cout << "\n���� �Ϸ�!\n" << endl;
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) {
		ModifyOrderMenu(order);
	}
	else;
}

void OrderHandler::DeleteOrderUsingPtr(Order* order)
{
	/*** ��ǰ ���� ***/
	int num = order->GetOrderNum();
	delete orderList.at(num);
	orderList.erase(num);
}

void OrderHandler::ModifyOrderMenu(Order* order)
{
	/*** ���� ���� ���� �޴� ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. �ֹ�����       2. ��ID       3. ��ǰID       4. �ֹ�����       5. ������" << endl;
	cout << LINE80 << endl;
	cout << "������ �׸��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 5);

	cout << LINE80 << endl;
	if (sel == 1) {
		string date;
		cout << "�ֹ����ڸ� �Է��ϼ���: ";
		date = GetDateString();
		order->SetOrderDate(date);
	}
	else if (sel == 2) {
		int cltID;
		cltID = GetCltID();
		order->SetOrderCltID(cltID);
	}
	else if (sel == 3) {
		int prodID;
		prodID = GetProdID();
		order->SetOrderProdID(prodID);
	}
	else if (sel == 4) {
		int prodNum;
		cout << "�ֹ������� �Է��ϼ���: ";
		prodNum = GetInt::GetInteger();
		order->SetOrderProdNum(prodNum);
	}
	else
		return;

	cout << "\n���� �Ϸ�!\n" << endl;
	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();
}

void OrderHandler::SearchOrderUsingCltIdMenu()
{
	/*** ��ID�� ��ȸ �޴� ***/
	int cltID;
	vector<Order*> searchResults;

	cltID = GetCltID();	

	/*** �˻� ��� �������� ***/
	searchResults = SearchOrderUsingCltId(cltID);

	/*** �˻� ��� ��� ***/
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE90 << endl;

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(searchResults);
}

vector<Order*> OrderHandler::SearchOrderUsingCltId(int cltID) const
{
	/*** ��ID�� �˻� ***/
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (cltID == i->second->GetOrderCltID())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void OrderHandler::ShowSearchResults(vector<Order*>& searchResults) const
{
	/*** �˻��� ����� ��� ***/
	int cnt = 1;	
	cout << LINE90 << endl;
	cout << setw(10) << left << "��ȣ";
	cout << setw(16) << left << "�ֹ���ȣ";
	cout << setw(15) << left << "�ֹ�����";
	cout << setw(30) << left << "��ǰID(��ǰ��)";
	cout << setw(12) << left << "�ֹ�����";
	cout << setw(10) << left << "�ֹ��ݾ�" << endl;
	cout << "          ";
	cout << setw(16) << left << "��ID(�̸�)";
	cout << setw(15) << left << "��ȭ��ȣ";
	cout << setw(30) << left << "�ּ�" << endl;
	cout << LINE90 << endl;

	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		ShowOrderInfoRow1(*i);
		cout << "          ";
		ShowOrderInfoRow2(*i);
		cout << '\n';
		cnt++;
	}	
}

void OrderHandler::SelectInSearchMenu(vector<Order*>& list)
{
	/*** �˻� ��Ͽ��� �����ϱ� ***/
	int sel;
	if (list.size() != 0) {
		cout << "���� �Ǵ� ������ �׸��� �����ϼ���(������ 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/*** ����/���� �޴� ���� ***/
			OrderDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}

void OrderHandler::SearchOrderUsingProdIdMenu()
{
	/*** ��ǰID�� ��ȸ �޴� ***/
	int prodID;
	vector<Order*> searchResults;

	prodID = GetProdID();

	/*** �˻� ��� �������� ***/
	searchResults = SearchOrderUsingProdId(prodID);

	/*** �˻� ��� ��� ***/
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE90 << endl;

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(searchResults);
}

vector<Order*> OrderHandler::SearchOrderUsingProdId(int prodID) const
{
	/*** ��ǰID�� �˻� ***/
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (prodID == i->second->GetOrderProdID())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void OrderHandler::SearchOrderUsingDateMenu()
{
	/*** ���ں� ��ȸ �޴� ***/
	string date;
	vector<Order*> searchResults;

	date = GetDateString();

	/*** �˻� ��� �������� ***/
	searchResults = SearchOrderUsingDate(date);

	/*** �˻� ��� ��� ***/
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE90 << endl;

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(searchResults);
}

vector<Order*> OrderHandler::SearchOrderUsingDate(string date) const
{
	/*** ���ڷ� �˻� ***/
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (date == i->second->GetOrderDate())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void OrderHandler::ShowAllOrderInfoMenu()
{
	/*** ��ü �ֹ� ���� ��ȸ �޴� ***/

	/*** ��ü �ֹ� ���� ������� �������� ***/
	vector<Order*> allOrders;
	for (auto i = orderList.begin(); i != orderList.end(); i++)
		allOrders.push_back(i->second);

	/*** ��ü �ֹ� ���� ��� ***/
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t��ü �ֹ� ���� ��ȸ" << endl;
	ShowSearchResults(allOrders);
	cout << "\n>> �� " << allOrders.size() << "���� �ֹ� ����\n" << endl;
	cout << LINE90 << endl;	

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(allOrders);
}

string OrderHandler::GetDateString()
{
	/*** string������ ��¥ �Է¹ޱ� ***/
	string strDate;	// ��¥
	int intDate;
	int day, month, year;

	cout << "�ֹ����ڸ� �Է��ϼ���(ex 20220907): ";

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
			cout << "��ϵ��� ���� ��ID�Դϴ�. �ٽ� �Է��ϼ���: ";		
	}
}

int OrderHandler::GetProdID()
{
	/*** ��ϵ� ��ǰID �Է¹ޱ� ***/
	int id;

	cout << "��ǰID�� �Է��ϼ���: ";
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

vector<string> OrderHandler::parseCSV(istream& file, char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	while (!file.eof()) {
		char c = file.get();
		if (c == delimiter || c == '\r' || c == '\n') {
			if (file.peek() == '\n') file.get();
			string s = ss.str();
			s.erase(0, s.find_first_not_of(t));
			s.erase(s.find_last_not_of(t) + 1);
			row.push_back(s);
			ss.str("");
			if (c != delimiter) break;
		}
		else {
			ss << c;
		}
	}
	return row;
}