#include "ClientHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>


void ClientHandler::ShowMenu() const
{
	/*** 고객 정보 관리 메뉴 출력 ***/
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
	/*** 신규 고객 등록 메뉴 ***/
	string name;
	string phoneNumber;
	string address;

	/*** 신규 고객 등록 메뉴 출력 ***/
	/*** 신규 고객 정보 입력 받기 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t신규 고객 등록" << endl;
	cout << LINE80 << endl;
	cout << "이름: ";		cin >> name;
	cout << "전화번호: ";	cin >> phoneNumber;
	cout << "주소: ";		cin.ignore();	getline(cin, address);

	/*** ID 생성 및 신규 고객 등록 ***/
	int id = MakeId();
	Client* newClient = new Client(id, name, phoneNumber, address);
	clientList.insert({ id, newClient });
	cout << "\n신규 고객 등록 완료!" << endl;
	cout << "고객번호는 " << id << "입니다.\n" << endl;

	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}

void ClientHandler::SearchClientMenu()
{
	int sel;

	/*** 고객 조회 메뉴 출력 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t고객 조회(삭제, 변경)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  고객ID로 조회" << endl;
	cout << "\t\t\t\t2.  이름으로 조회" << endl;
	cout << "\t\t\t\t3.  전체 고객 조회" << endl;
	cout << "\t\t\t\t4.  이전 메뉴" << endl;
	cout << LINE80 << endl;

	/*** 고객 조회 메뉴 선택 ***/
	cout << "메뉴를 선택하세요: ";
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
	/*** 고객ID로 검색 ***/
	int id;
	Client* client;
	cout << "고객ID를 입력하세요: ";
	id = GetInt::GetIntger();
	client = SearchCltUsingId(id);
	ShowSearchResult(client);

	/*** 삭제/변경 메뉴 ***/
	if (client != nullptr)
		ClientDeleteModifyMenu(client);
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}

void ClientHandler::ClientDeleteModifyMenu(Client* client)
{
	/*** 삭제/변경 메뉴 ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. 삭제\t\t2. 변경\t\t3. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetIntger(1, 3);

	if (sel == 1) {
		DeleteCltUsingPtr(client);
		cout << "삭제 완료!\n" << endl;
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) {
		ModifyClientMenu(client);
	}
	else;
}

void ClientHandler::ModifyClientMenu(Client* client)
{
	/*** 고객 변경 메뉴 ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. 이름\t\t2. 전화번호\t\t3. 주소\t\t4. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "변경할 항목을 선택하세요: ";
	sel = GetInt::GetIntger(1, 4);

	cout << LINE80 << endl;
	if (sel == 1) {
		string name;
		cout << "이름을 입력하세요: ";
		cin >> name;
		client->SetCltName(name);
	} 
	else if (sel == 2) {
		string phone;
		cout << "전화번호를 입력하세요: ";
		cin >> phone;
		client->SetCltPhoneNumber(phone);
	} 
	else if (sel == 3) {
		string address;
		cout << "주소를 입력하세요: ";
		cin >> address;
		client->SetCltAddress(address);
	}
	else {
		system("cls");
		return;
	}
	
	cout << "변경 완료!\n" << endl;
	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();
}


void ClientHandler::SearchCltUsingNameMenu()
{
	/*** 이름으로 조회 메뉴 ***/
	string name;
	vector<Client*> searchResults;

	cout << "고객 이름을 입력하세요: "; cin >> name;

	/*** 검색 결과 가져오기 ***/
	searchResults = SearchCltUsingName(name);
	/*** 검색 결과 출력 ***/
	ShowSearchResults(searchResults);

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(searchResults);
}


void ClientHandler::DeleteCltUsingPtr(Client* client)
{
	/*** 고객 삭제 ***/
	int id = client->getCltId();
	delete clientList.at(id);
	clientList.erase(id);
}

void ClientHandler::ShowAllCltInfoMenu()
{
	/*** 전체 고객 조회 메뉴 ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t전체 고객 조회" << endl;
	cout << LINE80 << endl;
	cout << setw(10) << left << "번호";
	cout << setw(8) << left << "고객ID";
	cout << setw(10) << left << "이름";
	cout << setw(20) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
	cout << LINE80 << endl;
	ShowAllCltInfo();
	cout << LINE80 << endl;

	/*** 전체 고객 가져오기 ***/
	vector<Client*> allClients;
	for (auto i = clientList.begin(); i != clientList.end(); i++)
		allClients.push_back(i->second);

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(allClients);
}

void ClientHandler::SelectInSearchMenu(vector<Client*>& list)
{
	/*** 검색 목록에서 선택하기 ***/
	int sel;
	if (list.size() != 0) {
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetIntger(0, list.size());
		if (sel != 0)
			/*** 삭제/변경 메뉴 진입 ***/
			ClientDeleteModifyMenu(list[sel - 1]);			
	}
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}

void ClientHandler::ShowAllCltInfo() const
{
	/*** 전체 고객 출력 ***/
	int cnt = 1;
	for (auto i = clientList.begin(); i != clientList.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		i->second->ShowCltInfo();
		cout << '\n';
		cnt++;
	}
	cout << "\n>> 총 " << clientList.size() << "명의 고객\n" << endl;
}

Client* ClientHandler::SearchCltUsingId(int id) const
{
	/*** 고객ID로 검색 ***/
	auto i = clientList.find(id);

	if (i != clientList.end())
		return i->second;
	else
		return nullptr;
}

vector<Client*> ClientHandler::SearchCltUsingName(string name) const
{
	/*** 이름으로 검색 ***/
	vector<Client*> searchResults;	

	for (auto i = clientList.begin(); i != clientList.end(); i++) {
		if (name == i->second->GetCltName())
			searchResults.push_back(i->second);
	}
	
	return searchResults;
}

void ClientHandler::ShowSearchResult(Client* client) const
{
	/*** ID로 검색한 결과 출력 ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	cout << LINE80 << endl;
	cout << std::setw(8) << left << "고객ID";
	cout << std::setw(10) << left << "이름";
	cout << std::setw(20) << left << "전화번호";
	cout << std::setw(30) << left << "주소" << endl;
	cout << LINE80 << endl;

	if (client != nullptr) {
		client->ShowCltInfo();
		cout << endl;
	}		
	else {
		cout << "\n존재하지 않는 고객ID입니다.\n" << endl;
	}	
}

void ClientHandler::ShowSearchResults(vector<Client*>& searchResults) const
{
	/*** 이름으로 검색한 결과들 출력 ***/
	int cnt = 1;
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	cout << LINE80 << endl;
	cout << setw(10) << left << "번호";
	cout << setw(8) << left << "고객ID";
	cout << setw(10) << left << "이름";
	cout << setw(20) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
	cout << LINE80 << endl;
	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		(*i)->ShowCltInfo();
		cout << '\n';
		cnt++;
	}
	cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
	cout << LINE80 << endl;
}

int ClientHandler::MakeId()
{
	/*** 중복되지 않는 ID 생성 ***/
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