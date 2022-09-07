#include "OrderHandler.h"
#include "GetInteger.h"
#include "Line.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>


/**
* @brief orderlist.txt ������ ��� ����� ��ǰ ����Ʈ�� ������ /
*       �� ���� ���� ��ü, ��ǰ ���� ���� ��ü�� ���������� ������
*/
OrderHandler::OrderHandler(ClientHandler& cltRef, ProductHandler& prodRef)
	:cltHandler(cltRef), prodHandler(prodRef)
{
	ifstream file;
	file.open("orderlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int num = stoi(row[0]); // ��ǰ��ȣ
				int cltID = stoi(row[2]); // ��ID
				int prodID = stoi(row[3]); // ��ǰID
				int prodNum = stoi(row[4]); // ������
				// (��ǰ��ȣ, �ֹ�����, ��ID, ��ǰID, ������)
				Order* o = new Order(num, row[1], cltID, prodID, prodNum);
				orderList.insert({ num, o });
			}
		}
	}
	file.close();
}


/**
* @brief ��ǰ ����Ʈ�� orderlist.txt�� ����
*/
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
			delete o; // �޸� �Ҵ��� ����
		}
	}
	file.close();
}


/**
* @brief �ֹ� ���� ���� �޴��� ���
*/
void OrderHandler::ShowOrderMenu() const
{
	/* �ֹ� ���� ���� �޴� ��� */
	cout << LINE80 << endl;
	cout << "\t\t\t\t�ֹ� ���� ����" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  �ֹ� ���� ���" << endl;
	cout << "\t\t\t\t2.  �ֹ� ���� ��ȸ(����, ����)" << endl;
	cout << "\t\t\t\t3.  ó������" << endl;
	cout << LINE80 << endl;
}


/**
* @brief �ֹ� ���� ��� �޴�
*/
void OrderHandler::AddOrderMenu()
{
	/* �ֹ� ���� �Է� �ޱ� */
	try {
		cout << LINE80 << endl;
		cout << "\t\t\t\t�ֹ� ���� ���" << endl;
		cout << LINE80 << endl;
		cout << "�����÷��� -1�� �Է��ϼ���.\n" << endl;

		string date = GetDateString(); // �ֹ�����
		int cltID = GetCltID(); // ��ID
		int prodID = GetProdID(); // ��ǰID
		int prodNum = GetProdNum(prodID); // �ֹ�����

		/* �ֹ���ȣ ���� ���� */
		int num = MakeOrderNum(); // 

		/* orderList�� �ֹ� �߰� */
		Order* newOrder = new Order(num, date, cltID, prodID, prodNum);
		orderList.insert({ num, newOrder });
		cout << "\n�ֹ� ���� ��� �Ϸ�!" << endl;
		cout << "�ֹ���ȣ�� " << num << "�Դϴ�.\n" << endl;
	}
	catch (int cancel) {// -1�� �Է��ϸ� ����� ����Ѵ�.
		if (cancel == -1)
			cout << "\n����� ����մϴ�.\n" << endl;
	}	

	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}


/**
* @brief �ֹ� ���� ��ȸ(����, ����) �޴� ���
*/
void OrderHandler::SearchOrderMenu()
{
	/* �ֹ� ���� ��ȸ �޴� ��� */
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

	/* �ֹ� ���� ��ȸ �޴� ���� */
	cout << "�޴��� �����ϼ���: ";
	int sel = GetInt::GetInteger(1, 6);

	if (sel == 1) // �ֹ���ȣ�� ��ȸ
		SearchOrderUsingNumMenu();
	else if (sel == 2) // ��ID�� ��ȸ
		SearchOrderUsingCltIdMenu();
	else if (sel == 3) // ��ǰID�� ��ȸ
		SearchOrderUsingProdIdMenu();
	else if (sel == 4) // �ֹ����ں� ��ȸ
		SearchOrderUsingDateMenu();
	else if (sel == 5) // ��ü �ֹ� ���� ��ȸ
		ShowAllOrderInfoMenu();
	else // ���� �޴�
		system("cls");
}


