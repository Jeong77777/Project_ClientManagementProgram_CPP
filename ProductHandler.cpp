#include "ProductHandler.h"
#include "Line.h"
#include "GetInteger.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>


/**
* @brief productlist.txt 파일을 열어서 저장된 상품 리스트를 가져옴
*/
ProductHandler::ProductHandler()
{
	ifstream file;
	file.open("productlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = stoi(row[0]); // 상품ID
				int classif = stoi(row[1]); // 상품종류
				int stock = stoi(row[3]); // 재고수량
				int price = stoi(row[4]); // 상품가격
				// (상품ID, 상품종류, 이름, 재고수량, 가격)
				Product* p = new Product(id, classif, row[2], stock, price);
				productList.insert({ id, p });
			}
		}
	}
	file.close();
}


/**
* @brief 상품 리스트를 productlist.txt에 저장
*/
ProductHandler::~ProductHandler()
{
	ofstream file;
	file.open("productlist.txt");
	if (!file.fail()) {
		for (const auto& v : productList) {
			Product* p = v.second;
			// (상품ID, 상품종류, 이름, 재고수량, 가격)
			file << p->GetProdID() << ", " << p->GetProdClassif() << ", ";
			file << p->GetProdName() << ", " << p->GetProdStock() << ", ";
			file << p->GetProdPrice() << endl;
			delete p; // 메모리 할당을 해제
		}
	}
	file.close();
}


/**
* @brief 상품 정보 관리 메뉴를 출력
*/
void ProductHandler::ShowProdMenu() const
{
	/* 상품 정보 관리 메뉴 출력 */
	cout << LINE80 << endl;
	cout << "\t\t\t\t상품 정보 관리" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  상품 등록" << endl;
	cout << "\t\t\t\t2.  상품 조회(삭제, 변경)" << endl;
	cout << "\t\t\t\t3.  처음으로" << endl;
	cout << LINE80 << endl;
}


