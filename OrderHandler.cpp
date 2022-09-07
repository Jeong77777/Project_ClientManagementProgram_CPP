#include "OrderHandler.h"
#include "GetInteger.h"
#include "Line.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>


/**
* @brief orderlist.txt 파일을 열어서 저장된 상품 리스트를 가져옴 /
*       고객 정보 관리 객체, 상품 정보 관리 객체를 참조형으로 가져옴
*/
OrderHandler::OrderHandler(ClientHandler& cltRef, ProductHandler& prodRef)
	:cltHandler(cltRef), prodHandler(prodRef)
{
	ifstream file;
	file.open("orderlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int num = stoi(row[0]); // 상품번호
				int cltID = stoi(row[2]); // 고객ID
				int prodID = stoi(row[3]); // 상품ID
				int prodNum = stoi(row[4]); // 재고수량
				// (상품번호, 주문일자, 고객ID, 상품ID, 재고수량)
				Order* o = new Order(num, row[1], cltID, prodID, prodNum);
				orderList.insert({ num, o });
			}
		}
	}
	file.close();
}


/**
* @brief 상품 리스트를 orderlist.txt에 저장
*/
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
			delete o; // 메모리 할당을 해제
		}
	}
	file.close();
}


/**
* @brief 주문 내역 관리 메뉴를 출력
*/
void OrderHandler::ShowOrderMenu() const
{
	/* 주문 내역 관리 메뉴 출력 */
	cout << LINE80 << endl;
	cout << "\t\t\t\t주문 내역 관리" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  주문 내역 등록" << endl;
	cout << "\t\t\t\t2.  주문 내역 조회(삭제, 변경)" << endl;
	cout << "\t\t\t\t3.  처음으로" << endl;
	cout << LINE80 << endl;
}


/**
* @brief 주문 내역 등록 메뉴
*/
void OrderHandler::AddOrderMenu()
{
	/* 주문 정보 입력 받기 */
	try {
		cout << LINE80 << endl;
		cout << "\t\t\t\t주문 내역 등록" << endl;
		cout << LINE80 << endl;
		cout << "나가시려면 -1을 입력하세요.\n" << endl;

		string date = GetDateString(); // 주문일자
		int cltID = GetCltID(); // 고객ID
		int prodID = GetProdID(); // 상품ID
		int prodNum = GetProdNum(prodID); // 주문수량

		/* 주문번호 생성 생성 */
		int num = MakeOrderNum(); // 

		/* orderList에 주문 추가 */
		Order* newOrder = new Order(num, date, cltID, prodID, prodNum);
		orderList.insert({ num, newOrder });
		cout << "\n주문 내역 등록 완료!" << endl;
		cout << "주문번호는 " << num << "입니다.\n" << endl;
	}
	catch (int cancel) {// -1을 입력하면 등록을 취소한다.
		if (cancel == -1)
			cout << "\n등록을 취소합니다.\n" << endl;
	}	

	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}


/**
* @brief 주문 내역 조회(삭제, 변경) 메뉴 출력
*/
void OrderHandler::SearchOrderMenu()
{
	/* 주문 내역 조회 메뉴 출력 */
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

	/* 주문 내역 조회 메뉴 선택 */
	cout << "메뉴를 선택하세요: ";
	int sel = GetInt::GetInteger(1, 6);

	if (sel == 1) // 주문번호로 조회
		SearchOrderUsingNumMenu();
	else if (sel == 2) // 고객ID로 조회
		SearchOrderUsingCltIdMenu();
	else if (sel == 3) // 상품ID로 조회
		SearchOrderUsingProdIdMenu();
	else if (sel == 4) // 주문일자별 조회
		SearchOrderUsingDateMenu();
	else if (sel == 5) // 전체 주문 내역 조회
		ShowAllOrderInfoMenu();
	else // 이전 메뉴
		system("cls");
}


