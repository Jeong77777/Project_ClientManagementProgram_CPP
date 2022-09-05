#include "OrderHandler.h"
#include "GetInteger.h"
#include "Line.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

OrderHandler::OrderHandler(ClientHandler& cltRef, ProductHandler& prodRef)
	:cltManager(cltRef), prodManager(prodRef)
{
	ifstream file;
	file.open("orderlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int num = stoi(row[0]);
				int cltID = stoi(row[2]);
				int prodID = stoi(row[3]);
				int prodNum = stoi(row[4]);
				Order* o = new Order(num, row[1], cltID, prodID, prodNum);
				orderList.insert({ num, o });
			}
		}
	}
	file.close();
}

OrderHandler::~OrderHandler()
{
	ofstream file;
	file.open("orderlist.txt");
	if (!file.fail()) {
		for (const auto& v : orderList) {
			Order* o = v.second;
			file << o->GetOrderNum() << ", " << o->GetOrderDate() << ", ";
			file << o->GetOrderCltID() << ", " << o->GetOrderProdID() << ", ";
			file << o->GetOrderProdNum() << endl;
			delete o;
		}
	}
	file.close();
}


void OrderHandler::ShowOrderMenu() const
{
	/*** 주문 내역 관리 메뉴 출력 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t주문 내역 관리" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  주문 내역 등록" << endl;
	cout << "\t\t\t\t2.  주문 내역 조회(삭제, 변경)" << endl;
	cout << "\t\t\t\t3.  처음으로" << endl;
	cout << LINE80 << endl;
}

void OrderHandler::AddOrderMenu()
{
	/*** 주문 내역 등록 메뉴 ***/
	int num;		// 주문번호
	string date;	// 주문일자
	int cltID;		// 고객ID
	int prodID;		// 상품ID
	int prodNum;	// 주문수량

	/*** 주문 정보 입력 받기 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t주문 내역 등록" << endl;
	cout << LINE80 << endl;

	date = GetDateString();
	cltID = GetCltID();
	prodID = GetProdID();
	cout << "주문 수량을 입력하세요: ";
	prodNum = GetInt::GetInteger();
	num = MakeOrderNum();

	/*** 주문 정보 등록 ***/
	Order* newOrder = new Order(num, date, cltID, prodID, prodNum);
	orderList.insert({ num, newOrder });
	cout << "\n주문 내역 등록 완료!" << endl;
	cout << "주문번호는 " << num << "입니다.\n" << endl;

	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}

void OrderHandler::SearchOrderMenu()
{
	int sel;

	/*** 상품 조회 메뉴 출력 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t주문 내역 조회(삭제, 변경)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  주문번호로 조회" << endl;
	cout << "\t\t\t\t2.  고객ID로 조회" << endl;
	cout << "\t\t\t\t3.  상품ID로 조회" << endl;
	cout << "\t\t\t\t4.  주문일자별 조회" << endl;
	cout << "\t\t\t\t5.  전체 주문 내역 조회" << endl;
	cout << "\t\t\t\t6.  이전 메뉴" << endl;
	cout << LINE80 << endl;

	/*** 상품 조회 메뉴 선택 ***/
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetInteger(1, 6);

	if (sel == 1)
		SearchOrderUsingNumMenu();
	else if (sel == 2)
		SearchOrderUsingCltIdMenu();
	else if (sel == 3)
		SearchOrderUsingProdIdMenu();
	else if (sel == 4)
		SearchOrderUsingDateMenu();
	else if (sel == 5)
		ShowAllOrderInfoMenu();
	else
		system("cls");
}

void OrderHandler::SearchOrderUsingNumMenu()
{
	/*** 주문번호로 검색 ***/
	int num;
	Order* order;
	cout << "주문번호를 입력하세요: ";
	num = GetInt::GetInteger();
	order = SearchOrderUsingNum(num);
	ShowSearchResult(order);

	/*** 삭제/변경 메뉴 호출 ***/
	if (order != nullptr)
		OrderDeleteModifyMenu(order);
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}

Order* OrderHandler::SearchOrderUsingNum(int num) const
{
	/*** 주문번호로 검색 ***/
	auto i = orderList.find(num);

	if (i != orderList.end())
		return i->second;
	else
		return nullptr;
}

