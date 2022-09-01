#include "ProductHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>

void ProductHandler::ShowMenu() const
{
	/*** 상품 정보 관리 메뉴 출력 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t상품 정보 관리" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  상품 등록" << endl;
	cout << "\t\t\t\t2.  상품 조회(삭제, 변경)" << endl;
	cout << "\t\t\t\t3.  처음으로" << endl;
	cout << LINE80 << endl;
}

void ProductHandler::AddProdMenu()
{
	/*** 상품 등록 메뉴 ***/
	int id;       // 상품ID
	int classif;  // 상품분류
	string name;  // 상품명
	int stock;    // 재고수량
	int price;    // 상품가격

	/*** 상품 정보 입력 받고 등록 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t상품 등록" << endl;
	cout << LINE80 << endl;
	cout << "상품ID: ";
	id = MakeProdId();
	cout << "상품분류(1. 치과장비  2. 치과재료  3. 위생용품): ";
	classif = GetInt::GetIntger(1, 3);
	cout << "상품명: ";	cin >> name;
	cout << "재고수량: ";
	stock = GetInt::GetIntger();
	cout << "가격: ";
	price = GetInt::GetIntger();
	Product* newProduct = new Product(id, classif, name, stock, price);
	ProductList.insert({ id, newProduct });
	cout << "\n상품 등록 완료!\n" << endl;

	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}

void ProductHandler::SearchProdMenu()
{
	int sel;

	/*** 상품 조회 메뉴 출력 ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t상품 조회(삭제, 변경)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  상품ID로 조회" << endl;
	cout << "\t\t\t\t2.  상품명으로 조회" << endl;
	cout << "\t\t\t\t3.  상품 종류별 조회" << endl;
	cout << "\t\t\t\t4.  전체 상품 조회" << endl;
	cout << "\t\t\t\t5.  이전 메뉴" << endl;
	cout << LINE80 << endl;

	/*** 고객 조회 메뉴 선택 ***/
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetIntger(1, 5);

	if (sel == 1)
		SearchProdUsingIdMenu();
	//else if (sel == 2);
	////SearchCltUsingNameMenu();
	//else if (sel == 3);
	////SearchProdUsingClasMenu();
	//else if (sel == 4);
	//	//ShowAllProdInfoMenu();
	//else if (sel == 4);
	//	system("cls");
}

void ProductHandler::SearchProdUsingIdMenu()
{
	/*** 상품ID로 검색 ***/
	int id;
	Product* product;
	cout << "상품ID를 입력하세요(1001부터 9999까지의 숫자): ";
	id = GetInt::GetIntger(1001, 9999);
	product = SearchProdUsingId(id);
	ShowSearchResult(product);
	system("pause");
	/*** 삭제/변경 메뉴 ***/
	if (product != nullptr)
		;//ProdDeleteModifyMenu(product);
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}

void ProductHandler::ShowSearchResult(Product* client) const
{
	/*** ID로 검색한 결과 출력 ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t검색 결과" << endl;
	cout << LINE80 << endl;
	cout << setw(8) << left << "상품ID";
	cout << setw(10) << left << "상품분류";
	cout << setw(20) << left << "상품명";
	cout << setw(10) << left << "재고수량";
	cout << setw(10) << left << "가격" << endl;
	cout << LINE80 << endl;

	if (client != nullptr) {
		client->ShowProdInfo();
		cout << endl;
	}
	else {
		cout << "\n존재하지 않는 고객ID입니다.\n" << endl;
	}
}

Product* ProductHandler::SearchProdUsingId(int id) const
{
	/*** 상품ID로 검색 ***/
	auto i = ProductList.find(id);

	if (i != ProductList.end())
		return i->second;
	else
		return nullptr;
}



int ProductHandler::MakeProdId()
{
	/*** 중복되지 않는 ID 생성 ***/
	int id;
	while (1) {
		id = GetInt::GetIntger();

		if (id < 1000 || id > 10000) {
			cout << "1001부터 9999까지의 숫자를 입력하세요: ";
		}
		else if (ProductList.find(id) != ProductList.end())
			cout << "중복된 상품ID입니다. 다시 입력하세요. ";
		else
			break;
	}
	return id;
}