/**
* @brief 주문번호로 조회 메뉴
*/
void OrderHandler::SearchOrderUsingNumMenu()
{
	/* 검색할 주문번호 입력 받기 */
	cout << "주문번호를 입력하세요(나가기 -1): ";
	int num = GetInt::GetInteger();
	if (num == -1) {
		system("cls");
		return;
	}

	/* 주문번호를 이용하여 검색하고 결과 가져오기 */
	Order* order = SearchOrderUsingNum(num);

	/* 검색한 주문 내역 출력 */
	ShowSearchResult(order);

	/* 삭제/변경 메뉴 호출 */
	if (order != nullptr)
		OrderDeleteModifyMenu(order);
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}


/**
* @brief 고객ID로 조회 메뉴
*/
void OrderHandler::SearchOrderUsingCltIdMenu()
{	
	try {
		/* 검색할 고객ID 입력 받기 */
		cout << "나가시려면 -1을 입력하세요." << endl;
		int cltID = GetCltID();

		/* 검색 결과 가져오기 */
		vector<Order*> searchResults = SearchOrderUsingCltId(cltID);

		/* 검색 결과 출력 */
		system("cls");
		cout << LINE90 << endl;
		cout << "\t\t\t\t검색 결과" << endl;
		ShowSearchResults(searchResults);
		cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
		cout << LINE90 << endl;

		/* 삭제/변경을 위한 선택 메뉴 호출 */
		SelectInSearchMenu(searchResults);
	}
	catch (int cancel) { // -1이면 검색 취소
		if (cancel == -1) {
			system("cls");
			return;
		}
	}
}


/**
* @brief 상품ID로 조회 메뉴
*/
void OrderHandler::SearchOrderUsingProdIdMenu()
{
	try {
		/* 검색할 상품ID 입력 받기 */
		cout << "나가시려면 -1을 입력하세요." << endl;
		int prodID = GetProdID();

		/* 검색 결과 가져오기 */
		vector<Order*>searchResults = SearchOrderUsingProdId(prodID);

		/* 검색 결과 출력 */
		system("cls");
		cout << LINE90 << endl;
		cout << "\t\t\t\t검색 결과" << endl;
		ShowSearchResults(searchResults);
		cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
		cout << LINE90 << endl;

		/* 삭제/변경을 위한 선택 메뉴 호출 */
		SelectInSearchMenu(searchResults);
	}
	catch (int cancel) { // -1이면 검색 취소
		if (cancel == -1) {
			system("cls");
			return;
		}
	}
}


/**
* @brief 주문일자별 조회 메뉴
*/
void OrderHandler::SearchOrderUsingDateMenu()
{
	try {
		/* 검색할 주문일자 입력 받기 */
		cout << "나가시려면 -1을 입력하세요." << endl;
		string date = GetDateString();

		/* 검색 결과 가져오기 */
		vector<Order*>searchResults = SearchOrderUsingDate(date);

		/* 검색 결과 출력 */
		system("cls");
		cout << LINE90 << endl;
		cout << "\t\t\t\t검색 결과" << endl;
		ShowSearchResults(searchResults);
		cout << "\n>> " << searchResults.size() << "개의 검색 결과\n" << endl;
		cout << LINE90 << endl;

		/* 삭제/변경을 위한 선택 메뉴 호출 */
		SelectInSearchMenu(searchResults);
	}
	catch (int cancel) { // -1이면 검색 취소
		if (cancel == -1) {
			system("cls");
			return;
		}
	}
}


/**
* @brief 전체 주문 내역 조회 메뉴
*/
void OrderHandler::ShowAllOrderInfoMenu()
{
	/* 전체 주문 내역 순서대로 가져오기 */
	vector<Order*> allOrders;
	for (auto i = orderList.begin(); i != orderList.end(); i++)
		allOrders.push_back(i->second);

	/* 전체 주문 내역 출력 */
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t전체 주문 내역 조회" << endl;
	ShowSearchResults(allOrders);
	cout << "\n>> 총 " << allOrders.size() << "개의 주문 내역\n" << endl;
	cout << LINE90 << endl;

	/* 삭제/변경을 위한 선택 메뉴 호출 */
	SelectInSearchMenu(allOrders);
}


