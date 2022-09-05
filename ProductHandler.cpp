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
				int id = atoi(row[0].c_str());
				int classif = atoi(row[1].c_str());
				int stock = atoi(row[3].c_str());
				int price = atoi(row[4].c_str());
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
	/*** ��ǰ ���� ���� �޴� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ǰ ���� ����" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ǰ ���" << endl;
	cout << "\t\t\t\t2.  ��ǰ ��ȸ(����, ����)" << endl;
	cout << "\t\t\t\t3.  ó������" << endl;
	cout << LINE80 << endl;
}

void ProductHandler::AddProdMenu()
{
	/*** ��ǰ ��� �޴� ***/
	int id;       // ��ǰID
	int classif;  // ��ǰ����
	string name;  // ��ǰ��
	int stock;    // ������
	int price;    // ��ǰ����

	/*** ��ǰ ���� �Է� �ް� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ǰ ���" << endl;
	cout << LINE80 << endl;
	cout << "��ǰID: ";
	id = MakeProdId();
	cout << "��ǰ����(1. ġ�����  2. ġ�����  3. ������ǰ): ";
	classif = GetInt::GetInteger(1, 3);
	cout << "��ǰ��: ";	cin >> name;
	cout << "������: ";
	stock = GetInt::GetInteger();
	cout << "����: ";
	price = GetInt::GetInteger();
	Product* newProduct = new Product(id, classif, name, stock, price);
	productList.insert({ id, newProduct });
	cout << "\n��ǰ ��� �Ϸ�!\n" << endl;

	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}

void ProductHandler::SearchProdMenu()
{
	int sel;

	/*** ��ǰ ��ȸ �޴� ��� ***/
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ǰ ��ȸ(����, ����)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ǰID�� ��ȸ" << endl;
	cout << "\t\t\t\t2.  ��ǰ������ ��ȸ" << endl;
	cout << "\t\t\t\t3.  ��ǰ ������ ��ȸ" << endl;
	cout << "\t\t\t\t4.  ��ü ��ǰ ��ȸ" << endl;
	cout << "\t\t\t\t5.  ���� �޴�" << endl;
	cout << LINE80 << endl;

	/*** ��ǰ ��ȸ �޴� ���� ***/
	cout << "�޴��� �����ϼ���: ";
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
	/*** ��ǰID�� �˻� ***/
	int id;
	Product* product;
	cout << "��ǰID�� �Է��ϼ���: ";
	id = GetInt::GetInteger();
	product = SearchProdUsingId(id);
	ShowSearchResult(product);

	/*** ����/���� �޴� ȣ�� ***/
	if (product != nullptr)
		ProdDeleteModifyMenu(product);
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}

void ProductHandler::ShowSearchResult(Product* client) const
{
	/*** ID�� �˻��� ��� ��� ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE80 << endl;
	cout << setw(8) << left << "��ǰID";
	cout << setw(10) << left << "��ǰ����";
	cout << setw(24) << left << "��ǰ��";
	cout << setw(10) << left << "������";
	cout << setw(10) << left << "����" << endl;
	cout << LINE80 << endl;

	if (client != nullptr) {
		client->ShowProdInfo();
		cout << endl;
	}
	else {
		cout << "\n�������� �ʴ� ��ǰID�Դϴ�.\n" << endl;
	}
}

Product* ProductHandler::SearchProdUsingId(int id) const
{
	/*** ��ǰID�� �˻� ***/
	auto i = productList.find(id);

	if (i != productList.end())
		return i->second;
	else
		return nullptr;
}

void ProductHandler::ProdDeleteModifyMenu(Product* product)
{
	/*** ����/���� �޴� ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. ����\t\t2. ����\t\t3. ������" << endl;
	cout << LINE80 << endl;
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) {
		DeleteProdUsingPtr(product);
		cout << "\n���� �Ϸ�!\n" << endl;
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) {
		ModifyProdMenu(product);
	}
	else;
}

void ProductHandler::ModifyProdMenu(Product* product)
{
	/*** ��ǰ ���� ���� �޴� ***/
	int sel;
	cout << LINE80 << endl;
	cout << "1. ��ǰ����       2. ��ǰ��       3. ������       4. ����       5. ������" << endl;
	cout << LINE80 << endl;
	cout << "������ �׸��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 5);

	cout << LINE80 << endl;
	if (sel == 1) {
		int classif;
		cout << "��ǰ����(1. ġ�����  2. ġ�����  3. ������ǰ): ";
		classif = GetInt::GetInteger(1, 3);
		product->SetProdClassif(classif);
	}
	else if (sel == 2) {
		string name;
		cout << "��ǰ���� �Է��ϼ���: ";
		cin >> name;
		product->SetProdName(name);
	}
	else if (sel == 3) {
		int stock;
		cout << "�������� �Է��ϼ���: ";
		stock = GetInt::GetInteger();
		product->SetProdStock(stock);
	}
	else if (sel == 4) {
		int price;
		cout << "������ �Է��ϼ���: ";
		price = GetInt::GetInteger();
		product->SetProdPrice(price);
	}
	else
		return;	

	cout << "\n���� �Ϸ�!\n" << endl;
	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();
}

