#include "GenericHandler.h"
#include "Line.h"
#include "GetInteger.h"


/**
* @brief orderHandler 객체가 고객 정보, 상품 정보를 쓰기 위해서
*	 초기화 하는데 ClientHandler, ProductHandler 객체가 쓰이고 있다.
*/
GenericHandler::GenericHandler(): cltHandler(), prodHandler(), orderHandler(cltHandler, prodHandler)
{
}


/**
* @brief 메인 메뉴 출력
*/
void GenericHandler::ShowGenMenu() const
{
	cout << LINE80 << endl;
	cout << "\t\t\t고객 관리 및 상품 관리 프로그램" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  고객 정보 관리" << endl;
	cout << "\t\t\t\t2.  상품 정보 관리" << endl;
	cout << "\t\t\t\t3.  주문 내역 관리" << endl;
	cout << "\t\t\t\t4.  프로그램 종료" << endl;
	cout << LINE80 << endl;
}


/**
* @brief 고객 정보 관리 메뉴
*/
void GenericHandler::CltMenu()
{
	while (1) {
		int sel;
		cltHandler.ShowClientMenu();
		cout << "메뉴를 선택하세요: ";
		sel = GetInt::GetInteger(1, 3);

		if (sel == 1) {	// 신규고객등록
			system("cls");
			cltHandler.AddClientMenu();
		}
		else if (sel == 2) {	// 정보조회삭제변경
			system("cls");
			cltHandler.SearchClientMenu();
		}
		else {				// 처음으로
			system("cls");
			break;
		}
	}
}


/**
* @brief 상품 정보 관리 메뉴
*/
void GenericHandler::ProdMenu()
{
	while (1) {
		int sel;
		prodHandler.ShowProdMenu();
		cout << "메뉴를 선택하세요: ";
		sel = GetInt::GetInteger(1, 3);

		if (sel == 1) {	// 상품등록
			system("cls");
			prodHandler.AddProdMenu();
		}
		else if (sel == 2) {	// 정보조회삭제변경
			system("cls");
			prodHandler.SearchProdMenu();
		}
		else {			// 처음으로
			system("cls");
			break;
		}
	}
}


/**
* @brief 주문 내역 관리 메뉴
*/
void GenericHandler::OrderMenu()
{
	while (1) {
		int sel;
		orderHandler.ShowOrderMenu();
		cout << "메뉴를 선택하세요: ";
		sel = GetInt::GetInteger(1, 3);

		if (sel == 1) {	// 주문내역등록
			system("cls");
			orderHandler.AddOrderMenu();
		}
		else if (sel == 2) {	// 정보조회삭제변경
			system("cls");
			orderHandler.SearchOrderMenu();
		}
		else {			// 처음으로
			system("cls");
			break;
		}
	}
}