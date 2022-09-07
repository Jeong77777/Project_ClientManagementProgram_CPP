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
* @brief clientlist.txt 파일을 열어서 저장된 고객 리스트를 가져옴
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
				// (고객ID, 이름, 전화번호, 주소)
				Client* c = new Client(id, row[1], row[2], row[3]);
				clientList.insert({ id, c });
			}
		}
	}
	file.close();
}


/**
* @brief 고객 리스트를 clientlist.txt에 저장
*/
ClientHandler::~ClientHandler()
{
	ofstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		for (const auto& v : clientList) {
			Client* c = v.second;
			// (고객ID, 이름, 전화번호, 주소)
			file << c->GetCltID() << ", " << c->GetCltName() << ", ";
			file << c->GetCltPhoneNumber() << ", ";
			file << c->GetCltAddress() << endl;
			delete c; // 메모리 할당을 해제
		}
	}
	file.close();
}


/**
* @brief 고객 정보 관리 메뉴를 출력
*/
void ClientHandler::ShowClientMenu() const
{
	/* 고객 정보 관리 메뉴 출력 */
	cout << LINE80 << endl;
	cout << "\t\t\t\t고객 정보 관리" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  신규 고객 등록" << endl;
	cout << "\t\t\t\t2.  고객 조회(삭제, 변경)" << endl;
	cout << "\t\t\t\t3.  처음으로" << endl;
	cout << LINE80 << endl;
}



/**
* @brief 신규 고객 등록 메뉴
*/
void ClientHandler::AddClientMenu()
{	
	/* 신규 고객 정보 입력 받기 */
	try {
		cout << LINE80 << endl;
		cout << "\t\t\t\t신규 고객 등록" << endl;
		cout << LINE80 << endl;
		cout << "나가시려면 -1을 입력하세요.\n" << endl;

		string name = GetCltName(); // 고객 이름
		string phoneNumber = GetCltPhoneNum(); // 전화번호
		string address = GetCltAddress(); // 주소

		/* 고객ID 생성 */
		int id = MakeClientId(); // 고객ID 생성

		/* clientList에 고객 추가 */
		Client* newClient = new Client(id, name, phoneNumber, address);
		clientList.insert({ id, newClient });

		cout << "\n신규 고객 등록 완료!" << endl;
		cout << "고객번호는 " << id << "입니다.\n" << endl;
	}
	catch(int cancel){ // -1을 입력하면 등록을 취소한다.
		if (cancel == -1)
			cout << "\n등록을 취소합니다.\n" << endl;
	}	

	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}


/**
* @brief 고객 조회(삭제, 변경) 메뉴 출력
*/
void ClientHandler::SearchClientMenu()
{
	/* 고객 조회 메뉴 출력 */
	cout << LINE80 << endl;
	cout << "\t\t\t\t고객 조회(삭제, 변경)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  고객ID로 조회" << endl;
	cout << "\t\t\t\t2.  이름으로 조회" << endl;
	cout << "\t\t\t\t3.  전체 고객 조회" << endl;
	cout << "\t\t\t\t4.  이전 메뉴" << endl;
	cout << LINE80 << endl;

	/* 고객 조회 메뉴 선택 */
	cout << "메뉴를 선택하세요: ";
	int sel = GetInt::GetInteger(1, 4);

	if (sel == 1) // 고객ID로 조회
		SearchCltUsingIdMenu();
	else if (sel == 2) // 이름으로 조회
		SearchCltUsingNameMenu();
	else if (sel == 3) // 전체 고객 조회
		ShowAllCltInfoMenu();
	else if (sel == 4) // 이전 메뉴
		system("cls");
}


/**
* @brief 고객ID로 조회 메뉴
*/
void ClientHandler::SearchCltUsingIdMenu()
{
	/* 검색할 고객ID 입력 받기 */
	cout << "고객ID를 입력하세요(나가기 -1): ";
	int id = GetInt::GetInteger();
	if (id == -1) { // -1이면 나가기
		system("cls");
		return;
	}

	/* 고객ID를 이용하여 검색하고 결과 가져오기 */
	Client* client = SearchCltUsingId(id);

	/* 검색한 고객 정보 출력 */
	ShowSearchResult(client);

	/* 삭제/변경 메뉴 호출 */
	if (client != nullptr)
		ClientDeleteModifyMenu(client);
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}


