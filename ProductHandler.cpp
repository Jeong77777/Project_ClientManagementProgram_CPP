#include "ProductHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

ProductHandler::ProductHandler()
{
	ifstream file;
	file.open("productlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = stoi(row[0]);
				int classif = stoi(row[1]);
				int stock = stoi(row[3]);
				int price = stoi(row[4]);
				Product* p = new Product(id, classif, row[2], stock, price);
				productList.insert({ id, p });
			}
		}
	}
	file.close();
}

ProductHandler::~ProductHandler()
{
	ofstream file;
	file.open("productlist.txt");
	if (!file.fail()) {
		for (const auto& v : productList) {
			Product* p = v.second;
			file << p->GetProdID() << ", " << p->GetProdClassif() << ", ";
			file << p->GetProdName() << ", " << p->GetProdStock() << ", ";
			file << p->GetProdPrice() << endl;
			delete p;
		}
	}
	file.close();
}

void ProductHandler::ShowProdMenu() const
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
	int classif;  // 상품종류
	string name;  // 상품명
	int stock;    // 재고수량
	int price;    // 상품가격

	/*** 상품 정보 입력 받고 등록 ***/
	try {
		cout << LINE80 << endl;
		cout << "\t\t\t\t상품 등록" << endl;
		cout << LINE80 << endl;
		cout << "나가시려면 -1을 입력하세요.\n" << endl;
		cout << "상품ID를 입력하세요: ";
		id = MakeProdId();
		classif = GetProdClasif();
		cout << "상품명을 입력하세요: ";	cin >> name;
		if (name == "-1") throw - 1;
		cout << "재고수량을 입력하세요: ";
		stock = GetInt::GetInteger(-1, INT_MAX);
		cout << "가격을 입력하세요: ";
		price = GetInt::GetInteger(-1, INT_MAX);
		if (price == -1) throw - 1;
		Product* newProduct = new Product(id, classif, name, stock, price);
		productList.insert({ id, newProduct });
		cout << "\n상품 등록 완료!\n" << endl;
	}
	catch (int cancel) {
		if (cancel == -1)
			cout << "\n등록을 취소합니다.\n" << endl;
	}

	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}

int ProductHandler::GetProdClasif()
{
	int classif;
	cout << "상품종류(1. 치과장비  2. 치과재료  3. 위생용품): ";
	while (1) {
		classif = GetInt::GetInteger();
		if (classif == -1)
			throw - 1;
		else if (classif >= 1 && classif <= 3)
			return classif;
		else
			cout << "다시 입력하세요: ";
	}
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

	/*** 상품 조회 메뉴 선택 ***/
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetInteger(1, 5);

	if (sel == 1)
		SearchProdUsingIdMenu();
	else if (sel == 2)
		SearchProdUsingNameMenu();
	else if (sel == 3)
		SearchProdUsingClasMenu();
	else if (sel == 4)
		ShowAllProdInfoMenu();
	else
		system("cls");
}

void ProductHandler::SearchProdUsingIdMenu()
{
	/*** 상품ID로 검색 ***/
	int id;
	Product* product;
	cout << "상품ID를 입력하세요(나가기 -1): ";
	id = GetInt::GetInteger();
	if (id == -1) {
		system("cls");
		return;
	}	
	product = SearchProdUsingId(id);
	ShowSearchResult(product);

	/*** 삭제/변경 메뉴 호출 ***/
	if (product != nullptr)
		ProdDeleteModifyMenu(product);
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
	cout << setw(10) << left << "상품종류";
	cout << setw(24) << left << "상품명";
	cout << setw(10) << left << "재고수량";
	cout << setw(10) << left << "가격" << endl;
	cout << LINE80 << endl;

	if (client != nullptr) {
		client->ShowProdInfo();
		cout << endl;
	}
	else {
		cout << "\n존재하지 않는 상품ID입니다.\n" << endl;
	}
}

Product* ProductHandler::SearchProdUsingId(int id) const
{
	/*** 상품ID로 검색 ***/
	auto i = productList.find(id);

	if (i != productList.end())
		return i->second;
	else
		return nullptr;
}

