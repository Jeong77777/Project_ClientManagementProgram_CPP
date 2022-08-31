#include "ClientHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>


void ClientHandler::ShowMenu() const
{
	cout << LINE80 << endl;
	cout << "\t\t\t\t고객 정보 관리" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  신규 고객 등록" << endl;
	cout << "\t\t\t\t2.  고객 조회(삭제, 변경)" << endl;
	cout << "\t\t\t\t3.  처음으로" << endl;
	cout << LINE80 << endl;
}

void ClientHandler::AddClientMenu()
{
	int sel;
	string name;
	string phoneNumber;
	string address;

	cout << LINE80 << endl;
	cout << "\t\t\t\t신규 고객 등록" << endl;
	cout << LINE80 << endl;
	cout << "이름: ";		cin >> name;
	cout << "전화번호: ";	cin >> phoneNumber;
	cout << "주소: ";		cin.ignore();	getline(cin, address);

	int id = MakeId();
	Client* newClient = new Client(id, name, phoneNumber, address);
	clientList.insert({ id, newClient });
	cout << "\n신규 고객 등록 완료!" << endl;
	cout << "고객번호는 " << id << "입니다.\n" << endl;

	cout << "메뉴로 돌아가기 (0): ";
	cin >> sel;
	while (sel != 0)
	{
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cin >> sel;
	}

	system("cls");
}

void ClientHandler::SearchClientMenu()
{
	int sel;
	cout << LINE80 << endl;
	cout << "\t\t\t\t고객 조회(삭제, 변경)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  고객ID로 조회" << endl;
	cout << "\t\t\t\t2.  이름으로 조회" << endl;
	cout << "\t\t\t\t3.  전체 고객 조회" << endl;
	cout << "\t\t\t\t4.  이전 메뉴" << endl;
	cout << LINE80 << endl;


	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetIntger(1, 4);
	if (sel == 1)
		SearchCltUsingIdMenu();
	else if (sel == 2)
		SearchCltUsingNameMenu();
	else if (sel == 3)
		ShowAllCltInfoMenu();
	else if (sel == 4)
	{
		system("cls");
	}
}

void ClientHandler::SearchCltUsingIdMenu()
{
	int id;
	Client* client;
	cout << "고객ID를 입력하세요: ";
	id = GetInt::GetIntger();
	client = SearchCltUsingId(id);
	ShowSearchResult(client);

	if (client != nullptr)
		ClientDeleteModifyMenu(client);
	else
	{
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}	

	system("cls");
}

void ClientHandler::ClientDeleteModifyMenu(Client* client)
{
	int sel;
	cout << LINE80 << endl;
	cout << "1. 삭제\t\t2. 변경\t\t3. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetIntger(1, 3);

	if (sel == 1)
	{
		DeleteCltUsingPtr(client);
		cout << "삭제 완료!" << endl;
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
		system("cls");
	}
	else if (sel == 2)
	{
		ModifyClientMenu(client);
	}
	else
	{
		system("cls");
	}
}

void ClientHandler::ModifyClientMenu(Client* client)
{
	int sel;
	cout << LINE80 << endl;
	cout << "1. 이름\t\t2. 전화번호\t\t3. 주소\t\t4. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "변경할 항목을 선택하세요: ";
	sel = GetInt::GetIntger(1, 4);

	cout << LINE80 << endl;
	if (sel == 1)
	{
		string name;
		cout << "이름을 입력하세요: ";
		cin >> name;
		client->SetCltName(name);
	}
	else if (sel == 2)
	{
		string phone;
		cout << "전화번호를 입력하세요: ";
		cin >> phone;
		client->SetCltPhoneNumber(phone);
	}
	else if (sel == 3)
	{
		string address;
		cout << "주소를 입력하세요: ";
		cin >> address;
		client->SetCltAddress(address);
	}
	else
		system("cls");
}


void ClientHandler::SearchCltUsingNameMenu()
{
	string name;
	vector<Client*> searchResults;
	cout << "고객 이름을 입력하세요: "; cin >> name;

	searchResults = SearchCltUsingName(name);
	ShowSearchResults(searchResults);

	int sel;
	if (searchResults.size() != 0)
	{		
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetIntger(0, searchResults.size());
		if (sel == 0)
		{
			system("cls");
		}			
		else
		{
			ClientDeleteModifyMenu(searchResults[sel - 1]);
		}			
	}
	else
	{
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
		system("cls");
	}
}


void ClientHandler::DeleteCltUsingPtr(Client* client)
{
	int id = client->getCltId();
	delete clientList.at(id);
	clientList.erase(id);
}

void ClientHandler::ShowAllCltInfoMenu()
{
	system("cls");

	cout << LINE80 << endl;
	cout << "\t\t\t\t전체 고객 조회" << endl;
	cout << LINE80 << endl;
	cout << setw(5) << left << "번호";
	cout << setw(8) << left << "고객ID";
	cout << setw(10) << left << "이름";
	cout << setw(20) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
	cout << LINE80 << endl;
	ShowAllCltInfo();
	cout << LINE80 << endl;

	int sel;
	if (clientList.size() != 0)
	{
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetIntger(0, clientList.size());
		if (sel == 0)
		{
			system("cls");
		}			
		else
		{
			ClientDeleteModifyMenu(clientList.begin() + sel - 1);
		}		
	}
	else
	{
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
		system("cls");
	}	
}

void ClientHandler::ShowAllCltInfo() const
{
	int cnt = 1;
	for (auto i = clientList.begin(); i != clientList.end(); i++)
	{
		cout << setw(5) << left << "# " + to_string(cnt);
		i->second->ShowCltInfo();
		cout << '\n';
		cnt++;
	}
	cout << "\n>> 총 " << clientList.size() << "명의 고객\n" << endl;
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
	cout << "\t\t\t\t검색 결과" << endl;
	cout << LINE80 << endl;
	cout << std::setw(8) << left << "고객ID";
	cout << std::setw(10) << left << "이름";
	cout << std::setw(20) << left << "전화번호";
	cout << std::setw(30) << left << "주소" << endl;
	cout << LINE80 << endl;
	if (client != nullptr)
	{
		client->ShowCltInfo();
		cout << endl;
	}		
	else
	{
		cout << "존재하지 않는 고객ID입니다.\n" << endl;
	}	
}

void ClientHandler::ShowSearchResults(vector<Client*> searchResults) const
{
	int cnt = 1;
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	cout << LINE80 << endl;
	cout << setw(5) << left << "번호";
	cout << setw(8) << left << "고객ID";
	cout << setw(10) << left << "이름";
	cout << setw(20) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
	cout << LINE80 << endl;
	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		cout << setw(5) << left << "# " + to_string(cnt);
		(*i)->ShowCltInfo();
		cout << '\n';
		cnt++;
	}
	cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
	cout << LINE80 << endl;
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