/**
* @brief 이름으로 조회 메뉴
*/
void ClientHandler::SearchCltUsingNameMenu()
{
	/* 검색할 고객이름 입력 받기 */
	string name;	
	cout << "고객 이름을 입력하세요(나가기 -1): "; cin >> name;
	if (name == "-1") { // -1이면 나가기
		system("cls");
		return;
	}

	/* 검색 결과 가져오기 */
	vector<Client*> searchResults = SearchCltUsingName(name);

	/* 검색 결과 출력 */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
	cout << LINE80 << endl;

	/* 삭제/변경을 위한 선택 메뉴 호출 */
	SelectInSearchMenu(searchResults);
}


/**
* @brief 전체 고객 조회 메뉴
*/
void ClientHandler::ShowAllCltInfoMenu()
{
	/* 전체 고객 순서대로 가져오기 */
	vector<Client*> allClients;
	for (auto i = clientList.begin(); i != clientList.end(); i++)
		allClients.push_back(i->second);

	/* 전체 고객 정보 출력 */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t전체 고객 조회" << endl;
	ShowSearchResults(allClients);
	cout << "\n>> 총 " << allClients.size() << "명의 고객\n" << endl;
	cout << LINE80 << endl;

	/* 삭제/변경을 위한 선택 메뉴 호출 */
	SelectInSearchMenu(allClients);
}