/**
* @brief 조회한 주문 내역 리스트에서 주문 내역을 선택
* @param vector<Order*>& list 조회한 주문 내역 리스트
*/
void OrderHandler::SelectInSearchMenu(vector<Order*>& list)
{
	/* 조회한 주문 내역 리스트에서 주문 내역을 선택 */
	int sel;
	if (list.size() != 0) {
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/* 삭제/변경 메뉴 호출 */
			OrderDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}


/**
* @brief 주문 내역 삭제/변경 메뉴
* @param Order* order 삭제/변경할 주문 내역
*/
void OrderHandler::OrderDeleteModifyMenu(Order* order)
{
	/* 삭제/변경/나가기 중에 선택 */
	int sel;
	cout << LINE90 << endl;
	cout << "1. 삭제\t\t2. 변경\t\t3. 나가기" << endl;
	cout << LINE90 << endl;
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) { // 삭제
		Product* product = prodHandler.SearchProdUsingId(order->GetOrderProdID());
		string input;

		if (product != nullptr) { // 삭제한 주문내역의 상품 정보가 있다면
			cout << "삭제한 주문내역에 대한 상품재고를 다시 추가하시겠습니까?(y/n): ";
			while (1) {
				cin >> input;
				if (input == "y" || input == "Y") {
					product->SetProdStock(product->GetProdStock() + order->GetOrderProdNum());
					break;
				}
				else if (input == "n" || input == "N")
					break;
				else
					cout << "다시 입력하세요: ";
			}
		}

		DeleteOrderUsingPtr(order);
		cout << "\n삭제 완료!\n" << endl;
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) { // 변경
		ModifyOrderMenu(order);
	}
	else; // 나가기
}


/**
* @brief 주문 내역 변경 메뉴
* @param Order* order 변경할 주문 내역
*/
void OrderHandler::ModifyOrderMenu(Order* order)
{
	/* 주문 내역 정보 선택 */
	cout << LINE90 << endl;
	cout << "1. 주문일자       2. 고객ID       3. 상품ID       4. 주문수량       5. 나가기" << endl;
	cout << LINE90 << endl;
	cout << "변경할 항목을 선택하세요: ";
	int sel = GetInt::GetInteger(1, 5);

	cout << LINE90 << endl;
	try {
		if (sel == 1 || sel == 2 || sel == 3 || sel == 4) {
			cout << "나가시려면 -1을 입력하세요." << endl;
			if (sel == 1) { // 주문일자 변경
				string date;
				date = GetDateString();
				order->SetOrderDate(date);
			}
			else if (sel == 2) { // 고객ID 변경
				int cltID;
				cltID = GetCltID();
				order->SetOrderCltID(cltID);
			}
			else if (sel == 3) { // 상품ID 변경
				ChangeProdID(order);
			}
			else if (sel == 4) { // 주문수량 변경
				ChangeProdNum(order);
			}
		}
		else // 나가기
			return;

		cout << "\n변경 완료!\n" << endl;
	}
	catch (int cancel) {// -1이면 변경 취소
		if (cancel == -1)
			cout << "\n변경을 취소합니다.\n" << endl;
	}
	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();
}


/**
* @brief 주문번호를 이용한 주문 내역 검색
* @param int num 검색할 주문번호
* @return Order* 검색된 주문 내역 반환
*/
Order* OrderHandler::SearchOrderUsingNum(int num) const
{
	/* 주문번호를 이용한 주문 내역 검색 */
	auto i = orderList.find(num);

	if (i != orderList.end()) // 검색 결과가 존재할 때
		return i->second;
	else // 검색 결과가 존재하지 않을 때
		return nullptr;
}


