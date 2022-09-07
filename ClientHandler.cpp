#include "ClientHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>


/** 
* @brief clientlist.txt ������ ��� ����� �� ����Ʈ�� ������
*/
ClientHandler::ClientHandler()
{
	ifstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = stoi(row[0]);
				// (��ID, �̸�, ��ȭ��ȣ, �ּ�)
				Client* c = new Client(id, row[1], row[2], row[3]);
				clientList.insert({ id, c });
			}
		}
	}
	file.close();
}


/**
* @brief �� ����Ʈ�� clientlist.txt�� ����
*/
ClientHandler::~ClientHandler()
{
	ofstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		for (const auto& v : clientList) {
			Client* c = v.second;
			// (��ID, �̸�, ��ȭ��ȣ, �ּ�)
			file << c->GetCltID() << ", " << c->GetCltName() << ", ";
			file << c->GetCltPhoneNumber() << ", ";
			file << c->GetCltAddress() << endl;
			delete c; // �޸� �Ҵ��� ����
		}
	}
	file.close();
}


/**
* @brief �� ���� ���� �޴��� ���
*/
void ClientHandler::ShowClientMenu() const
{
	/* �� ���� ���� �޴� ��� */
	cout << LINE80 << endl;
	cout << "\t\t\t\t�� ���� ����" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  �ű� �� ���" << endl;
	cout << "\t\t\t\t2.  �� ��ȸ(����, ����)" << endl;
	cout << "\t\t\t\t3.  ó������" << endl;
	cout << LINE80 << endl;
}



/**
* @brief �ű� �� ��� �޴�
*/
void ClientHandler::AddClientMenu()
{	
	/* �ű� �� ���� �Է� �ޱ� */
	try {
		cout << LINE80 << endl;
		cout << "\t\t\t\t�ű� �� ���" << endl;
		cout << LINE80 << endl;
		cout << "�����÷��� -1�� �Է��ϼ���.\n" << endl;

		string name = GetCltName(); // �� �̸�
		string phoneNumber = GetCltPhoneNum(); // ��ȭ��ȣ
		string address = GetCltAddress(); // �ּ�

		/* ��ID ���� */
		int id = MakeClientId(); // ��ID ����

		/* clientList�� �� �߰� */
		Client* newClient = new Client(id, name, phoneNumber, address);
		clientList.insert({ id, newClient });

		cout << "\n�ű� �� ��� �Ϸ�!" << endl;
		cout << "����ȣ�� " << id << "�Դϴ�.\n" << endl;
	}
	catch(int cancel){ // -1�� �Է��ϸ� ����� ����Ѵ�.
		if (cancel == -1)
			cout << "\n����� ����մϴ�.\n" << endl;
	}	

	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}


/**
* @brief �� ��ȸ(����, ����) �޴� ���
*/
void ClientHandler::SearchClientMenu()
{
	/* �� ��ȸ �޴� ��� */
	cout << LINE80 << endl;
	cout << "\t\t\t\t�� ��ȸ(����, ����)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ID�� ��ȸ" << endl;
	cout << "\t\t\t\t2.  �̸����� ��ȸ" << endl;
	cout << "\t\t\t\t3.  ��ü �� ��ȸ" << endl;
	cout << "\t\t\t\t4.  ���� �޴�" << endl;
	cout << LINE80 << endl;

	/* �� ��ȸ �޴� ���� */
	cout << "�޴��� �����ϼ���: ";
	int sel = GetInt::GetInteger(1, 4);

	if (sel == 1) // ��ID�� ��ȸ
		SearchCltUsingIdMenu();
	else if (sel == 2) // �̸����� ��ȸ
		SearchCltUsingNameMenu();
	else if (sel == 3) // ��ü �� ��ȸ
		ShowAllCltInfoMenu();
	else if (sel == 4) // ���� �޴�
		system("cls");
}