/**
* @brief 조회한 고객 정보 리스트에서 고객 정보를 선택
* @param vector<Client*>& list 조회한 고객 정보 리스트
*/
void ClientHandler::SelectInSearchMenu(vector<Client*>& list)
{
	/* 조회한 고객 정보 리스트에서 고객 정보를 선택 */
	int sel;
	if (list.size() != 0) {
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/* 삭제/변경 메뉴 호출 */
			ClientDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}


/**
* @brief 고객 정보 삭제/변경 메뉴
* @param Client* client 삭제/변경할 고객
*/
void ClientHandler::ClientDeleteModifyMenu(Client* client)
{
	/* 삭제/변경/나가기 중에 선택 */
	cout << LINE80 << endl;
	cout << "1. 삭제\t\t2. 변경\t\t3. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "메뉴를 선택하세요: ";
	int sel = GetInt::GetInteger(1, 3);

	if (sel == 1) { // 삭제
		DeleteCltUsingPtr(client);
		cout << "\n삭제 완료!\n" << endl;
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) { // 변경
		ModifyClientMenu(client);
	}
	else; // 나가기
}


/**
* @brief 고객 정보 변경 메뉴
* @param Client* client 변경할 고객
*/
void ClientHandler::ModifyClientMenu(Client* client)
{
	/* 변경할 고객 정보 선택 */
	cout << LINE80 << endl;
	cout << "1. 이름\t\t2. 전화번호\t\t3. 주소\t\t4. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "변경할 항목을 선택하세요: ";
	int sel = GetInt::GetInteger(1, 4);	
	cout << LINE80 << endl;	

	try {
		if (sel == 1 || sel == 2 || sel == 3) {
			cout << "나가시려면 -1을 입력하세요." << endl;
			if (sel == 1) { // 이름 변경
				string name = GetCltName();
				client->SetCltName(name);
			}
			else if (sel == 2) { // 전화번호 변경
				string phone = GetCltPhoneNum();
				client->SetCltPhoneNumber(phone);
			}
			else if (sel == 3) { // 주소 변경
				string address = GetCltAddress();
				client->SetCltAddress(address);
			}
		}
		else // 나가기
			return;

		cout << "\n변경 완료!\n" << endl;
	}
	catch(int cancel){ // -1이면 변경 취소
		if (cancel == -1)
			cout << "\n변경을 취소합니다.\n" << endl;
	}
	
	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();
}


/**
* @brief 고객ID를 이용한 고객 검색
* @param int id 검색할 고객ID
* @return Clinet* 검색된 고객 반환
*/
Client* ClientHandler::SearchCltUsingId(int id) const
{
	/* 고객ID를 이용한 고객 검색 */
	auto i = clientList.find(id);

	if (i != clientList.end()) // 검색 결과가 존재할 때
		return i->second;
	else // 검색 결과가 존재하지 않을 때
		return nullptr;
}


/**
* @brief 고객이름을 이용한 고객 검색
* @param string name 검색할 고객이름
* @return vector<Client*> 검색된 고객들 반환
*/
vector<Client*> ClientHandler::SearchCltUsingName(string name) const
{
	/* 이름을 이용한 고객 검색 */
	vector<Client*> searchResults;

	for (auto i = clientList.begin(); i != clientList.end(); i++) {
		if (i->second->GetCltName().find(name) != -1)
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief 고객ID로 검색한 결과 출력
* @param Client* client 검색된 고객
*/
void ClientHandler::ShowSearchResult(Client* client) const
{
	/* 고객ID로 검색한 결과 출력 */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	cout << LINE80 << endl;
	cout << setw(8) << left << "고객ID";
	cout << setw(10) << left << "이름";
	cout << setw(20) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
	cout << LINE80 << endl;

	if (client != nullptr) { // 검색된 것이 존재할 때
		client->ShowCltInfo();
		cout << endl;
	}
	else { // 검색된 것이 존재하지 않을 때
		cout << "\n존재하지 않는 고객ID입니다.\n" << endl;
	}
}


/**
* @brief 검색한 결과들 출력(이름으로 조회, 전체 고객으로 조회)
* @param vector<Client*>& searchResults 검색된 고객들 리스트
*/
void ClientHandler::ShowSearchResults(vector<Client*>& searchResults) const
{
	/* 검색한 결과들 출력 */
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


/**
* @brief 고객 정보 삭제
* @param Client* client 고객 정보
*/
void ClientHandler::DeleteCltUsingPtr(Client* client)
{
	/* 고객 정보 삭제 */
	int id = client->GetCltID();
	delete clientList.at(id);
	clientList.erase(id);
}


/**
* @brief 중복되지 않는 고객ID 생성
* @return int 생성한 고객ID 반환
*/
int ClientHandler::MakeClientId()
{
	/* 중복되지 않는 고객ID 생성 */
	auto key = clientList.end();
	if (clientList.size() == 0) {
		// 기존에 저장된 고객정보가 한 개도 없을 때
		return 1001; // 고객ID는 1001부터 시작
	}
	else {
		// 기존에 저장된 고객정보가 있을 때
		// 가장 마지막 고객ID보다 +1만큼 큰 숫자를 반환
		int id = (--key)->first;
		return ++id;
	}
}


/**
* @brief 올바른 전화번호 입력 받기
* @return string 입력 받은 전화번호 반환
* @exception -1이 입력되면 입력 중단
*/
string ClientHandler::GetCltPhoneNum()
{
	/* 올바른 전화번호 입력받기 */
	string phoneNum;

	cout << "전화번호를 입력하세요(ex 010-XXXX-XXXX): ";
	while (1) {
		cin >> phoneNum;
		if (phoneNum == "-1")
			throw - 1; // -1이 입력되면 입력이 중단되도록 예외를 던짐
		else if (IsValidPhoneNum(phoneNum)) // 올바른 전화번호 인지 검사
			return phoneNum; 
		else
			cout << "올바르지 않은 전화번호입니다. 다시 입력하세요: ";
	}
}


/**
* @brief 이름 입력 받기
* @return string 입력 받은 이름 반환
* @exception -1이 입력되면 입력 중단
*/
string ClientHandler::GetCltName()
{
	string name;
	cout << "이름을 입력하세요: ";
	cin.ignore();	getline(cin, name); // 공백을 포함한다.
	if (name == "-1")
		throw - 1; // -1이 입력되면 입력이 중단되도록 예외를 던짐
	else
		return name;
}


/**
* @brief 주소 입력 받기
* @return string 입력 받은 주소 반환
* @exception -1이 입력되면 입력 중단
*/
string ClientHandler::GetCltAddress()
{
	string address;
	cout << "주소를 입력하세요: ";
	cin.ignore();	getline(cin, address); // 공백을 포함한다.
	if (address == "-1")
		throw - 1; // -1이 입력되면 입력이 중단되도록 예외를 던짐
	else
		return address;
}


/**
* @brief 올바른 전화번호인지 검사
* @param string phoneNumber 입력한 전화번호
* @return bool 올바른 전화번호인지 true/false
*/
bool ClientHandler::IsValidPhoneNum(string phoneNumber)
{
	/* 올바른 전화번호인지 검사 */
	string num[3];
	int dash1, dash2;

	dash1 = phoneNumber.find("-"); // 첫 번째 - 위치
	dash2 = phoneNumber.find("-", dash1 + 1); // 두 번째 - 위치

	num[0] = phoneNumber.substr(0, dash1); // 첫 번째 자리(지역번호)
	num[1] = phoneNumber.substr(dash1 + 1, dash2 - dash1 - 1); // 가운데 자리
	num[2] = phoneNumber.substr(dash2 + 1, phoneNumber.size() - dash2 - 1); // 마지막 자리

	/* 올바른 지역번호인지 검사 */
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

	/* 가운데 자리와 마지막 자리에 숫자만 있는지 검사 */
	for (int i = 1; i < 3; i++)
		if (false == !num[i].empty() && num[i].find_first_not_of("0123456789") == string::npos)
			return false;

	return true;
}


/**
* @brief CSV 형식 파일의 내용을 한 행씩 가져오기
* @param istream& file 가져올 내용이 들어있는 파일
* @param char delimiter 구분 문자
* @return vector<string> 한 행을 반환
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