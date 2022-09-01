#include "ClientHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>


void ClientHandler::ShowMenu() const
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

	/*** �ű� �� ��� �޴� ��� ***/
	/*** �ű� �� ���� �Է� �ޱ� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t�ű� �� ���" << endl;
	cout << LINE80 << endl;
	cout << "�̸�: ";		cin >> name;
	cout << "��ȭ��ȣ: ";	cin >> phoneNumber;
	cout << "�ּ�: ";		cin.ignore();	getline(cin, address);

	/*** ID ���� �� �ű� �� ��� ***/
	int id = MakeId();
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
	sel = GetInt::GetIntger(1, 4);

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
	id = GetInt::GetIntger();
	client = SearchCltUsingId(id);
	ShowSearchResult(client);

	/*** ����/���� �޴� ***/
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
	sel = GetInt::GetIntger(1, 3);

	if (sel == 1) {
		DeleteCltUsingPtr(client);
		cout << "���� �Ϸ�!\n" << endl;
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
	/*** �� ���� �޴� ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. �̸�\t\t2. ��ȭ��ȣ\t\t3. �ּ�\t\t4. ������" << endl;
	cout << LINE80 << endl;
	cout << "������ �׸��� �����ϼ���: ";
	sel = GetInt::GetIntger(1, 4);

	cout << LINE80 << endl;
	if (sel == 1) {
		string name;
		cout << "�̸��� �Է��ϼ���: ";
		cin >> name;
		client->SetCltName(name);
	} 
	else if (sel == 2) {
		string phone;
		cout << "��ȭ��ȣ�� �Է��ϼ���: ";
		cin >> phone;
		client->SetCltPhoneNumber(phone);
	} 
	else if (sel == 3) {
		string address;
		cout << "�ּҸ� �Է��ϼ���: ";
		cin >> address;
		client->SetCltAddress(address);
	}
	else {
		system("cls");
		return;
	}
	
	cout << "���� �Ϸ�!\n" << endl;
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
	ShowSearchResults(searchResults);

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(searchResults);
}


void ClientHandler::DeleteCltUsingPtr(Client* client)
{
	/*** �� ���� ***/
	int id = client->getCltId();
	delete clientList.at(id);
	clientList.erase(id);
}

void ClientHandler::ShowAllCltInfoMenu()
{
	/*** ��ü �� ��ȸ �޴� ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ü �� ��ȸ" << endl;
	cout << LINE80 << endl;
	cout << setw(10) << left << "��ȣ";
	cout << setw(8) << left << "��ID";
	cout << setw(10) << left << "�̸�";
	cout << setw(20) << left << "��ȭ��ȣ";
	cout << setw(30) << left << "�ּ�" << endl;
	cout << LINE80 << endl;
	ShowAllCltInfo();
	cout << LINE80 << endl;

	/*** ��ü �� �������� ***/
	vector<Client*> allClients;
	for (auto i = clientList.begin(); i != clientList.end(); i++)
		allClients.push_back(i->second);

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(allClients);
}

void ClientHandler::SelectInSearchMenu(vector<Client*>& list)
{
	/*** �˻� ��Ͽ��� �����ϱ� ***/
	int sel;
	if (list.size() != 0) {
		cout << "���� �Ǵ� ������ �׸��� �����ϼ���(������ 0): # ";
		sel = GetInt::GetIntger(0, list.size());
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

void ClientHandler::ShowAllCltInfo() const
{
	/*** ��ü �� ��� ***/
	int cnt = 1;
	for (auto i = clientList.begin(); i != clientList.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		i->second->ShowCltInfo();
		cout << '\n';
		cnt++;
	}
	cout << "\n>> �� " << clientList.size() << "���� ��\n" << endl;
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
		if (name == i->second->GetCltName())
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
	cout << std::setw(8) << left << "��ID";
	cout << std::setw(10) << left << "�̸�";
	cout << std::setw(20) << left << "��ȭ��ȣ";
	cout << std::setw(30) << left << "�ּ�" << endl;
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
	/*** �̸����� �˻��� ����� ��� ***/
	int cnt = 1;
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
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
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE80 << endl;
}

int ClientHandler::MakeId()
{
	/*** �ߺ����� �ʴ� ID ���� ***/
	auto key = clientList.end();
	if (clientList.size() == 0)
	{
		return 1001;
	}
	else
	{
		int id = (--key)->first;
		return ++id;
	}
}