/**
* @brief 상품 등록 메뉴
*/
void ProductHandler::AddProdMenu()
{
	/* 상품 정보 입력 받기 */
	try {
		cout << LINE80 << endl;
		cout << "\t\t\t\t상품 등록" << endl;
		cout << LINE80 << endl;
		cout << "나가시려면 -1을 입력하세요.\n" << endl;

		int id = GetProdId(); // 상품ID
		int classif = GetProdClasif(); // 상품종류
		string name = GetProdName(); // 이름
		int stock = GetProdStock(); // 재고수량
		int price = GetProdPrice();	// 가격	

		/* productList에 상품 추가 */
		Product* newProduct = new Product(id, classif, name, stock, price);
		productList.insert({ id, newProduct });
		cout << "\n상품 등록 완료!\n" << endl;
	}
	catch (int cancel) { // -1을 입력하면 등록을 취소한다.
		if (cancel == -1)
			cout << "\n등록을 취소합니다.\n" << endl;
	}

	cout << "메뉴로 돌아가기 (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}


/**
* @brief 상품 조회(삭제, 변경) 메뉴 출력
*/
void ProductHandler::SearchProdMenu()
{
	/* 상품 조회 메뉴 출력 */
	cout << LINE80 << endl;
	cout << "\t\t\t\t상품 조회(삭제, 변경)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  상품ID로 조회" << endl;
	cout << "\t\t\t\t2.  상품명으로 조회" << endl;
	cout << "\t\t\t\t3.  상품 종류별 조회" << endl;
	cout << "\t\t\t\t4.  전체 상품 조회" << endl;
	cout << "\t\t\t\t5.  이전 메뉴" << endl;
	cout << LINE80 << endl;

	/* 상품 조회 메뉴 선택 */
	cout << "메뉴를 선택하세요: ";
	int sel = GetInt::GetInteger(1, 5);

	if (sel == 1) // 상품ID로 조회
		SearchProdUsingIdMenu();
	else if (sel == 2) // 상품명으로 조회
		SearchProdUsingNameMenu();
	else if (sel == 3) // 상품 종류별 조회
		SearchProdUsingClasMenu();
	else if (sel == 4) // 전체 상품 조회
		ShowAllProdInfoMenu();
	else // 이전 메뉴
		system("cls");
}


/**
* @brief 상품ID로 조회 메뉴
*/
void ProductHandler::SearchProdUsingIdMenu()
{
	/* 검색할 상품ID 입력 받기 */
	cout << "상품ID를 입력하세요(나가기 -1): ";
	int id = GetInt::GetInteger();
	if (id == -1) { // -1이면 나가기
		system("cls");
		return;
	}

	/* 상품ID를 이용하여 검색하고 결과 가져오기 */
	Product* product = SearchProdUsingId(id);

	/* 검색한 상품 정보 출력 */
	ShowSearchResult(product);

	/* 삭제/변경 메뉴 호출 */
	if (product != nullptr)
		ProdDeleteModifyMenu(product);
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}


/**
* @brief 이름으로 조회 메뉴
*/
void ProductHandler::SearchProdUsingNameMenu()
{
	/* 검색할 상품이름 입력 받기 */
	string name;
	cout << "상품명을 입력하세요(나가기 -1): "; cin >> name;
	if (name == "-1") { // -1이면 나가기
		system("cls");
		return;
	}

	/* 검색 결과 가져오기 */
	vector<Product*> searchResults = SearchProdUsingName(name);

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
* @brief 상품 종류별 조회 메뉴
*/
void ProductHandler::SearchProdUsingClasMenu()
{	
	try {
		/* 검색할 상품 종류 선택 하기 */
		cout << "나가시려면 -1을 입력하세요." << endl;
		int classif = GetProdClasif();

		/* 검색 결과 가져오기 */
		vector<Product*> searchResults = SearchProdUsingClas(classif);

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
	catch (int cancel) { // -1이면 검색 취소
		if (cancel == -1) {
			system("cls");
			return;
		}
	}
}


/**
* @brief 전체 상품 조회 메뉴
*/
void ProductHandler::ShowAllProdInfoMenu()
{
	/* 전체 상품 순서대로 가져오기 */
	vector<Product*> allProducts;
	for (auto i = productList.begin(); i != productList.end(); i++)
		allProducts.push_back(i->second);

	/* 전체 상품 정보 출력 */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t전체 상품 조회" << endl;
	ShowSearchResults(allProducts);
	cout << "\n>> 총 " << productList.size() << "개의 상품\n" << endl;
	cout << LINE80 << endl;

	/* 삭제/변경을 위한 선택 메뉴 호출 */
	SelectInSearchMenu(allProducts);
}


/**
* @brief 조회한 상품 정보 리스트에서 상품 정보를 선택
* @param vector<Product*>& list 조회한 상품 정보 리스트
*/
void ProductHandler::SelectInSearchMenu(vector<Product*>& list)
{
	/* 조회한 상품 정보 리스트에서 고객 정보를 선택 */
	int sel;
	if (list.size() != 0) {
		cout << "삭제 또는 변경할 항목을 선택하세요(나가기 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/* 삭제/변경 메뉴 호출 */
			ProdDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}


/**
* @brief 상품 정보 삭제/변경 메뉴
* @param Product* product 삭제/변경할 상품
*/
void ProductHandler::ProdDeleteModifyMenu(Product* product)
{
	/* 삭제/변경/나가기 중에 선택 */
	int sel;
	cout << LINE80 << endl;
	cout << "1. 삭제\t\t2. 변경\t\t3. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "메뉴를 선택하세요: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) { // 삭제
		DeleteProdUsingPtr(product);
		cout << "\n삭제 완료!\n" << endl;
		cout << "메뉴로 돌아가기 (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) { // 변경
		ModifyProdMenu(product);
	}
	else; // 나가기
}


/**
* @brief 상품 정보 변경 메뉴
* @param Product* product 변경할 상품
*/
void ProductHandler::ModifyProdMenu(Product* product)
{
	/* 변경할 상품 정보 선택 */
	cout << LINE80 << endl;
	cout << "1. 상품종류       2. 상품명       3. 재고수량       4. 가격       5. 나가기" << endl;
	cout << LINE80 << endl;
	cout << "변경할 항목을 선택하세요: ";
	int sel = GetInt::GetInteger(1, 5);
	cout << LINE80 << endl;

	try {
		if (sel == 1 || sel == 2 || sel == 3 || sel == 4) {
			cout << "나가시려면 -1을 입력하세요." << endl;
			if (sel == 1) { // 상품종류 변경
				int classif = GetProdClasif();
				product->SetProdClassif(classif);
			}
			else if (sel == 2) { // 상품명 변경
				string name = GetProdName();
				product->SetProdName(name);
			}
			else if (sel == 3) { // 재고수량 변경
				int stock = GetProdStock();
				product->SetProdStock(stock);
			}
			else if (sel == 4) { // 가격 변경
				int price = GetProdPrice();
				product->SetProdPrice(price);
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
* @brief 상품ID를 이용한 상품 검색
* @param int id 검색할 상품ID
* @return Product* 검색된 상품 반환
*/
Product* ProductHandler::SearchProdUsingId(int id) const
{
	/* 상품ID를 이용한 상품 검색 */
	auto i = productList.find(id);

	if (i != productList.end()) // 검색 결과가 존재할 때
		return i->second;
	else // 검색 결과가 존재하지 않을 때
		return nullptr;
}


/**
* @brief 상품명을 이용한 상품 검색
* @param string name 검색할 상품명
* @return vector<Product*> 검색된 상품들 반환
*/
vector<Product*> ProductHandler::SearchProdUsingName(string name) const
{
	/* 상품명을 이용한 상품 검색 */
	vector<Product*> searchResults;

	for (auto i = productList.begin(); i != productList.end(); i++) {
		if (i->second->GetProdName().find(name) != -1)
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief 상품종류별 상품 검색
* @param int classif 검색할 상품종류
* @return vector<Product*> 검색된 상품들 반환
*/
vector<Product*> ProductHandler::SearchProdUsingClas(int classif) const
{
	/* 상품종류별 상품 검색 */
	vector<Product*> searchResults;

	for (auto i = productList.begin(); i != productList.end(); i++) {
		if (classif == i->second->GetProdClassif())
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief 상품ID로 검색한 결과 출력
* @param Product* product 검색된 상품
*/
void ProductHandler::ShowSearchResult(Product* product) const
{
	/* 상품ID로 검색한 결과 출력 */
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

	if (product != nullptr) { // 검색된 것이 존재할 때
		product->ShowProdInfo();
		cout << endl;
	}
	else { // 검색된 것이 존재하지 않을 때
		cout << "\n존재하지 않는 상품ID입니다.\n" << endl;
	}
}



/**
* @brief 검색한 결과들 출력(상품명, 상품종류, 전체 상품으로 조회)
* @param vector<Product*>& searchResults 검색된 상품들 리스트
*/
void ProductHandler::ShowSearchResults(vector<Product*>& searchResults) const
{
	/* 검색한 결과들 출력 */
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


/**
* @brief 상품 정보 삭제
* @param Product* product 고객 정보
*/
void ProductHandler::DeleteProdUsingPtr(Product* product)
{
	/* 상품 정보 삭제 */
	int id = product->GetProdID();
	delete productList.at(id);
	productList.erase(id);
}


/**
* @brief 중복되지 않게 상품ID 입력받기
* @return int 입력받은 상품ID 반환
* @exception -1이 입력되면 입력 중단
*/
int ProductHandler::GetProdId()
{
	/* 상품ID 입력 받기 */
	cout << "상품ID를 입력하세요: ";
	int id;
	while (1) {
		id = GetInt::GetInteger();

		if (id == -1)
			// -1이 입력되면 입력이 중단되도록 예외를 던짐
			throw - 1;
		else if (id < 1000 || id > 9999) {
			// 상품ID는 1001부터 9999까지만 허용한다.
			cout << "1001부터 9999까지의 숫자를 입력하세요: ";
		}
		else if (productList.find(id) != productList.end())
			// 상품ID 중복 검사
			cout << "중복된 상품ID입니다. 다시 입력하세요. ";
		else
			break;
	}
	return id;
}


/**
* @brief 상품명 입력받기
* @return string 입력받은 상품명 반환
* @exception -1이 입력되면 입력 중단
*/
string ProductHandler::GetProdName()
{
	/* 상품명 입력 받기 */
	string name;
	cout << "상품명을 입력하세요: ";
	cin.ignore();	getline(cin, name); // 공백 허용
	if (name == "-1")
		throw - 1; // -1이 입력되면 입력이 중단되도록 예외를 던짐
	else
		return name;
}


/**
* @brief 상품종류 선택 하기
* @return int 선택한 상품종류 반환
* @exception -1이 입력되면 입력 중단
*/
int ProductHandler::GetProdClasif()
{
	/* 상품종류 선택 하기 */
	int classif;
	cout << "상품종류(1. 치과장비  2. 치과재료  3. 위생용품): ";
	while (1) {
		classif = GetInt::GetInteger();
		if (classif == -1)
			throw - 1; // -1이 입력되면 입력이 중단되도록 예외를 던짐
		else if (classif >= 1 && classif <= 3)
			return classif;
		else
			cout << "다시 입력하세요: ";
	}
}


/**
* @brief 재고수량 입력 받기
* @return int 입력 받은 재고수량 반환
* @exception -1이 입력되면 입력 중단
*/
int ProductHandler::GetProdStock()
{	
	/* 재고수량 입력 받기 */
	cout << "재고수량을 입력하세요: ";
	// -1 이상의 숫자만 입력 받는다.
	int stock = GetInt::GetInteger(-1, INT_MAX);
	if (stock == -1)
		throw - 1; // -1이 입력되면 입력이 중단되도록 예외를 던짐
	else
		return stock;
}


/**
* @brief 가격 입력 받기
* @return int 입력 받은 가격 반환
* @exception -1이 입력되면 입력 중단
*/
int ProductHandler::GetProdPrice()
{
	/* 가격 입력 받기 */
	cout << "가격을 입력하세요: ";
	int price = GetInt::GetInteger(-1, INT_MAX);
	// -1 이상의 숫자만 입력 받는다.
	if (price == -1)
		throw - 1; // -1이 입력되면 입력이 중단되도록 예외를 던짐
	else
		return price;
}


/**
* @brief CSV 형식 파일의 내용을 한 행씩 가져오기
* @param istream& file 가져올 내용이 있는 파일
* @param char delimiter 구분 문자
* @return vector<string> 한 행을 반환
*/
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