/**
* @brief ��ID�� ��ȸ �޴�
*/
void ClientHandler::SearchCltUsingIdMenu()
{
	/* �˻��� ��ID �Է� �ޱ� */
	cout << "��ID�� �Է��ϼ���(������ -1): ";
	int id = GetInt::GetInteger();
	if (id == -1) { // -1�̸� ������
		system("cls");
		return;
	}

	/* ��ID�� �̿��Ͽ� �˻��ϰ� ��� �������� */
	Client* client = SearchCltUsingId(id);

	/* �˻��� �� ���� ��� */
	ShowSearchResult(client);

	/* ����/���� �޴� ȣ�� */
	if (client != nullptr)
		ClientDeleteModifyMenu(client);
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}


/**
* @brief �̸����� ��ȸ �޴�
*/
void ClientHandler::SearchCltUsingNameMenu()
{
	/* �˻��� ���̸� �Է� �ޱ� */
	string name;	
	cout << "�� �̸��� �Է��ϼ���(������ -1): "; cin >> name;
	if (name == "-1") { // -1�̸� ������
		system("cls");
		return;
	}

	/* �˻� ��� �������� */
	vector<Client*> searchResults = SearchCltUsingName(name);

	/* �˻� ��� ��� */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE80 << endl;

	/* ����/������ ���� ���� �޴� ȣ�� */
	SelectInSearchMenu(searchResults);
}


/**
* @brief ��ü �� ��ȸ �޴�
*/
void ClientHandler::ShowAllCltInfoMenu()
{
	/* ��ü �� ������� �������� */
	vector<Client*> allClients;
	for (auto i = clientList.begin(); i != clientList.end(); i++)
		allClients.push_back(i->second);

	/* ��ü �� ���� ��� */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ü �� ��ȸ" << endl;
	ShowSearchResults(allClients);
	cout << "\n>> �� " << allClients.size() << "���� ��\n" << endl;
	cout << LINE80 << endl;

	/* ����/������ ���� ���� �޴� ȣ�� */
	SelectInSearchMenu(allClients);
}


