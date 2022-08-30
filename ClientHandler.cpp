#include "ClientHandler.h"
#include <Windows.h>
#include <iostream>


void ClientHandler::ShowMenu() const
{
	//system("cls");
	cout << "\n-----Menu------" << endl;
	cout << "1. �ű� �� ���" << endl;
	cout << "2. �� ���� ��ȸ" << endl;
	cout << "3. �� ���� ����" << endl;
	cout << "4. ó������" << endl;
}

void ClientHandler::AddClient()
{
	string name;
	string phoneNumber;
	string address;
	string email;

	cout << "\n[�ű� �� ���]" << endl;
	cout << "�̸�: ";		cin >> name;
	cout << "��ȭ��ȣ: ";	cin >> phoneNumber;
	cout << "�ּ�: ";		cin.ignore();	getline(cin, address);
	cout << "�̸����ּ�: ";	cin >> email;

	int id = MakeId();
	Client* newClient = new Client(id, name, phoneNumber, address, email);
	clientList.insert({ id, newClient });
	cout << "\n�ű� �� ��� �Ϸ�!" << endl;
	cout << "����ȣ�� " << id << "�Դϴ�.\n" << endl;
}

void ClientHandler::DeleteClient(int id)
{
	delete clientList.at(id);
	clientList.erase(id);
}

void ClientHandler::ShowAllAccInfo() const
{
	for (auto i = clientList.begin(); i != clientList.end(); i++)
	{
		i->second->ShowCltInfo();
	}
	cout << "\n>> �� " << clientList.size() << "���� ��\n" << endl;
}

void ClientHandler::SearchClient() const
{
	int sel;
	cout << "\n-----�� ��ȸ(����, ����)------" << endl;
	cout << "1. ��ID�� ��ȸ" << endl;
	cout << "2. �̸����� ��ȸ" << endl;
	cout << "3. ��ü �� ��ȸ" << endl;
	cout << "4. ���� �޴�" << endl;
	cout << "����: ";	cin >> sel;

	if (sel == 1)
		SearchUsingId();
	else if (sel == 2)
		SearchUsingName();
	else if (sel == 3)
		ShowAllAccInfo();
	else if (sel == 4)
		;
	else
		cout << "�߸��� �Է��Դϴ�." << endl;
}

void ClientHandler::ShowSearchResult(vector<Client*> searchResults) const
{
	cout << '\n';
	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		(*i)->ShowCltInfo();
		cout << '\n';
	}
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
}

vector<Client*> ClientHandler::SearchUsingId() const
{
	int id;
	vector<Client*> searchResults;

	cout << "\n��ID�� �Է��Ͻÿ�: ";	cin >> id;

	//cout << "at: " << clientList.at(5) << endl;

	for (auto i = clientList.begin(); i != clientList.end(); i++)
		if (id == i->first)
			searchResults.push_back(i->second);

	ShowSearchResult(searchResults);
	return searchResults;
}

vector<Client*> ClientHandler::SearchUsingName() const
{
	string name;
	vector<Client*> searchResults;

	cout << "\n�� �̸��� �Է��Ͻÿ�: "; cin >> name;

	for (auto i = clientList.begin(); i != clientList.end(); i++)
	{
		if (name == i->second->GetCltName())
			searchResults.push_back(i->second);
	}
	ShowSearchResult(searchResults);
	return searchResults;
}

int ClientHandler::MakeId()
{
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