void OrderHandler::ShowSearchResult(Order* order) const
{
	/*** 주문번호로 검색한 결과 출력 ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	cout << LINE80 << endl;
	cout << setw(16) << left << "주문번호";
	cout << setw(15) << left << "주문일자";
	cout << setw(30) << left << "상품ID(상품명)";
	cout << setw(12) << left << "주문수량";
	cout << setw(10) << left << "주문금액" << endl;
	cout << setw(16) << left << "고객ID(이름)";
	cout << setw(15) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
	cout << LINE80 << endl;
	
	if (order != nullptr) {
		ShowOrderInfoRow1(order);
		ShowOrderInfoRow2(order);
		cout << endl;
	}
	else {
		cout << "\n존재하지 않는 주문번호입니다.\n" << endl;
	}
}

void OrderHandler::ShowOrderInfoRow1(Order* order) const
{
	/*** 주문 정보 1행 출력 ***/

	/*** 주문번호 ***/
	cout << setw(16) << left << order->GetOrderNum();

	/*** 주문일자 ***/
	cout << setw(15) << left << order->GetOrderDate();

	/*** 상품ID(상품명) ***/
	Product* product = prodManager.SearchProdUsingId(order->GetOrderProdID());
	if (product != nullptr) {
		cout << setw(30) << left << to_string(product->GetProdID()) + \
			'(' + product->GetProdName() + ')';
	}
	else {
		cout << setw(30) << left << "상품 정보 없음";
	}

	/*** 주문수량 ***/
	cout << setw(12) << left << order->GetOrderProdNum();

	/*** 주문금액 ***/
	if (product != nullptr) {
		cout << setw(10) << left << order->GetOrderProdNum() * product->GetProdPrice() << endl;
	}
	else {
		cout << setw(10) << left << "상품 정보 없음" << endl;
	}
}

void OrderHandler::ShowOrderInfoRow2(Order* order) const
{
	/*** 주문 정보 2행 출력 ***/

	/*** 고객ID(이름), 전화번호, 주소 ***/
	Client* client = cltManager.SearchCltUsingId(order->GetOrderCltID());
	if (client != nullptr) {
		cout << setw(16) << left << to_string(client->getCltID()) + \
			'(' + client->GetCltName() + ')';
		cout << setw(15) << left << client->GetCltPhoneNumber();
		cout << setw(30) << left << client->GetCltAddress() << endl;
	}
	else {
		cout << setw(16) << left << "고객 정보 없음" << endl;
	}
}

void OrderHandler::OrderDeleteModifyMenu(Order* order)
{
	/*** 삭제/변경 메뉴 ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. 삭제\t\t2. 변경\t\t3. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) {
		DeleteOrderUsingPtr(order);
		cout << "\n삭제 완료!\n" << endl;
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) {
		ModifyOrderMenu(order);
	}
	else;
}

void OrderHandler::DeleteOrderUsingPtr(Order* order)
{
	/*** 상품 삭제 ***/
	int num = order->GetOrderNum();
	delete orderList.at(num);
	orderList.erase(num);
}

void OrderHandler::ModifyOrderMenu(Order* order)
{
	/*** 구매 내역 변경 메뉴 ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. 주문일자       2. 고객ID       3. 상품ID       4. 주문수량       5. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "변경할 항목을 선택하세요: ";
	sel = GetInt::GetInteger(1, 5);

	cout << LINE80 << endl;
	if (sel == 1) {
		string date;
		cout << "주문일자를 입력하세요: ";
		date = GetDateString();
		order->SetOrderDate(date);
	}
	else if (sel == 2) {
		int cltID;
		cltID = GetCltID();
		order->SetOrderCltID(cltID);
	}
	else if (sel == 3) {
		int prodID;
		prodID = GetProdID();
		order->SetOrderProdID(prodID);
	}
	else if (sel == 4) {
		int prodNum;
		cout << "주문수량을 입력하세요: ";
		prodNum = GetInt::GetInteger();
		order->SetOrderProdNum(prodNum);
	}
	else
		return;

	cout << "\n변경 완료!\n" << endl;
	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();
}

void OrderHandler::SearchOrderUsingCltIdMenu()
{
	/*** 고객ID로 조회 메뉴 ***/
	int cltID;
	vector<Order*> searchResults;

	cltID = GetCltID();	

	/*** 검색 결과 가져오기 ***/
	searchResults = SearchOrderUsingCltId(cltID);

	/*** 검색 결과 출력 ***/
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
	cout << LINE90 << endl;

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(searchResults);
}

vector<Order*> OrderHandler::SearchOrderUsingCltId(int cltID) const
{
	/*** 고객ID로 검색 ***/
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (cltID == i->second->GetOrderCltID())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void OrderHandler::ShowSearchResults(vector<Order*>& searchResults) const
{
	/*** 검색한 결과들 출력 ***/
	int cnt = 1;	
	cout << LINE90 << endl;
	cout << setw(10) << left << "번호";
	cout << setw(16) << left << "주문번호";
	cout << setw(15) << left << "주문일자";
	cout << setw(30) << left << "상품ID(상품명)";
	cout << setw(12) << left << "주문수량";
	cout << setw(10) << left << "주문금액" << endl;
	cout << "          ";
	cout << setw(16) << left << "고객ID(이름)";
	cout << setw(15) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
	cout << LINE90 << endl;

	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		ShowOrderInfoRow1(*i);
		cout << "          ";
		ShowOrderInfoRow2(*i);
		cout << '\n';
		cnt++;
	}	
}