/**
* @brief 고객ID를 이용한 주문 내역 검색
* @param int cltID 검색할 고객ID
* @return vector<Order*> 검색된 주문 내역들 반환
*/
vector<Order*> OrderHandler::SearchOrderUsingCltId(int cltID) const
{
	/* 고객ID를 이용한 주문 내역 검색 */
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (cltID == i->second->GetOrderCltID())
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief 상품ID를 이용한 주문 내역 검색
* @param int prodID 검색할 상품ID
* @return vector<Order*> 검색된 주문 내역들 반환
*/
vector<Order*> OrderHandler::SearchOrderUsingProdId(int prodID) const
{
	/* 상품ID를 이용한 주문 내역 검색 */
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (prodID == i->second->GetOrderProdID())
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief 주문일자별 주문 내역 검색
* @string date 검색할 주문일자
* @return vector<Order*> 검색된 주문 내역들 반환
*/
vector<Order*> OrderHandler::SearchOrderUsingDate(string date) const
{
	/* 주문일자별 주문 내역 검색 */
	vector<Order*> searchResults;

	for (auto i = orderList.begin(); i != orderList.end(); i++) {
		if (date == i->second->GetOrderDate())
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief 주문번호로 검색한 결과 출력
* @param Order* order 검색된 주문 내역
*/
void OrderHandler::ShowSearchResult(Order* order) const
{
	/* 주문번호로 검색한 결과 출력 */
	system("cls");
	cout << LINE90 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	cout << LINE90 << endl;
	cout << setw(16) << left << "주문번호";
	cout << setw(15) << left << "주문일자";
	cout << setw(30) << left << "상품ID(상품명)";
	cout << setw(12) << left << "주문수량";
	cout << setw(10) << left << "주문금액" << endl;
	cout << setw(16) << left << "고객ID(이름)";
	cout << setw(15) << left << "전화번호";
	cout << setw(30) << left << "주소" << endl;
	cout << LINE90 << endl;

	if (order != nullptr) { // 검색된 것이 존재할 때
		ShowOrderInfoRow1(order);
		ShowOrderInfoRow2(order);
		cout << endl;
	}
	else { // 검색된 것이 존재하지 않을 때
		cout << "\n존재하지 않는 주문번호입니다.\n" << endl;
	}
}


/**
* @brief 검색한 결과들 출력(고객ID, 상품ID, 주문일자별, 전체 주문 내역으로 조회)
* @param vector<Order*>& searchResults 검색된 주문 내역들 리스트
*/
void OrderHandler::ShowSearchResults(vector<Order*>& searchResults) const
{
	/* 검색한 결과들 출력 */
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


/**
* @brief 한 개의 주문 내역 출력 (1행)
* @param Order* order 한 개의 주문 내역
*/
void OrderHandler::ShowOrderInfoRow1(Order* order) const
{
	/* 주문번호 */
	cout << setw(16) << left << order->GetOrderNum();

	/* 주문일자 */
	cout << setw(15) << left << order->GetOrderDate();

	/* 상품ID(상품명) */
	Product* product = prodHandler.SearchProdUsingId(order->GetOrderProdID());

	if (product != nullptr) { // 상품 정보가 존재할 때
		cout << setw(30) << left << to_string(product->GetProdID()) + \
			'(' + product->GetProdName() + ')';
	}
	else { // 상품 정보가 존재하지 않을 때
		cout << setw(30) << left << "상품 정보 없음";
	}

	/* 주문수량 */
	cout << setw(12) << left << order->GetOrderProdNum();

	/* 주문금액 */
	if (product != nullptr) { // 상품 정보가 존재할 때
		cout << setw(10) << left << order->GetOrderProdNum() * product->GetProdPrice() << endl;
	}
	else { // 상품 정보가 존재하지 않을 때
		cout << setw(10) << left << "상품 정보 없음" << endl;
	}
}


/**
* @brief 한 개의 주문 내역 출력 (2행)
* @param Order* order 한 개의 주문 내역
*/
void OrderHandler::ShowOrderInfoRow2(Order* order) const
{
	/* 고객ID(이름), 전화번호, 주소 */
	Client* client = cltHandler.SearchCltUsingId(order->GetOrderCltID());

	if (client != nullptr) { // 고객 정보가 존재할 때
		cout << setw(16) << left << to_string(client->GetCltID()) + \
			'(' + client->GetCltName() + ')';
		cout << setw(15) << left << client->GetCltPhoneNumber();
		cout << setw(30) << left << client->GetCltAddress() << endl;
	}
	else { // 고객 정보가 존재하지 않을 때
		cout << setw(16) << left << "고객 정보 없음" << endl;
	}
}


/**
* @brief 주문 내역 삭제
* @param Order* order 주문 내역
*/
void OrderHandler::DeleteOrderUsingPtr(Order* order)
{
	/* 주문 내역 삭제 */
	int num = order->GetOrderNum();
	delete orderList.at(num);
	orderList.erase(num);
}


/**
* @brief 중복되지 않는 주문번호 생성
* @return int 생성한 주문번호 반환
*/
int OrderHandler::MakeOrderNum()
{
	/* 중복되지 않는 주문번호 생성 */
	auto key = orderList.end();
	if (orderList.size() == 0) {
		// 기존에 저장된 주문내역이 한 개도 없을 때
		return 10001; // 주문번호는 10001부터 시작
	}
	else {
		// 기존에 저장된 주문내역이 있을 때
		// 가장 마지막 주문번호보다 +1만큼 큰 숫자를 반환
		int num = (--key)->first;
		return ++num;
	}
}


/**
* @brief 올바른 날짜 입력 받기
* @return string 입력 받은 날짜 반환
* @exception -1이 입력되면 입력 중단
*/
string OrderHandler::GetDateString()
{
	string strDate;	// string 형식날짜
	int intDate; // int 형식날짜
	int day, month, year; // 일, 월, 년 분리

	cout << "주문일자를 입력하세요(ex 20220907): ";

	while (1) {
		// 먼저 int형으로 날짜 입력 받기
		intDate = GetInt::GetInteger();

		if (intDate == -1)
			throw - 1; // -1이 입력되면 입력이 중단되도록 예외를 던짐

		// 년, 월, 일로 분리
		year = intDate / 10000;
		month = (intDate - (year * 10000)) / 100;
		day = intDate % 100;

		// 날짜 유효성 검사
		if (CheckValidDate(year, month, day)) {
			// 유효한 날짜이면 string형으로 변경
			strDate = to_string(year) + '-';
			if (month < 10) strDate += '0';
			strDate += to_string(month) + '-';
			if (day < 10) strDate += '0';
			strDate += to_string(day);
			return strDate;
		}
		else // 유효하지 않은 날짜이면
			cout << "유효하지 않은 날짜입니다. 다시 입력하세요: ";
	}
}


/**
* @brief 날짜 유효성 검사
* @param int year 입력한 년
* @param int month 입력한 월
* @param int day 입력한 일
* @return bool 유효한 날짜인지 true/false
*/
bool OrderHandler::CheckValidDate(int year, int month, int day)
{
	/* 유효한 날짜인지 검사 */

	/* 년도 검사 */
	if (year < 1900 || year>2999) // 1900~2999년
		return false;

	/* 월,일 검사 */
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
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) { // 윤년
					if (day < 1 || day>29)
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


/**
* @brief 등록된 고객ID 입력받기
* @return int 입력 받은 고객ID 반환
* @exception -1이 입력되면 입력 중단
*/
int OrderHandler::GetCltID()
{
	/* 등록된 고객ID 입력받기 */
	int id;
	cout << "고객ID를 입력하세요: ";

	while (1) {
		id = GetInt::GetInteger();

		if (id == -1)
			// -1이 입력되면 입력이 중단되도록 예외를 던짐
			throw - 1;

		if (cltHandler.SearchCltUsingId(id) != nullptr)
			// 등록된 고객ID일 때
			return id;
		else
			// 등록된 고객ID가 아닐 때
			cout << "등록되지 않은 고객ID입니다. 다시 입력하세요: ";
	}
}


/**
* @brief 등록된 상품ID 입력받기
* @return int 입력 받은 상품ID 반환
* @exception -1이 입력되면 입력 중단
*/
int OrderHandler::GetProdID()
{
	/* 등록된 상품ID 입력받기 */
	int id;
	cout << "상품ID를 입력하세요: ";

	while (1) {
		id = GetInt::GetInteger();

		if (id == -1)
			// -1이 입력되면 입력이 중단되도록 예외를 던짐
			throw - 1;

		if (prodHandler.SearchProdUsingId(id) != nullptr)
			// 등록된 상품ID일 때
			return id;
		else
			// 등록된 상품ID가 아닐 때
			cout << "등록되지 않은 상품ID입니다. 다시 입력하세요: ";
	}
}


/**
* @brief 주문수량 입력받기
* @return int 입력 받은 상품ID 반환
* @exception -1이 입력되면 입력 중단
*/
int OrderHandler::GetProdNum(int prodID)
{		
	/* 상품 정보 가져오기 */
	Product* product = prodHandler.SearchProdUsingId(prodID);
	int stock = product->GetProdStock();

	/* 주문 수량 입력 받기 */
	int prodNum;
	cout << "주문수량을 입력하세요" << "(재고: " << stock << "): ";
	while (1) {
		// -1 이상의 숫자만 입력 받기
		prodNum = GetInt::GetInteger(-1, INT_MAX);

		if (prodNum == -1)
			// -1이 입력되면 입력이 중단되도록 예외를 던짐
			throw - 1;

		if (stock >= prodNum) {

			product->SetProdStock(stock - prodNum); // 재고 변경 즉시 반영
			return prodNum;
		}
		else // 재고가 부족할 때
			cout << "재고가 부족합니다. 다시 입력하세요" << "(재고: " << stock << "): ";
	}
}


/**
* @brief 상품ID 변경하기
* @param Order* order 변경할 주문내역
*/
void OrderHandler::ChangeProdID(Order* order)
{
	/* 변경 전 상품ID */
	int oldProdID = order->GetOrderProdID();
	/* 변경 전 주문수량 */
	int oldProdNum = order->GetOrderProdNum();
	/* 변경 전 상품 정보 */
	Product* oldProduct = prodHandler.SearchProdUsingId(oldProdID);
	/* 변경할 상품ID 입력 받기 */
	int newProdID = GetProdID();
	/* 변경할 주문수량 입력 받기 */
	int newProdNum = GetProdNum(newProdID);

	/* 새로운 상품ID와 주문수량 설정 */
	order->SetOrderProdID(newProdID);
	order->SetOrderProdNum(newProdNum);

	if (oldProduct == nullptr) // 변경 전에 대한 상품 정보가 존재하지 않다면
		return;
	else { // 변경 전에 대한 상품 정보가 존재한다면
		cout << "변경 전 상품에 대한 재고를 다시 추가하시겠습니까?(y/n): ";
		while (1) {
			/* y 또는 n 선택 */
			string input; 	cin >> input;

			if (input == "y" || input == "Y") { // 변경 전 상품에 대한 재고를 다시 추가
				oldProduct->SetProdStock(oldProduct->GetProdStock() + oldProdNum);
				return;
			}
			else if (input == "n" || input == "N") // 재고 추가 안하기
				return;
			else
				cout << "다시 입력하세요: ";
		}
	}
}


/**
* @brief 주문수량 변경하기
* @param Order* order 변경할 주문내역
* @exception -1이 입력되면 입력 중단 
*/
void OrderHandler::ChangeProdNum(Order* order)
{
	/* 현재 상품 정보 */
	Product* product = prodHandler.SearchProdUsingId(order->GetOrderProdID());
	/* 현재 상품의 재고를 가져오기 */
	int stock = product->GetProdStock();
	/* 변경 전 주문수량 */
	int oldProdNum = order->GetOrderProdNum();

	/* 변경할 주문수량 입력 받기 */
	cout << "주문수량을 입력하세요" << "(최대: " << stock + oldProdNum << "): ";
	while (1) {
		// -1 이상의 숫자만 입력 받기
		int newProdNum = GetInt::GetInteger(-1, INT_MAX);

		if (newProdNum == -1)
			// -1이 입력되면 입력이 중단되도록 예외를 던짐
			throw - 1;

		if (stock + oldProdNum >= newProdNum) {  // 재고가 충분할 때
			// 재고 변경 즉시 반영
			product->SetProdStock(stock + oldProdNum - newProdNum);
			// 주문수량 변경
			order->SetOrderProdNum(newProdNum);
			return;
		}
		else // 재고가 부족할 때
			cout << "재고가 부족합니다. 다시 입력하세요" << "(최대: " << stock + oldProdNum << "): ";
	}
}


/**
* @brief CSV 형식 파일의 내용을 한 행씩 가져오기
* @param istream& file 가져올 내용이 들어있는 파일
* @param char delimiter 구분 문자
* @return vector<string> 한 행을 반환
*/
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