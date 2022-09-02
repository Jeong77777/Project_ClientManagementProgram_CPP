#include "OrderHandler.h"
#include "GetInteger.h"
#include "Line.h"
#include <iostream>

OrderHandler::OrderHandler(ClientHandler& cltRef, ProductHandler& prodRef)
	:cltManager(cltRef), prodManager(prodRef)
{
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
	string date;	// 주문날짜
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
	cout << "\n주문 내역 등록 완료!\n" << endl;

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
	cout << "\t\t\t\t4.  날짜별 조회" << endl;
	cout << "\t\t\t\t5.  전체 주문 내역 조회" << endl;
	cout << "\t\t\t\t6.  이전 메뉴" << endl;
	cout << LINE80 << endl;

	/*** 상품 조회 메뉴 선택 ***/
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetInteger(1, 5);

	if (sel == 1)
		;//SearchOrderUsingIdMenu();
	else if (sel == 2)
		;//SearchOrderUsingNameMenu();
	else if (sel == 3)
		;//SearchOrderUsingClasMenu();
	else if (sel == 4)
		;//ShowAllOrderInfoMenu();
	else if (sel == 5)
		;//ShowAllOrderInfoMenu();
	else
		system("cls");
}

string OrderHandler::GetDateString()
{
	/*** string형식의 날짜 입력받기 ***/
	string strDate;	// 날짜
	int intDate;
	int day, month, year;

	cout << "주문날짜 입력(ex 20220907): ";

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
			cout << "등록되지 않은 고객ID입니다. 다시 입력하세요 : ";		
	}
}

int OrderHandler::GetProdID()
{
	/*** 등록된 상품ID 입력받기 ***/
	int id;

	cout << "상품ID를 입력하세요: ";
	while (1) {
		id = GetInt::GetInteger();
		if (cltManager.SearchCltUsingId(id) != nullptr)
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
		return 1001;
	}
	else {
		int num = (--key)->first;
		return ++num;
	}
}