/**
* @brief �ֹ���ȣ�� ��ȸ �޴�
*/
void OrderHandler::SearchOrderUsingNumMenu()
{
	/* �˻��� �ֹ���ȣ �Է� �ޱ� */
	cout << "�ֹ���ȣ�� �Է��ϼ���(������ -1): ";
	int num = GetInt::GetInteger();
	if (num == -1) {
		system("cls");
		return;
	}

	/* �ֹ���ȣ�� �̿��Ͽ� �˻��ϰ� ��� �������� */
	Order* order = SearchOrderUsingNum(num);

	/* �˻��� �ֹ� ���� ��� */
	ShowSearchResult(order);

	/* ����/���� �޴� ȣ�� */
	if (order != nullptr)
		OrderDeleteModifyMenu(order);
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}


/**
* @brief ��ID�� ��ȸ �޴�
*/
void OrderHandler::SearchOrderUsingCltIdMenu()
{	
	try {
		/* �˻��� ��ID �Է� �ޱ� */
		cout << "�����÷��� -1�� �Է��ϼ���." << endl;
		int cltID = GetCltID();

		/* �˻� ��� �������� */
		vector<Order*> searchResults = SearchOrderUsingCltId(cltID);

		/* �˻� ��� ��� */
		system("cls");
		cout << LINE90 << endl;
		cout << "\t\t\t\t�˻� ���" << endl;
		ShowSearchResults(searchResults);
		cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
		cout << LINE90 << endl;

		/* ����/������ ���� ���� �޴� ȣ�� */
		SelectInSearchMenu(searchResults);
	}
	catch (int cancel) { // -1�̸� �˻� ���
		if (cancel == -1) {
			system("cls");
			return;
		}
	}
}


/**
* @brief ��ǰID�� ��ȸ �޴�
*/
void OrderHandler::SearchOrderUsingProdIdMenu()
{
	try {
		/* �˻��� ��ǰID �Է� �ޱ� */
		cout << "�����÷��� -1�� �Է��ϼ���." << endl;
		int prodID = GetProdID();

		/* �˻� ��� �������� */
		vector<Order*>searchResults = SearchOrderUsingProdId(prodID);

		/* �˻� ��� ��� */
		system("cls");
		cout << LINE90 << endl;
		cout << "\t\t\t\t�˻� ���" << endl;
		ShowSearchResults(searchResults);
		cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
		cout << LINE90 << endl;

		/* ����/������ ���� ���� �޴� ȣ�� */
		SelectInSearchMenu(searchResults);
	}
	catch (int cancel) { // -1�̸� �˻� ���
		if (cancel == -1) {
			system("cls");
			return;
		}
	}
}


/**
* @brief �ֹ����ں� ��ȸ �޴�
*/
void OrderHandler::SearchOrderUsingDateMenu()
{
	try {
		/* �˻��� �ֹ����� �Է� �ޱ� */
		cout << "�����÷��� -1�� �Է��ϼ���." << endl;
		string date = GetDateString();

		/* �˻� ��� �������� */
		vector<Order*>searchResults = SearchOrderUsingDate(date);

		/* �˻� ��� ��� */
		system("cls");
		cout << LINE90 << endl;
		cout << "\t\t\t\t�˻� ���" << endl;
		ShowSearchResults(searchResults);
		cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
		cout << LINE90 << endl;

		/* ����/������ ���� ���� �޴� ȣ�� */
		SelectInSearchMenu(searchResults);
	}
	catch (int cancel) { // -1�̸� �˻� ���
		if (cancel == -1) {
			system("cls");
			return;
		}
	}
}


/**
* @brief ��ü �ֹ� ���� ��ȸ �޴�
*/
void OrderHandler::ShowAllOrderInfoMenu()
{
	/* ��ü �ֹ� ���� ������� �������� */
	vector<Order*> allOrders;
	for (auto i = orderList.begin(); i != orderList.end(); i++)
		allOrders.push_back(i->second);

	/* ��ü �ֹ� ���� ��� */
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t��ü �ֹ� ���� ��ȸ" << endl;
	ShowSearchResults(allOrders);
	cout << "\n>> �� " << allOrders.size() << "���� �ֹ� ����\n" << endl;
	cout << LINE90 << endl;

	/* ����/������ ���� ���� �޴� ȣ�� */
	SelectInSearchMenu(allOrders);
}