void ProductHandler::DeleteProdUsingPtr(Product* product)
{
	/*** ��ǰ ���� ***/
	int id = product->GetProdID();
	delete productList.at(id);
	productList.erase(id);
}

void ProductHandler::SearchProdUsingNameMenu()
{
	/*** ��ǰ������ ��ȸ �޴� ***/
	string name;
	vector<Product*> searchResults;

	cout << "��ǰ���� �Է��ϼ���: "; cin >> name;

	/*** �˻� ��� �������� ***/
	searchResults = SearchProdUsingName(name);
	/*** �˻� ��� ��� ***/
	ShowSearchResults(searchResults);

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(searchResults);
}

vector<Product*> ProductHandler::SearchProdUsingName(string name) const
{
	/*** �̸����� �˻� ***/
	vector<Product*> searchResults;

	for (auto i = productList.begin(); i != productList.end(); i++) {
		if (name == i->second->GetProdName())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void ProductHandler::ShowSearchResults(vector<Product*>& searchResults) const
{
	/*** ��ǰ������ �˻��� ����� ��� ***/
	int cnt = 1;
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	cout << LINE80 << endl;
	cout << setw(10) << left << "��ȣ";
	cout << setw(8) << left << "��ǰID";
	cout << setw(10) << left << "��ǰ����";
	cout << setw(24) << left << "��ǰ��";
	cout << setw(10) << left << "������";
	cout << setw(10) << left << "����" << endl;
	cout << LINE80 << endl;
	for (auto i = searchResults.begin(); i != searchResults.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		(*i)->ShowProdInfo();
		cout << '\n';
		cnt++;
	}
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE80 << endl;
}

void ProductHandler::SelectInSearchMenu(vector<Product*>& list)
{
	/*** �˻� ��Ͽ��� �����ϱ� ***/
	int sel;
	if (list.size() != 0) {
		cout << "���� �Ǵ� ������ �׸��� �����ϼ���(������ 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/*** ����/���� �޴� ���� ***/
			ProdDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}

void ProductHandler::SearchProdUsingClasMenu()
{
	/*** ��ǰ������ ��ȸ �޴� ***/
	int classif;
	vector<Product*> searchResults;

	cout << "��ǰ����(1. ġ�����  2. ġ�����  3. ������ǰ): ";
	classif = GetInt::GetInteger(1, 3);

	/*** �˻� ��� �������� ***/
	searchResults = SearchProdUsingClas(classif);
	/*** �˻� ��� ��� ***/
	ShowSearchResults(searchResults);

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(searchResults);
}

vector<Product*> ProductHandler::SearchProdUsingClas(int classif) const
{
	/*** �̸����� �˻� ***/
	vector<Product*> searchResults;

	for (auto i = productList.begin(); i != productList.end(); i++) {
		if (classif == i->second->GetProdClassif())
			searchResults.push_back(i->second);
	}

	return searchResults;
}

void ProductHandler::ShowAllProdInfoMenu()
{
	/*** ��ü ��ǰ ��ȸ �޴� ***/
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ü ��ǰ ��ȸ" << endl;
	cout << LINE80 << endl;
	cout << setw(10) << left << "��ȣ";
	cout << setw(8) << left << "��ǰID";
	cout << setw(10) << left << "��ǰ����";
	cout << setw(24) << left << "��ǰ��";
	cout << setw(10) << left << "������";
	cout << setw(10) << left << "����" << endl;
	cout << LINE80 << endl;
	ShowAllProdInfo();
	cout << LINE80 << endl;

	/*** ��ü ��ǰ ������� �������� ***/
	vector<Product*> allProducts;
	for (auto i = productList.begin(); i != productList.end(); i++)
		allProducts.push_back(i->second);

	/*** ���� �޴� ���� ***/
	SelectInSearchMenu(allProducts);
}

void ProductHandler::ShowAllProdInfo() const
{
	/*** ��ü ��ǰ ��� ***/
	int cnt = 1;
	for (auto i = productList.begin(); i != productList.end(); i++) {
		cout << setw(2) << left << "# ";
		cout << setw(4) << right << cnt;
		cout << "    ";
		i->second->ShowProdInfo();
		cout << '\n';
		cnt++;
	}
	cout << "\n>> �� " << productList.size() << "���� ��ǰ\n" << endl;
}

int ProductHandler::MakeProdId()
{
	/*** �ߺ����� �ʴ� ID ���� ***/
	int id;
	while (1) {
		id = GetInt::GetInteger();

		if (id < 1000 || id > 9999) {
			cout << "1001���� 9999������ ���ڸ� �Է��ϼ���: ";
		}
		else if (productList.find(id) != productList.end())
			cout << "�ߺ��� ��ǰID�Դϴ�. �ٽ� �Է��ϼ���. ";
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