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

	/*** 신규 고객 정보 입력 받기 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t신규 고객 등록" << endl;
	cout << LINE80 << endl;
	cout << "이름을 입력하세요: ";		cin >> name;
	phoneNumber = GetPhoneNumber();
	cout << "주소를 입력하세요: ";		cin.ignore();	getline(cin, address);

	/*** ID 생성 및 신규 고객 등록 ***/
	int id = MakeClientId();
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
	/*** 고객ID로 검색 ***/
	int id;
	Client* client;
	cout << "고객ID를 입력하세요: ";
	id = GetInt::GetInteger();
	client = SearchCltUsingId(id);
	ShowSearchResult(client);

	/*** 삭제/변경 메뉴 호출 ***/
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
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) {
		DeleteCltUsingPtr(client);
		cout << "\n삭제 완료!\n" << endl;
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
	/*** 고객 정보 변경 메뉴 ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. 이름\t\t2. 전화번호\t\t3. 주소\t\t4. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "변경할 항목을 선택하세요: ";
	sel = GetInt::GetInteger(1, 4);

	cout << LINE80 << endl;
	if (sel == 1) {
		string name;
		cout << "이름을 입력하세요: ";
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
		cout << "주소를 입력하세요: ";		cin.ignore();	getline(cin, address);
		client->SetCltAddress(address);
	}
	else
		return;
	
	
	cout << "\n변경 완료!\n" << endl;
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
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
	cout << LINE80 << endl;

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(searchResults);
}

void ClientHandler::DeleteCltUsingPtr(Client* client)
{
	/*** 고객 삭제 ***/
	int id = client->getCltID();
	delete clientList.at(id);
	clientList.erase(id);
}

void ClientHandler::ShowAllCltInfoMenu()
{
	/*** 전체 고객 조회 메뉴 ***/

	/*** 전체 고객 순서대로 가져오기 ***/
	vector<Client*> allClients;
	for (auto i = clientList.begin(); i != clientList.end(); i++)
		allClients.push_back(i->second);

	/*** 전체 고객 정보 출력 ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t전체 고객 조회" << endl;
	ShowSearchResults(allClients);
	cout << "\n>> 총 " << allClients.size() << "명의 고객\n" << endl;
	cout << LINE80 << endl;	

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(allClients);
}

void ClientHandler::SelectInSearchMenu(vector<Client*>& list)
{
	/*** 검색 목록에서 선택하기 ***/
	int sel;
	if (list.size() != 0) {
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetInteger(0, list.size());
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
		if(i->second->GetCltName().find(name) != -1)
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
	cout << setw(8) << left << "고객ID";
	cout << setw(10) << left << "이름";
	cout << setw(20) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
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
	/*** 검색한 결과들 출력 ***/
	int cnt = 1;	
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
}

int ClientHandler::MakeClientId()
{
	/*** 중복되지 않는 ID 생성 ***/
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
	/*** 올바른 전화번호 입력받기 ***/
	string phoneNum;

	cout << "전화번호를 입력하세요(ex 010-XXXX-XXXX): ";
	while (1) {
		cin >> phoneNum;
		if (IsValidPhoneNumber(phoneNum))
			return phoneNum;
		else
			cout << "올바르지 않은 전화번호입니다. 다시 입력하세요: ";
	}
}

bool ClientHandler::IsValidPhoneNumber(string phoneNumber)
{
	/*** 올바른 전화번호인지 검사 ***/
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