/**
* @brief ��ȸ�� �ֹ� ���� ����Ʈ���� �ֹ� ������ ����
* @param vector<Order*>& list ��ȸ�� �ֹ� ���� ����Ʈ
*/
void OrderHandler::SelectInSearchMenu(vector<Order*>& list)
{
	/* ��ȸ�� �ֹ� ���� ����Ʈ���� �ֹ� ������ ���� */
	int sel;
	if (list.size() != 0) {
		cout << "���� �Ǵ� ������ �׸��� �����ϼ���(������ 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/* ����/���� �޴� ȣ�� */
			OrderDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}


/**
* @brief �ֹ� ���� ����/���� �޴�
* @param Order* order ����/������ �ֹ� ����
*/
void OrderHandler::OrderDeleteModifyMenu(Order* order)
{
	/* ����/����/������ �߿� ���� */
	int sel;
	cout << LINE90 << endl;
	cout << "1. ����\t\t2. ����\t\t3. ������" << endl;
	cout << LINE90 << endl;
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) { // ����
		Product* product = prodHandler.SearchProdUsingId(order->GetOrderProdID());
		string input;

		if (product != nullptr) { // ������ �ֹ������� ��ǰ ������ �ִٸ�
			cout << "������ �ֹ������� ���� ��ǰ��� �ٽ� �߰��Ͻðڽ��ϱ�?(y/n): ";
			while (1) {
				cin >> input;
				if (input == "y" || input == "Y") {
					product->SetProdStock(product->GetProdStock() + order->GetOrderProdNum());
					break;
				}
				else if (input == "n" || input == "N")
					break;
				else
					cout << "�ٽ� �Է��ϼ���: ";
			}
		}

		DeleteOrderUsingPtr(order);
		cout << "\n���� �Ϸ�!\n" << endl;
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) { // ����
		ModifyOrderMenu(order);
	}
	else; // ������
}


/**
* @brief �ֹ� ���� ���� �޴�
* @param Order* order ������ �ֹ� ����
*/
void OrderHandler::ModifyOrderMenu(Order* order)
{
	/* �ֹ� ���� ���� ���� */
	cout << LINE90 << endl;
	cout << "1. �ֹ�����       2. ��ID       3. ��ǰID       4. �ֹ�����       5. ������" << endl;
	cout << LINE90 << endl;
	cout << "������ �׸��� �����ϼ���: ";
	int sel = GetInt::GetInteger(1, 5);

	cout << LINE90 << endl;
	try {
		if (sel == 1 || sel == 2 || sel == 3 || sel == 4) {
			cout << "�����÷��� -1�� �Է��ϼ���." << endl;
			if (sel == 1) { // �ֹ����� ����
				string date;
				date = GetDateString();
				order->SetOrderDate(date);
			}
			else if (sel == 2) { // ��ID ����
				int cltID;
				cltID = GetCltID();
				order->SetOrderCltID(cltID);
			}
			else if (sel == 3) { // ��ǰID ����
				ChangeProdID(order);
			}
			else if (sel == 4) { // �ֹ����� ����
				ChangeProdNum(order);
			}
		}
		else // ������
			return;

		cout << "\n���� �Ϸ�!\n" << endl;
	}
	catch (int cancel) {// -1�̸� ���� ���
		if (cancel == -1)
			cout << "\n������ ����մϴ�.\n" << endl;
	}
	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();
}


/**
* @brief �ֹ���ȣ�� �̿��� �ֹ� ���� �˻�
* @param int num �˻��� �ֹ���ȣ
* @return Order* �˻��� �ֹ� ���� ��ȯ
*/
Order* OrderHandler::SearchOrderUsingNum(int num) const
{
	/* �ֹ���ȣ�� �̿��� �ֹ� ���� �˻� */
	auto i = orderList.find(num);

	if (i != orderList.end()) // �˻� ����� ������ ��
		return i->second;
	else // �˻� ����� �������� ���� ��
		return nullptr;
}


