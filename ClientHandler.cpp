#include "ClientHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

ClientHandler::ClientHandler()
{
	ifstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = stoi(row[0]);
				Client* c = new Client(id, row[1], row[2], row[3]);
				clientList.insert({ id, c });
			}
		}
	}
	file.close();
}

ClientHandler::~ClientHandler()
{
	ofstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		for (const auto& v : clientList) {
			Client* c = v.second;
			file << c->getCltID() << ", " << c->GetCltName() << ", ";
			file << c->GetCltPhoneNumber() << ", ";
			file << c->GetCltAddress() << endl;
			delete c;
		}
	}
	file.close();
}


void ClientHandler::ShowClientMenu() const
{
	/*** �� ���� ���� �޴� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t�� ���� ����" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  �ű� �� ���" << endl;
	cout << "\t\t\t\t2.  �� ��ȸ(����, ����)" << endl;
	cout << "\t\t\t\t3.  ó������" << endl;
	cout << LINE80 << endl;
}

void ClientHandler::AddClientMenu()
{
	/*** �ű� �� ��� �޴� ***/
	string name;
	string phoneNumber;
	string address;

	/*** �ű� �� ���� �Է� �ޱ� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t�ű� �� ���" << endl;
	cout << LINE80 << endl;
	cout << "�̸��� �Է��ϼ���: ";		cin >> name;
	phoneNumber = GetPhoneNumber();
	cout << "�ּҸ� �Է��ϼ���: ";		cin.ignore();	getline(cin, address);

	/*** ID ���� �� �ű� �� ��� ***/
	int id = MakeClientId();
	Client* newClient = new Client(id, name, phoneNumber, address);
	clientList.insert({ id, newClient });
	cout << "\n�ű� �� ��� �Ϸ�!" << endl;
	cout << "����ȣ�� " << id << "�Դϴ�.\n" << endl;

	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}

void ClientHandler::SearchClientMenu()
{
	int sel;

	/*** �� ��ȸ �޴� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t�� ��ȸ(����, ����)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ID�� ��ȸ" << endl;
	cout << "\t\t\t\t2.  �̸����� ��ȸ" << endl;
	cout << "\t\t\t\t3.  ��ü �� ��ȸ" << endl;
	cout << "\t\t\t\t4.  ���� �޴�" << endl;
	cout << LINE80 << endl;

	/*** �� ��ȸ �޴� ���� ***/
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 4);

	if (sel == 1)
		SearchCltUsingIdMenu();
	else if (sel == 2)
		SearchCltUsingNameMenu();
	else if (sel == 3)
		ShowAllCltInfoMenu();
	else if (sel == 4)
		system("cls");
}

void ClientHandler::SearchCltUsingIdMenu()
{
	/*** ��ID�� �˻� ***/
	int id;
	Client* client;
	cout << "��ID�� �Է��ϼ���: ";
	id = GetInt::GetInteger();
	client = SearchCltUsingId(id);
	ShowSearchResult(client);

	/*** ����/���� �޴� ȣ�� ***/
	if (client != nullptr)
		ClientDeleteModifyMenu(client);
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}

void ClientHandler::ClientDeleteModifyMenu(Client* client)
{
	/*** ����/���� �޴� ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. ����\t\t2. ����\t\t3. ������" << endl;
	cout << LINE80 << endl;
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) {
		DeleteCltUsingPtr(client);
		cout << "\n���� �Ϸ�!\n" << endl;
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) {
		ModifyClientMenu(client);
	}
	else;
}

void ClientHandler::ModifyClientMenu(Client* client)
{
	/*** �� ���� ���� �޴� ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. �̸�\t\t2. ��ȭ��ȣ\t\t3. �ּ�\t\t4. ������" << endl;
	cout << LINE80 << endl;
	cout << "������ �׸��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 4);

	cout << LINE80 << endl;
	if (sel == 1) {
		string name;
		cout << "�̸��� �Է��ϼ���: ";
		cin >> name;
		client->SetCltName(name);
	}
	else if (sel == 2) {
		string phone;
		phone = GetPhoneNumber();
		client->SetCltPhoneNumber(phone);
	}
	else if (sel == 3) {
		string address;
		cout << "�ּҸ� �Է��ϼ���: ";		cin.ignore();	getline(cin, address);
		client->SetCltAddress(address);
	}
	else
		return;
	
	
	cout << "\n���� �Ϸ�!\n" << endl;
	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();
}

void ClientHandler::SearchCltUsingNameMenu()
{
	/*** �̸����� ��ȸ �޴� ***/
	string name;
	vector<Client*> searchResults;

	cout << "�� �̸��� �Է��ϼ���: "; cin >> name;

	/*** �˻� ��� �������� ***/
	searchResults = SearchCltUsingName(name);

	/*** �˻� ��� ��� ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE80 << endl;

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(searchResults);
}

void ClientHandler::DeleteCltUsingPtr(Client* client)
{
	/*** �� ���� ***/
	int id = client->getCltID();
	delete clientList.at(id);
	clientList.erase(id);
}

