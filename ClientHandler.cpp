#include "ClientHandler.h"
#include <Windows.h>
#include <iostream>


void ClientHandler::ShowMenu() const
{
	//system("cls");
	cout << "\n-----Menu------" << endl;
	cout << "1. 신규 고객 등록" << endl;
	cout << "2. 고객 정보 조회" << endl;
	cout << "3. 고객 정보 삭제" << endl;
	cout << "4. 처음으로" << endl;
}

void ClientHandler::AddClient()
{
	string name;
	string phoneNumber;
	string address;
	string email;

	cout << "\n[신규 고객 등록]" << endl;
	cout << "이름: ";		cin >> name;
	cout << "전화번호: ";	cin >> phoneNumber;
	cout << "주소: ";		cin.ignore();	getline(cin, address);
	cout << "이메일주소: ";	cin >> email;

	int id = MakeId();
	Client* newClient = new Client(id, name, phoneNumber, address, email);
	clientList.insert({ id, newClient });
	cout << "\n신규 고객 등록 완료!" << endl;
	cout << "고객번호는 " << id << "입니다.\n" << endl;
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
	cout << "\n>> 총 " << clientList.size() << "명의 고객\n" << endl;
}

void ClientHandler::SearchClient() const
{
	int sel;
	cout << "\n-----고객 조회(삭제, 변경)------" << endl;
	cout << "1. 고객ID로 조회" << endl;
	cout << "2. 이름으로 조회" << endl;
	cout << "3. 전체 고객 조회" << endl;
	cout << "4. 이전 메뉴" << endl;
	cout << "선택: ";	cin >> sel;

	if (sel == 1)
		SearchUsingId();
	else if (sel == 2)
		SearchUsingName();
	else if (sel == 3)
		ShowAllAccInfo();
	else if (sel == 4)
		;
	else
		cout << "잘못된 입력입니다." << endl;
}

void ClientHandler::ShowSearchResult(vector<Client*> searchResults) const
{
	cout << '\n';
	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		(*i)->ShowCltInfo();
		cout << '\n';
	}
	cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
}

vector<Client*> ClientHandler::SearchUsingId() const
{
	int id;
	vector<Client*> searchResults;

	cout << "\n고객ID를 입력하시오: ";	cin >> id;

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

	cout << "\n고객 이름을 입력하시오: "; cin >> name;

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