/**
* @brief ��ID�� �̿��� �ֹ� ���� �˻�
* @param int cltID �˻��� ��ID
* @return vector<Order*> �˻��� �ֹ� ������ ��ȯ
*/
vector<Order*> OrderHandler::SearchOrderUsingCltId(int cltID) const
{
	/* ��ID�� �̿��� �ֹ� ���� �˻� */
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (cltID == i->second->GetOrderCltID())
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief ��ǰID�� �̿��� �ֹ� ���� �˻�
* @param int prodID �˻��� ��ǰID
* @return vector<Order*> �˻��� �ֹ� ������ ��ȯ
*/
vector<Order*> OrderHandler::SearchOrderUsingProdId(int prodID) const
{
	/* ��ǰID�� �̿��� �ֹ� ���� �˻� */
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (prodID == i->second->GetOrderProdID())
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief �ֹ����ں� �ֹ� ���� �˻�
* @string date �˻��� �ֹ�����
* @return vector<Order*> �˻��� �ֹ� ������ ��ȯ
*/
vector<Order*> OrderHandler::SearchOrderUsingDate(string date) const
{
	/* �ֹ����ں� �ֹ� ���� �˻� */
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (date == i->second->GetOrderDate())
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief �ֹ���ȣ�� �˻��� ��� ���
* @param Order* order �˻��� �ֹ� ����
*/
void OrderHandler::ShowSearchResult(Order* order) const
{
	/* �ֹ���ȣ�� �˻��� ��� ��� */
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE90 << endl;
	cout << setw(16) << left << "�ֹ���ȣ";
	cout << setw(15) << left << "�ֹ�����";
	cout << setw(30) << left << "��ǰID(��ǰ��)";
	cout << setw(12) << left << "�ֹ�����";
	cout << setw(10) << left << "�ֹ��ݾ�" << endl;
	cout << setw(16) << left << "��ID(�̸�)";
	cout << setw(15) << left << "��ȭ��ȣ";
	cout << setw(30) << left << "�ּ�" << endl;
	cout << LINE90 << endl;

	if (order != nullptr) { // �˻��� ���� ������ ��
		ShowOrderInfoRow1(order);
		ShowOrderInfoRow2(order);
		cout << endl;
	}
	else { // �˻��� ���� �������� ���� ��
		cout << "\n�������� �ʴ� �ֹ���ȣ�Դϴ�.\n" << endl;
	}
}


/**
* @brief �˻��� ����� ���(��ID, ��ǰID, �ֹ����ں�, ��ü �ֹ� �������� ��ȸ)
* @param vector<Order*>& searchResults �˻��� �ֹ� ������ ����Ʈ
*/
void OrderHandler::ShowSearchResults(vector<Order*>& searchResults) const
{
	/* �˻��� ����� ��� */
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


/**
* @brief �� ���� �ֹ� ���� ��� (1��)
* @param Order* order �� ���� �ֹ� ����
*/
void OrderHandler::ShowOrderInfoRow1(Order* order) const
{
	/* �ֹ���ȣ */
	cout << setw(16) << left << order->GetOrderNum();

	/* �ֹ����� */
	cout << setw(15) << left << order->GetOrderDate();

	/* ��ǰID(��ǰ��) */
	Product* product = prodHandler.SearchProdUsingId(order->GetOrderProdID());

	if (product != nullptr) { // ��ǰ ������ ������ ��
		cout << setw(30) << left << to_string(product->GetProdID()) + \
			'(' + product->GetProdName() + ')';
	}
	else { // ��ǰ ������ �������� ���� ��
		cout << setw(30) << left << "��ǰ ���� ����";
	}

	/* �ֹ����� */
	cout << setw(12) << left << order->GetOrderProdNum();

	/* �ֹ��ݾ� */
	if (product != nullptr) { // ��ǰ ������ ������ ��
		cout << setw(10) << left << order->GetOrderProdNum() * product->GetProdPrice() << endl;
	}
	else { // ��ǰ ������ �������� ���� ��
		cout << setw(10) << left << "��ǰ ���� ����" << endl;
	}
}


/**
* @brief �� ���� �ֹ� ���� ��� (2��)
* @param Order* order �� ���� �ֹ� ����
*/
void OrderHandler::ShowOrderInfoRow2(Order* order) const
{
	/* ��ID(�̸�), ��ȭ��ȣ, �ּ� */
	Client* client = cltHandler.SearchCltUsingId(order->GetOrderCltID());

	if (client != nullptr) { // �� ������ ������ ��
		cout << setw(16) << left << to_string(client->GetCltID()) + \
			'(' + client->GetCltName() + ')';
		cout << setw(15) << left << client->GetCltPhoneNumber();
		cout << setw(30) << left << client->GetCltAddress() << endl;
	}
	else { // �� ������ �������� ���� ��
		cout << setw(16) << left << "�� ���� ����" << endl;
	}
}


/**
* @brief �ֹ� ���� ����
* @param Order* order �ֹ� ����
*/
void OrderHandler::DeleteOrderUsingPtr(Order* order)
{
	/* �ֹ� ���� ���� */
	int num = order->GetOrderNum();
	delete orderList.at(num);
	orderList.erase(num);
}


/**
* @brief �ߺ����� �ʴ� �ֹ���ȣ ����
* @return int ������ �ֹ���ȣ ��ȯ
*/
int OrderHandler::MakeOrderNum()
{
	/* �ߺ����� �ʴ� �ֹ���ȣ ���� */
	auto key = orderList.end();
	if (orderList.size() == 0) {
		// ������ ����� �ֹ������� �� ���� ���� ��
		return 10001; // �ֹ���ȣ�� 10001���� ����
	}
	else {
		// ������ ����� �ֹ������� ���� ��
		// ���� ������ �ֹ���ȣ���� +1��ŭ ū ���ڸ� ��ȯ
		int num = (--key)->first;
		return ++num;
	}
}


/**
* @brief �ùٸ� ��¥ �Է� �ޱ�
* @return string �Է� ���� ��¥ ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
string OrderHandler::GetDateString()
{
	string strDate;	// string ���ĳ�¥
	int intDate; // int ���ĳ�¥
	int day, month, year; // ��, ��, �� �и�

	cout << "�ֹ����ڸ� �Է��ϼ���(ex 20220907): ";

	while (1) {
		// ���� int������ ��¥ �Է� �ޱ�
		intDate = GetInt::GetInteger();

		if (intDate == -1)
			throw - 1; // -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����

		// ��, ��, �Ϸ� �и�
		year = intDate / 10000;
		month = (intDate - (year * 10000)) / 100;
		day = intDate % 100;

		// ��¥ ��ȿ�� �˻�
		if (CheckValidDate(year, month, day)) {
			// ��ȿ�� ��¥�̸� string������ ����
			strDate = to_string(year) + '-';
			if (month < 10) strDate += '0';
			strDate += to_string(month) + '-';
			if (day < 10) strDate += '0';
			strDate += to_string(day);
			return strDate;
		}
		else // ��ȿ���� ���� ��¥�̸�
			cout << "��ȿ���� ���� ��¥�Դϴ�. �ٽ� �Է��ϼ���: ";
	}
}


/**
* @brief ��¥ ��ȿ�� �˻�
* @param int year �Է��� ��
* @param int month �Է��� ��
* @param int day �Է��� ��
* @return bool ��ȿ�� ��¥���� true/false
*/
bool OrderHandler::CheckValidDate(int year, int month, int day)
{
	/* ��ȿ�� ��¥���� �˻� */

	/* �⵵ �˻� */
	if (year < 1900 || year>2999) // 1900~2999��
		return false;

	/* ��,�� �˻� */
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
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) { // ����
					if (day < 1 || day>29)
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


/**
* @brief ��ϵ� ��ID �Է¹ޱ�
* @return int �Է� ���� ��ID ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
int OrderHandler::GetCltID()
{
	/* ��ϵ� ��ID �Է¹ޱ� */
	int id;
	cout << "��ID�� �Է��ϼ���: ";

	while (1) {
		id = GetInt::GetInteger();

		if (id == -1)
			// -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
			throw - 1;

		if (cltHandler.SearchCltUsingId(id) != nullptr)
			// ��ϵ� ��ID�� ��
			return id;
		else
			// ��ϵ� ��ID�� �ƴ� ��
			cout << "��ϵ��� ���� ��ID�Դϴ�. �ٽ� �Է��ϼ���: ";
	}
}


/**
* @brief ��ϵ� ��ǰID �Է¹ޱ�
* @return int �Է� ���� ��ǰID ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
int OrderHandler::GetProdID()
{
	/* ��ϵ� ��ǰID �Է¹ޱ� */
	int id;
	cout << "��ǰID�� �Է��ϼ���: ";

	while (1) {
		id = GetInt::GetInteger();

		if (id == -1)
			// -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
			throw - 1;

		if (prodHandler.SearchProdUsingId(id) != nullptr)
			// ��ϵ� ��ǰID�� ��
			return id;
		else
			// ��ϵ� ��ǰID�� �ƴ� ��
			cout << "��ϵ��� ���� ��ǰID�Դϴ�. �ٽ� �Է��ϼ���: ";
	}
}


/**
* @brief �ֹ����� �Է¹ޱ�
* @return int �Է� ���� ��ǰID ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
int OrderHandler::GetProdNum(int prodID)
{		
	/* ��ǰ ���� �������� */
	Product* product = prodHandler.SearchProdUsingId(prodID);
	int stock = product->GetProdStock();

	/* �ֹ� ���� �Է� �ޱ� */
	int prodNum;
	cout << "�ֹ������� �Է��ϼ���" << "(���: " << stock << "): ";
	while (1) {
		// -1 �̻��� ���ڸ� �Է� �ޱ�
		prodNum = GetInt::GetInteger(-1, INT_MAX);

		if (prodNum == -1)
			// -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
			throw - 1;

		if (stock >= prodNum) {

			product->SetProdStock(stock - prodNum); // ��� ���� ��� �ݿ�
			return prodNum;
		}
		else // ��� ������ ��
			cout << "��� �����մϴ�. �ٽ� �Է��ϼ���" << "(���: " << stock << "): ";
	}
}


/**
* @brief ��ǰID �����ϱ�
* @param Order* order ������ �ֹ�����
*/
void OrderHandler::ChangeProdID(Order* order)
{
	/* ���� �� ��ǰID */
	int oldProdID = order->GetOrderProdID();
	/* ���� �� �ֹ����� */
	int oldProdNum = order->GetOrderProdNum();
	/* ���� �� ��ǰ ���� */
	Product* oldProduct = prodHandler.SearchProdUsingId(oldProdID);
	/* ������ ��ǰID �Է� �ޱ� */
	int newProdID = GetProdID();
	/* ������ �ֹ����� �Է� �ޱ� */
	int newProdNum = GetProdNum(newProdID);

	/* ���ο� ��ǰID�� �ֹ����� ���� */
	order->SetOrderProdID(newProdID);
	order->SetOrderProdNum(newProdNum);

	if (oldProduct == nullptr) // ���� ���� ���� ��ǰ ������ �������� �ʴٸ�
		return;
	else { // ���� ���� ���� ��ǰ ������ �����Ѵٸ�
		cout << "���� �� ��ǰ�� ���� ��� �ٽ� �߰��Ͻðڽ��ϱ�?(y/n): ";
		while (1) {
			/* y �Ǵ� n ���� */
			string input; 	cin >> input;

			if (input == "y" || input == "Y") { // ���� �� ��ǰ�� ���� ��� �ٽ� �߰�
				oldProduct->SetProdStock(oldProduct->GetProdStock() + oldProdNum);
				return;
			}
			else if (input == "n" || input == "N") // ��� �߰� ���ϱ�
				return;
			else
				cout << "�ٽ� �Է��ϼ���: ";
		}
	}
}


/**
* @brief �ֹ����� �����ϱ�
* @param Order* order ������ �ֹ�����
* @exception -1�� �ԷµǸ� �Է� �ߴ� 
*/
void OrderHandler::ChangeProdNum(Order* order)
{
	/* ���� ��ǰ ���� */
	Product* product = prodHandler.SearchProdUsingId(order->GetOrderProdID());
	/* ���� ��ǰ�� ��� �������� */
	int stock = product->GetProdStock();
	/* ���� �� �ֹ����� */
	int oldProdNum = order->GetOrderProdNum();

	/* ������ �ֹ����� �Է� �ޱ� */
	cout << "�ֹ������� �Է��ϼ���" << "(�ִ�: " << stock + oldProdNum << "): ";
	while (1) {
		// -1 �̻��� ���ڸ� �Է� �ޱ�
		int newProdNum = GetInt::GetInteger(-1, INT_MAX);

		if (newProdNum == -1)
			// -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
			throw - 1;

		if (stock + oldProdNum >= newProdNum) {  // ��� ����� ��
			// ��� ���� ��� �ݿ�
			product->SetProdStock(stock + oldProdNum - newProdNum);
			// �ֹ����� ����
			order->SetOrderProdNum(newProdNum);
			return;
		}
		else // ��� ������ ��
			cout << "��� �����մϴ�. �ٽ� �Է��ϼ���" << "(�ִ�: " << stock + oldProdNum << "): ";
	}
}


/**
* @brief CSV ���� ������ ������ �� �྿ ��������
* @param istream& file ������ ������ ����ִ� ����
* @param char delimiter ���� ����
* @return vector<string> �� ���� ��ȯ
*/
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