void ClientHandler::ShowAllCltInfoMenu()
{
	/*** ��ü �� ��ȸ �޴� ***/

	/*** ��ü �� ������� �������� ***/
	vector<Client*> allClients;
	for (auto i = clientList.begin(); i != clientList.end(); i++)
		allClients.push_back(i->second);

	/*** ��ü �� ���� ��� ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ü �� ��ȸ" << endl;
	ShowSearchResults(allClients);
	cout << "\n>> �� " << allClients.size() << "���� ��\n" << endl;
	cout << LINE80 << endl;	

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(allClients);
}

void ClientHandler::SelectInSearchMenu(vector<Client*>& list)
{
	/*** �˻� ��Ͽ��� �����ϱ� ***/
	int sel;
	if (list.size() != 0) {
		cout << "���� �Ǵ� ������ �׸��� �����ϼ���(������ 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/*** ����/���� �޴� ���� ***/
			ClientDeleteModifyMenu(list[sel - 1]);			
	}
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}

Client* ClientHandler::SearchCltUsingId(int id) const
{
	/*** ��ID�� �˻� ***/
	auto i = clientList.find(id);

	if (i != clientList.end())
		return i->second;
	else
		return nullptr;
}

vector<Client*> ClientHandler::SearchCltUsingName(string name) const
{
	/*** �̸����� �˻� ***/
	vector<Client*> searchResults;	

	for (auto i = clientList.begin(); i != clientList.end(); i++) {
		if(i->second->GetCltName().find(name) != -1)
			searchResults.push_back(i->second);
	}
	
	return searchResults;
}

void ClientHandler::ShowSearchResult(Client* client) const
{
	/*** ID�� �˻��� ��� ��� ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE80 << endl;
	cout << setw(8) << left << "��ID";
	cout << setw(10) << left << "�̸�";
	cout << setw(20) << left << "��ȭ��ȣ";
	cout << setw(30) << left << "�ּ�" << endl;
	cout << LINE80 << endl;

	if (client != nullptr) {
		client->ShowCltInfo();
		cout << endl;
	}		
	else {
		cout << "\n�������� �ʴ� ��ID�Դϴ�.\n" << endl;
	}	
}

void ClientHandler::ShowSearchResults(vector<Client*>& searchResults) const
{
	/*** �˻��� ����� ��� ***/
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

int ClientHandler::MakeClientId()
{
	/*** �ߺ����� �ʴ� ID ���� ***/
	auto key = clientList.end();
	if (clientList.size() == 0) {
		return 1001;
	}
	else {
		int id = (--key)->first;
		return ++id;
	}
}

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

string ClientHandler::GetPhoneNumber()
{
	/*** �ùٸ� ��ȭ��ȣ �Է¹ޱ� ***/
	string phoneNum;

	cout << "��ȭ��ȣ�� �Է��ϼ���(ex 010-XXXX-XXXX): ";
	while (1) {
		cin >> phoneNum;
		if (IsValidPhoneNumber(phoneNum))
			return phoneNum;
		else
			cout << "�ùٸ��� ���� ��ȭ��ȣ�Դϴ�. �ٽ� �Է��ϼ���: ";
	}
}

bool ClientHandler::IsValidPhoneNumber(string phoneNumber)
{
	/*** �ùٸ� ��ȭ��ȣ���� �˻� ***/
	string num[3];
	int dash1, dash2;

	dash1 = phoneNumber.find("-");
	dash2 = phoneNumber.find("-", dash1 + 1);

	num[0] = phoneNumber.substr(0, dash1);
	num[1] = phoneNumber.substr(dash1 + 1, dash2 - dash1 - 1);
	num[2] = phoneNumber.substr(dash2 + 1, phoneNumber.size() - dash2 - 1);

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

	for (int i = 1; i < 3; i++)
		if (false == !num[i].empty() && num[i].find_first_not_of("0123456789") == string::npos)
			return false;

	return true;
}