/**
* @brief ��ȸ�� �� ���� ����Ʈ���� �� ������ ����
* @param vector<Client*>& list ��ȸ�� �� ���� ����Ʈ
*/
void ClientHandler::SelectInSearchMenu(vector<Client*>& list)
{
	/* ��ȸ�� �� ���� ����Ʈ���� �� ������ ���� */
	int sel;
	if (list.size() != 0) {
		cout << "���� �Ǵ� ������ �׸��� �����ϼ���(������ 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/* ����/���� �޴� ȣ�� */
			ClientDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}


/**
* @brief �� ���� ����/���� �޴�
* @param Client* client ����/������ ��
*/
void ClientHandler::ClientDeleteModifyMenu(Client* client)
{
	/* ����/����/������ �߿� ���� */
	cout << LINE80 << endl;
	cout << "1. ����\t\t2. ����\t\t3. ������" << endl;
	cout << LINE80 << endl;
	cout << "�޴��� �����ϼ���: ";
	int sel = GetInt::GetInteger(1, 3);

	if (sel == 1) { // ����
		DeleteCltUsingPtr(client);
		cout << "\n���� �Ϸ�!\n" << endl;
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) { // ����
		ModifyClientMenu(client);
	}
	else; // ������
}


/**
* @brief �� ���� ���� �޴�
* @param Client* client ������ ��
*/
void ClientHandler::ModifyClientMenu(Client* client)
{
	/* ������ �� ���� ���� */
	cout << LINE80 << endl;
	cout << "1. �̸�\t\t2. ��ȭ��ȣ\t\t3. �ּ�\t\t4. ������" << endl;
	cout << LINE80 << endl;
	cout << "������ �׸��� �����ϼ���: ";
	int sel = GetInt::GetInteger(1, 4);	
	cout << LINE80 << endl;	

	try {
		if (sel == 1 || sel == 2 || sel == 3) {
			cout << "�����÷��� -1�� �Է��ϼ���." << endl;
			if (sel == 1) { // �̸� ����
				string name = GetCltName();
				client->SetCltName(name);
			}
			else if (sel == 2) { // ��ȭ��ȣ ����
				string phone = GetCltPhoneNum();
				client->SetCltPhoneNumber(phone);
			}
			else if (sel == 3) { // �ּ� ����
				string address = GetCltAddress();
				client->SetCltAddress(address);
			}
		}
		else // ������
			return;

		cout << "\n���� �Ϸ�!\n" << endl;
	}
	catch(int cancel){ // -1�̸� ���� ���
		if (cancel == -1)
			cout << "\n������ ����մϴ�.\n" << endl;
	}
	
	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();
}


/**
* @brief ��ID�� �̿��� �� �˻�
* @param int id �˻��� ��ID
* @return Clinet* �˻��� �� ��ȯ
*/
Client* ClientHandler::SearchCltUsingId(int id) const
{
	/* ��ID�� �̿��� �� �˻� */
	auto i = clientList.find(id);

	if (i != clientList.end()) // �˻� ����� ������ ��
		return i->second;
	else // �˻� ����� �������� ���� ��
		return nullptr;
}


/**
* @brief ���̸��� �̿��� �� �˻�
* @param string name �˻��� ���̸�
* @return vector<Client*> �˻��� ���� ��ȯ
*/
vector<Client*> ClientHandler::SearchCltUsingName(string name) const
{
	/* �̸��� �̿��� �� �˻� */
	vector<Client*> searchResults;

	for (auto i = clientList.begin(); i != clientList.end(); i++) {
		if (i->second->GetCltName().find(name) != -1)
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief ��ID�� �˻��� ��� ���
* @param Client* client �˻��� ��
*/
void ClientHandler::ShowSearchResult(Client* client) const
{
	/* ��ID�� �˻��� ��� ��� */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE80 << endl;
	cout << setw(8) << left << "��ID";
	cout << setw(10) << left << "�̸�";
	cout << setw(20) << left << "��ȭ��ȣ";
	cout << setw(30) << left << "�ּ�" << endl;
	cout << LINE80 << endl;

	if (client != nullptr) { // �˻��� ���� ������ ��
		client->ShowCltInfo();
		cout << endl;
	}
	else { // �˻��� ���� �������� ���� ��
		cout << "\n�������� �ʴ� ��ID�Դϴ�.\n" << endl;
	}
}


/**
* @brief �˻��� ����� ���(�̸����� ��ȸ, ��ü ������ ��ȸ)
* @param vector<Client*>& searchResults �˻��� ���� ����Ʈ
*/
void ClientHandler::ShowSearchResults(vector<Client*>& searchResults) const
{
	/* �˻��� ����� ��� */
	int cnt = 1;
	cout << LINE80 << endl;
	cout << setw(10) << left << "��ȣ";
	cout << setw(8) << left << "��ID";
	cout << setw(10) << left << "�̸�";
	cout << setw(20) << left << "��ȭ��ȣ";
	cout << setw(30) << left << "�ּ�" << endl;
	cout << LINE80 << endl;

	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		(*i)->ShowCltInfo();
		cout << '\n';
		cnt++;
	}
}


/**
* @brief �� ���� ����
* @param Client* client �� ����
*/
void ClientHandler::DeleteCltUsingPtr(Client* client)
{
	/* �� ���� ���� */
	int id = client->GetCltID();
	delete clientList.at(id);
	clientList.erase(id);
}


/**
* @brief �ߺ����� �ʴ� ��ID ����
* @return int ������ ��ID ��ȯ
*/
int ClientHandler::MakeClientId()
{
	/* �ߺ����� �ʴ� ��ID ���� */
	auto key = clientList.end();
	if (clientList.size() == 0) {
		// ������ ����� �������� �� ���� ���� ��
		return 1001; // ��ID�� 1001���� ����
	}
	else {
		// ������ ����� �������� ���� ��
		// ���� ������ ��ID���� +1��ŭ ū ���ڸ� ��ȯ
		int id = (--key)->first;
		return ++id;
	}
}


/**
* @brief �ùٸ� ��ȭ��ȣ �Է� �ޱ�
* @return string �Է� ���� ��ȭ��ȣ ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
string ClientHandler::GetCltPhoneNum()
{
	/* �ùٸ� ��ȭ��ȣ �Է¹ޱ� */
	string phoneNum;

	cout << "��ȭ��ȣ�� �Է��ϼ���(ex 010-XXXX-XXXX): ";
	while (1) {
		cin >> phoneNum;
		if (phoneNum == "-1")
			throw - 1; // -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
		else if (IsValidPhoneNum(phoneNum)) // �ùٸ� ��ȭ��ȣ ���� �˻�
			return phoneNum; 
		else
			cout << "�ùٸ��� ���� ��ȭ��ȣ�Դϴ�. �ٽ� �Է��ϼ���: ";
	}
}


/**
* @brief �̸� �Է� �ޱ�
* @return string �Է� ���� �̸� ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
string ClientHandler::GetCltName()
{
	string name;
	cout << "�̸��� �Է��ϼ���: ";
	cin.ignore();	getline(cin, name); // ������ �����Ѵ�.
	if (name == "-1")
		throw - 1; // -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
	else
		return name;
}


/**
* @brief �ּ� �Է� �ޱ�
* @return string �Է� ���� �ּ� ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
string ClientHandler::GetCltAddress()
{
	string address;
	cout << "�ּҸ� �Է��ϼ���: ";
	cin.ignore();	getline(cin, address); // ������ �����Ѵ�.
	if (address == "-1")
		throw - 1; // -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
	else
		return address;
}


/**
* @brief �ùٸ� ��ȭ��ȣ���� �˻�
* @param string phoneNumber �Է��� ��ȭ��ȣ
* @return bool �ùٸ� ��ȭ��ȣ���� true/false
*/
bool ClientHandler::IsValidPhoneNum(string phoneNumber)
{
	/* �ùٸ� ��ȭ��ȣ���� �˻� */
	string num[3];
	int dash1, dash2;

	dash1 = phoneNumber.find("-"); // ù ��° - ��ġ
	dash2 = phoneNumber.find("-", dash1 + 1); // �� ��° - ��ġ

	num[0] = phoneNumber.substr(0, dash1); // ù ��° �ڸ�(������ȣ)
	num[1] = phoneNumber.substr(dash1 + 1, dash2 - dash1 - 1); // ��� �ڸ�
	num[2] = phoneNumber.substr(dash2 + 1, phoneNumber.size() - dash2 - 1); // ������ �ڸ�

	/* �ùٸ� ������ȣ���� �˻� */
	if (num[0] != "02" && num[0] != "031"
		&& num[0] != "032" && num[0] != "033"
		&& num[0] != "041" && num[0] != "042"
		&& num[0] != "043" && num[0] != "044"
		&& num[0] != "051" && num[0] != "052"
		&& num[0] != "053" && num[0] != "054"
		&& num[0] != "055" && num[0] != "061"
		&& num[0] != "062" && num[0] != "063"
		&& num[0] != "064" && num[0] != "011"
		&& num[0] != "016" && num[0] != "017"
		&& num[0] != "018" && num[0] != "019" && num[0] != "010")
		return false;

	/* ��� �ڸ��� ������ �ڸ��� ���ڸ� �ִ��� �˻� */
	for (int i = 1; i < 3; i++)
		if (false == !num[i].empty() && num[i].find_first_not_of("0123456789") == string::npos)
			return false;

	return true;
}


/**
* @brief CSV ���� ������ ������ �� �྿ ��������
* @param istream& file ������ ������ ����ִ� ����
* @param char delimiter ���� ����
* @return vector<string> �� ���� ��ȯ
*/
vector<string> ClientHandler::parseCSV(istream& file, char delimiter)
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