void OrderHandler::SelectInSearchMenu(vector<Order*>& list)
{
	/*** 검색 목록에서 선택하기 ***/
	int sel;
	if (list.size() != 0) {
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/*** 삭제/변경 메뉴 진입 ***/
			OrderDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}

void OrderHandler::SearchOrderUsingProdIdMenu()
{
	/*** 상품ID로 조회 메뉴 ***/
	int prodID;
	vector<Order*> searchResults;

	prodID = GetProdID();

	/*** 검색 결과 가져오기 ***/
	searchResults = SearchOrderUsingProdId(prodID);

	/*** 검색 결과 출력 ***/
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
	cout << LINE90 << endl;

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(searchResults);
}

vector<Order*> OrderHandler::SearchOrderUsingProdId(int prodID) const
{
	/*** 상품ID로 검색 ***/
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (prodID == i->second->GetOrderProdID())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void OrderHandler::SearchOrderUsingDateMenu()
{
	/*** 일자별 조회 메뉴 ***/
	string date;
	vector<Order*> searchResults;

	date = GetDateString();

	/*** 검색 결과 가져오기 ***/
	searchResults = SearchOrderUsingDate(date);

	/*** 검색 결과 출력 ***/
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
	cout << LINE90 << endl;

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(searchResults);
}

vector<Order*> OrderHandler::SearchOrderUsingDate(string date) const
{
	/*** 일자로 검색 ***/
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (date == i->second->GetOrderDate())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void OrderHandler::ShowAllOrderInfoMenu()
{
	/*** 전체 주문 내역 조회 메뉴 ***/

	/*** 전체 주문 내역 순서대로 가져오기 ***/
	vector<Order*> allOrders;
	for (auto i = orderList.begin(); i != orderList.end(); i++)
		allOrders.push_back(i->second);

	/*** 전체 주문 내역 출력 ***/
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t전체 주문 내역 조회" << endl;
	ShowSearchResults(allOrders);
	cout << "\n>> 총 " << allOrders.size() << "개의 주문 내역\n" << endl;
	cout << LINE90 << endl;	

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(allOrders);
}

string OrderHandler::GetDateString()
{
	/*** string형식의 날짜 입력받기 ***/
	string strDate;	// 날짜
	int intDate;
	int day, month, year;

	cout << "주문일자를 입력하세요(ex 20220907): ";

	while (1) {
		intDate = GetInt::GetInteger();
		year = intDate / 10000;
		month = (intDate - (year * 10000)) / 100;
		day = intDate % 100;
		if (CheckValidDate(year, month, day)) {
			strDate = to_string(year) + '-';
				if (month < 10) strDate += '0';
				strDate += to_string(month) + '-';
				if (day < 10) strDate += '0';
				strDate += to_string(day);
				return strDate;
		}
		else
			cout << "유효하지 않은 날짜입니다. 다시 입력하세요: ";
	}
}

int OrderHandler::GetCltID()
{
	/*** 등록된 고객ID 입력받기 ***/
	int id;

	cout << "고객ID를 입력하세요: ";
	while (1) {
		id = GetInt::GetInteger();
		if (cltManager.SearchCltUsingId(id) != nullptr)
			return id;
		else
			cout << "등록되지 않은 고객ID입니다. 다시 입력하세요: ";		
	}
}

int OrderHandler::GetProdID()
{
	/*** 등록된 상품ID 입력받기 ***/
	int id;

	cout << "상품ID를 입력하세요: ";
	while (1) {
		id = GetInt::GetInteger();
		if (prodManager.SearchProdUsingId(id) != nullptr)
			return id;
		else
			cout << "등록되지 않은 상품ID입니다. 다시 입력하세요: ";
	}
}

bool OrderHandler::CheckValidDate(int year, int month, int day)
{
	/*** 날짜의 유효성 검사 ***/
	/*** 년도 검사 ***/
	if (year < 1900 || year>2999) // 1900~2999년
		return false;

	/*** 월,일 검사 ***/
	if (month < 1 || month>12)  // 1~12
		return false;
	else {
		if ((month & 0x1) == 1) { // odd month
			if (month <= 7) {	// 1, 3, 5, 7
				if (day < 1 || day>31)
					return false;
			}
			else {	// 9, 11
				if (day < 1 || day>30)
					return false;
			}
		}
		else {					// even month
			if (month == 2) {	// 2
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
					if (day < 1 || day>29)	// 윤년
						return false;
				}
				else {	// 평년
					if (day < 1 || day>28)
						return false;
				}
			}
			else if (month <= 6) {	// 4, 6
				if (day < 1 || day>30)
					return false;
			}
			else {	// 8, 10, 12
				if (day < 1 || day>31)
					return false;
			}
		}
	}

	return true;
}

int OrderHandler::MakeOrderNum()
{
	/*** 중복되지 않는 주문번호 생성 ***/
	auto key = orderList.end();
	if (orderList.size() == 0) {
		return 10001;
	}
	else {
		int num = (--key)->first;
		return ++num;
	}
}

vector<string> OrderHandler::parseCSV(istream& file, char delimiter)
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