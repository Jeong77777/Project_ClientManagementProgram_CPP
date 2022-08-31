#include "ClientHandler.h"
#include "Line.h"
#include <Windows.h>
#include <iostream>


void ClientHandler::ShowMenu() const
{
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
	string name;
	string phoneNumber;
	string address;

	cout << LINE80 << endl;
	cout << "\t\t\t\t�ű� �� ���" << endl;
	cout << LINE80 << endl;
	cout << "�̸�: ";		cin >> name;
	cout << "��ȭ��ȣ: ";	cin >> phoneNumber;
	cout << "�ּ�: ";		cin.ignore();	getline(cin, address);

	int id = MakeId();
	Client* newClient = new Client(id, name, phoneNumber, address);
	clientList.insert({ id, newClient });
	cout << "\n�ű� �� ��� �Ϸ�!" << endl;
	cout << "����ȣ�� " << id << "�Դϴ�.\n" << endl;
	cout << "�޴��� ���ư����� �ƹ�Ű�� �Է��ϼ���: " << endl;
	system("pause");
	system("cls");
}

void ClientHandler::SearchClientMenu()
{
	int sel;
	cout << LINE80 << endl;
	cout << "\t\t\t\t�� ��ȸ(����, ����)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ID�� ��ȸ" << endl;
	cout << "\t\t\t\t2.  �̸����� ��ȸ" << endl;
	cout << "\t\t\t\t3.  ��ü �� ��ȸ" << endl;
	cout << "\t\t\t\t4.  ���� �޴�" << endl;
	cout << LINE80 << endl;


	cout << "�޴��� �����ϼ���: ";	cin >> sel;
	if (sel == 1)
		SearchCltUsingIdMenu();
	else if (sel == 2)
		SearchCltUsingNameMenu();
	else if (sel == 3)
		ShowAllAccInfo();
	else if (sel == 4)
	{
		system("cls");
	}
	else
		cout << "�߸��� �Է��Դϴ�." << endl;
}

void ClientHandler::SearchCltUsingIdMenu()
{
	int id;
	Client* client;
	cout << "��ID�� �Է��ϼ���: ";
	cin >> id;
	client = SearchCltUsingId(id);
	ShowSearchResult(client);

	if (client != nullptr)
		ClientDeleteModifyMenu(client);
	else
		system("pause");

	system("cls");
}

void ClientHandler::ClientDeleteModifyMenu(Client* client)
{
	int sel;
	cout << LINE80 << endl;
	cout << "1. ����\t\t2. ����" << endl;
	cout << LINE80 << endl;
	cout << "�޴��� �����ϼ���: ";
	cin >> sel;

	if (sel == 1)
	{
		DeleteCltUsingPtr(client);
	}
	else if (sel == 2)
	{
		ModifyClientMenu(client);
	}
	else
		cout << "�߸��� �Է��Դϴ�. " << endl;
}

void ClientHandler::ModifyClientMenu(Client* client)
{
	int sel;
	cout << LINE80 << endl;
	cout << "1. �̸�\t\t2. ��ȭ��ȣ\t\t3.�ּ�" << endl;
	cout << LINE80 << endl;
	cout << "������ �׸��� �����ϼ���: ";	cin >> sel;
	cout << LINE80 << endl;
	if (sel == 1)
	{
		string name;
		cout << "�̸��� �Է��ϼ���: ";
		cin >> name;
		client->SetCltName(name);
	}
	else if (sel == 2)
	{
		string phone;
		cout << "��ȭ��ȣ�� �Է��ϼ���: ";
		cin >> phone;
		client->SetCltPhoneNumber(phone);
	}
	else if (sel == 3)
	{
		string address;
		cout << "�ּҸ� �Է��ϼ���: ";
		cin >> address;
		client->SetCltAddress(address);
	}
	else
		cout << "�߸��� �Է��Դϴ�." << endl;
}


void ClientHandler::SearchCltUsingNameMenu()
{
	string name;
	vector<Client*> searchResults;
	cout << "�� �̸��� �Է��ϼ���: "; cin >> name;

	searchResults = SearchCltUsingName(name);
	ShowSearchResults(searchResults);

	if (searchResults.size() != 0)
	{
		unsigned int sel;
		cout << "���� �Ǵ� ������ �׸��� �����ϼ���: # ";
		cin >> sel;
		if (sel >= 1 && sel <= searchResults.size())
			ClientDeleteModifyMenu(searchResults[sel-1]);
		else
			cout << "�߸��� �Է��Դϴ�." << endl;		
	}
	else
		system("pause");

	system("cls");
}


void ClientHandler::DeleteCltUsingPtr(Client* client)
{
	int id = client->getCltId();
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



Client* ClientHandler::SearchCltUsingId(int id) const
{
	auto i = clientList.find(id);

	if (i != clientList.end())
	{
		return i->second;
	}
	else
	{		
		return nullptr;
	}	
}

vector<Client*> ClientHandler::SearchCltUsingName(string name) const
{
	vector<Client*> searchResults;	

	for (auto i = clientList.begin(); i != clientList.end(); i++)
	{
		if (name == i->second->GetCltName())
			searchResults.push_back(i->second);
	}
	
	return searchResults;
}

void ClientHandler::ShowSearchResult(Client* client) const
{
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE80 << '\n' << endl;
	if (client != nullptr)
	{
		client->ShowCltInfo();
		cout << endl;
	}		
	else
	{
		cout << "�������� �ʴ� ��ID�Դϴ�.\n" << endl;
	}	
}

void ClientHandler::ShowSearchResults(vector<Client*> searchResults) const
{
	int idx = 1;
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE80 << '\n' << endl;
	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		cout << "# " << idx << endl;
		(*i)->ShowCltInfo();
		cout << '\n';
		idx++;
	}
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE80 << '\n' << endl;
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