void ProductHandler::ProdDeleteModifyMenu(Product* product)
{
	/*** 삭제/변경 메뉴 ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. 삭제\t\t2. 변경\t\t3. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) {
		DeleteProdUsingPtr(product);
		cout << "\n삭제 완료!\n" << endl;
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) {
		ModifyProdMenu(product);
	}
	else;
}

void ProductHandler::ModifyProdMenu(Product* product)
{
	/*** 상품 정보 변경 메뉴 ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. 상품종류       2. 상품명       3. 재고수량       4. 가격       5. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "변경할 항목을 선택하세요: ";
	sel = GetInt::GetInteger(1, 5);
	cout << LINE80 << endl;
	try {
		if (sel == 1 || sel == 2 || sel == 3 || sel == 4) {
			cout << "나가시려면 -1을 입력하세요." << endl;
			if (sel == 1) {
				int classif;
				classif = GetProdClasif();
				if (classif == -1) throw - 1;
				product->SetProdClassif(classif);
			}
			else if (sel == 2) {
				string name;
				cout << "상품명을 입력하세요: ";
				cin >> name;
				if (name == "-1") throw - 1;
				product->SetProdName(name);
			}
			else if (sel == 3) {
				int stock;
				cout << "재고수량을 입력하세요: ";
				stock = GetInt::GetInteger(-1, INT_MAX);
				if (stock == -1) throw - 1;
				product->SetProdStock(stock);
			}
			else if (sel == 4) {
				int price;
				cout << "가격을 입력하세요: ";
				price = GetInt::GetInteger(-1, INT_MAX);
				if (price == -1) throw - 1;
				product->SetProdPrice(price);
			}
		}		
		else
			return;

		cout << "\n변경 완료!\n" << endl;
	}
	catch (int cancel) {
		if (cancel == -1)
			cout << "\n변경을 취소합니다.\n" << endl;
	}
	
	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();
}

void ProductHandler::DeleteProdUsingPtr(Product* product)
{
	/*** 상품 삭제 ***/
	int id = product->GetProdID();
	delete productList.at(id);
	productList.erase(id);
}

void ProductHandler::SearchProdUsingNameMenu()
{
	/*** 상품명으로 조회 메뉴 ***/
	string name;
	vector<Product*> searchResults;

	cout << "상품명을 입력하세요(나가기 -1): "; cin >> name;
	if (name == "-1") {
		system("cls");
		return;
	}

	/*** 검색 결과 가져오기 ***/
	searchResults = SearchProdUsingName(name);

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

vector<Product*> ProductHandler::SearchProdUsingName(string name) const
{
	/*** 이름으로 검색 ***/
	vector<Product*> searchResults;

	for (auto i = productList.begin(); i != productList.end(); i++) {
		if (i->second->GetProdName().find(name) != -1)
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void ProductHandler::ShowSearchResults(vector<Product*>& searchResults) const
{
	/*** 상품명으로 검색한 결과들 출력 ***/
	int cnt = 1;	
	cout << LINE80 << endl;
	cout << setw(10) << left << "번호";
	cout << setw(8) << left << "상품ID";
	cout << setw(10) << left << "상품종류";
	cout << setw(24) << left << "상품명";
	cout << setw(10) << left << "재고수량";
	cout << setw(10) << left << "가격" << endl;
	cout << LINE80 << endl;

	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		(*i)->ShowProdInfo();
		cout << '\n';
		cnt++;
	}	
}

void ProductHandler::SelectInSearchMenu(vector<Product*>& list)
{
	/*** 검색 목록에서 선택하기 ***/
	int sel;
	if (list.size() != 0) {
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/*** 삭제/변경 메뉴 진입 ***/
			ProdDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}

void ProductHandler::SearchProdUsingClasMenu()
{
	/*** 상품종류로 조회 메뉴 ***/
	int classif;
	vector<Product*> searchResults;

	try {
		cout << "나가시려면 -1을 입력하세요." << endl;
		classif = GetProdClasif();
		/*** 검색 결과 가져오기 ***/
		searchResults = SearchProdUsingClas(classif);

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
	catch (int cancel) {
		if (cancel == -1) {
			system("cls");
			return;
		}		
	}	
}

vector<Product*> ProductHandler::SearchProdUsingClas(int classif) const
{
	/*** 이름으로 검색 ***/
	vector<Product*> searchResults;

	for (auto i = productList.begin(); i != productList.end(); i++) {
		if (classif == i->second->GetProdClassif())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void ProductHandler::ShowAllProdInfoMenu()
{
	/*** 전체 상품 조회 메뉴 ***/

	/*** 전체 상품 순서대로 가져오기 ***/
	vector<Product*> allProducts;
	for (auto i = productList.begin(); i != productList.end(); i++)
		allProducts.push_back(i->second);

	/*** 전체 상품 정보 출력 ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t전체 상품 조회" << endl;
	ShowSearchResults(allProducts);
	cout << "\n>> 총 " << productList.size() << "개의 상품\n" << endl;
	cout << LINE80 << endl;	

	/*** 선택 메뉴 진입 ***/
	SelectInSearchMenu(allProducts);
}

int ProductHandler::MakeProdId()
{
	/*** 상품ID 중복 검사 ***/
	int id;
	while (1) {
		id = GetInt::GetInteger();

		if (id == -1)
			throw - 1;
		else if (id < 1000 || id > 9999) {
			cout << "1001부터 9999까지의 숫자를 입력하세요: ";
		}
		else if (productList.find(id) != productList.end())
			cout << "중복된 상품ID입니다. 다시 입력하세요. ";
		else
			break;
	}
	return id;
}

vector<string> ProductHandler::parseCSV(istream& file, char delimiter)
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