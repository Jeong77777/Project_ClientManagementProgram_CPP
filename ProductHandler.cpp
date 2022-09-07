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
* @brief productlist.txt ������ ��� ����� ��ǰ ����Ʈ�� ������
*/
ProductHandler::ProductHandler()
{
	ifstream file;
	file.open("productlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = stoi(row[0]); // ��ǰID
				int classif = stoi(row[1]); // ��ǰ����
				int stock = stoi(row[3]); // ������
				int price = stoi(row[4]); // ��ǰ����
				// (��ǰID, ��ǰ����, �̸�, ������, ����)
				Product* p = new Product(id, classif, row[2], stock, price);
				productList.insert({ id, p });
			}
		}
	}
	file.close();
}


/**
* @brief ��ǰ ����Ʈ�� productlist.txt�� ����
*/
ProductHandler::~ProductHandler()
{
	ofstream file;
	file.open("productlist.txt");
	if (!file.fail()) {
		for (const auto& v : productList) {
			Product* p = v.second;
			// (��ǰID, ��ǰ����, �̸�, ������, ����)
			file << p->GetProdID() << ", " << p->GetProdClassif() << ", ";
			file << p->GetProdName() << ", " << p->GetProdStock() << ", ";
			file << p->GetProdPrice() << endl;
			delete p; // �޸� �Ҵ��� ����
		}
	}
	file.close();
}


/**
* @brief ��ǰ ���� ���� �޴��� ���
*/
void ProductHandler::ShowProdMenu() const
{
	/* ��ǰ ���� ���� �޴� ��� */
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ǰ ���� ����" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ǰ ���" << endl;
	cout << "\t\t\t\t2.  ��ǰ ��ȸ(����, ����)" << endl;
	cout << "\t\t\t\t3.  ó������" << endl;
	cout << LINE80 << endl;
}


/**
* @brief ��ǰ ��� �޴�
*/
void ProductHandler::AddProdMenu()
{
	/* ��ǰ ���� �Է� �ޱ� */
	try {
		cout << LINE80 << endl;
		cout << "\t\t\t\t��ǰ ���" << endl;
		cout << LINE80 << endl;
		cout << "�����÷��� -1�� �Է��ϼ���.\n" << endl;

		int id = GetProdId(); // ��ǰID
		int classif = GetProdClasif(); // ��ǰ����
		string name = GetProdName(); // �̸�
		int stock = GetProdStock(); // ������
		int price = GetProdPrice();	// ����	

		/* productList�� ��ǰ �߰� */
		Product* newProduct = new Product(id, classif, name, stock, price);
		productList.insert({ id, newProduct });
		cout << "\n��ǰ ��� �Ϸ�!\n" << endl;
	}
	catch (int cancel) { // -1�� �Է��ϸ� ����� ����Ѵ�.
		if (cancel == -1)
			cout << "\n����� ����մϴ�.\n" << endl;
	}

	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();

	system("cls");
}


/**
* @brief ��ǰ ��ȸ(����, ����) �޴� ���
*/
void ProductHandler::SearchProdMenu()
{
	/* ��ǰ ��ȸ �޴� ��� */
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ǰ ��ȸ(����, ����)" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  ��ǰID�� ��ȸ" << endl;
	cout << "\t\t\t\t2.  ��ǰ������ ��ȸ" << endl;
	cout << "\t\t\t\t3.  ��ǰ ������ ��ȸ" << endl;
	cout << "\t\t\t\t4.  ��ü ��ǰ ��ȸ" << endl;
	cout << "\t\t\t\t5.  ���� �޴�" << endl;
	cout << LINE80 << endl;

	/* ��ǰ ��ȸ �޴� ���� */
	cout << "�޴��� �����ϼ���: ";
	int sel = GetInt::GetInteger(1, 5);

	if (sel == 1) // ��ǰID�� ��ȸ
		SearchProdUsingIdMenu();
	else if (sel == 2) // ��ǰ������ ��ȸ
		SearchProdUsingNameMenu();
	else if (sel == 3) // ��ǰ ������ ��ȸ
		SearchProdUsingClasMenu();
	else if (sel == 4) // ��ü ��ǰ ��ȸ
		ShowAllProdInfoMenu();
	else // ���� �޴�
		system("cls");
}


/**
* @brief ��ǰID�� ��ȸ �޴�
*/
void ProductHandler::SearchProdUsingIdMenu()
{
	/* �˻��� ��ǰID �Է� �ޱ� */
	cout << "��ǰID�� �Է��ϼ���(������ -1): ";
	int id = GetInt::GetInteger();
	if (id == -1) { // -1�̸� ������
		system("cls");
		return;
	}

	/* ��ǰID�� �̿��Ͽ� �˻��ϰ� ��� �������� */
	Product* product = SearchProdUsingId(id);

	/* �˻��� ��ǰ ���� ��� */
	ShowSearchResult(product);

	/* ����/���� �޴� ȣ�� */
	if (product != nullptr)
		ProdDeleteModifyMenu(product);
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}

	system("cls");
}


/**
* @brief �̸����� ��ȸ �޴�
*/
void ProductHandler::SearchProdUsingNameMenu()
{
	/* �˻��� ��ǰ�̸� �Է� �ޱ� */
	string name;
	cout << "��ǰ���� �Է��ϼ���(������ -1): "; cin >> name;
	if (name == "-1") { // -1�̸� ������
		system("cls");
		return;
	}

	/* �˻� ��� �������� */
	vector<Product*> searchResults = SearchProdUsingName(name);

	/* �˻� ��� ��� */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t�˻� ���" << endl;
	ShowSearchResults(searchResults);
	cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
	cout << LINE80 << endl;

	/* ����/������ ���� ���� �޴� ȣ�� */
	SelectInSearchMenu(searchResults);
}


/**
* @brief ��ǰ ������ ��ȸ �޴�
*/
void ProductHandler::SearchProdUsingClasMenu()
{	
	try {
		/* �˻��� ��ǰ ���� ���� �ϱ� */
		cout << "�����÷��� -1�� �Է��ϼ���." << endl;
		int classif = GetProdClasif();

		/* �˻� ��� �������� */
		vector<Product*> searchResults = SearchProdUsingClas(classif);

		/* �˻� ��� ��� */
		system("cls");
		cout << LINE80 << endl;
		cout << "\t\t\t\t�˻� ���" << endl;
		ShowSearchResults(searchResults);
		cout << "\n>> " << searchResults.size() << "���� �˻� ���\n" << endl;
		cout << LINE80 << endl;

		/* ����/������ ���� ���� �޴� ȣ�� */
		SelectInSearchMenu(searchResults);
	}
	catch (int cancel) { // -1�̸� �˻� ���
		if (cancel == -1) {
			system("cls");
			return;
		}
	}
}


/**
* @brief ��ü ��ǰ ��ȸ �޴�
*/
void ProductHandler::ShowAllProdInfoMenu()
{
	/* ��ü ��ǰ ������� �������� */
	vector<Product*> allProducts;
	for (auto i = productList.begin(); i != productList.end(); i++)
		allProducts.push_back(i->second);

	/* ��ü ��ǰ ���� ��� */
	system("cls");
	cout << LINE80 << endl;
	cout << "\t\t\t\t��ü ��ǰ ��ȸ" << endl;
	ShowSearchResults(allProducts);
	cout << "\n>> �� " << productList.size() << "���� ��ǰ\n" << endl;
	cout << LINE80 << endl;

	/* ����/������ ���� ���� �޴� ȣ�� */
	SelectInSearchMenu(allProducts);
}


/**
* @brief ��ȸ�� ��ǰ ���� ����Ʈ���� ��ǰ ������ ����
* @param vector<Product*>& list ��ȸ�� ��ǰ ���� ����Ʈ
*/
void ProductHandler::SelectInSearchMenu(vector<Product*>& list)
{
	/* ��ȸ�� ��ǰ ���� ����Ʈ���� �� ������ ���� */
	int sel;
	if (list.size() != 0) {
		cout << "���� �Ǵ� ������ �׸��� �����ϼ���(������ 0): # ";
		sel = GetInt::GetInteger(0, list.size());
		if (sel != 0)
			/* ����/���� �޴� ȣ�� */
			ProdDeleteModifyMenu(list[sel - 1]);
	}
	else {
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	system("cls");
}


/**
* @brief ��ǰ ���� ����/���� �޴�
* @param Product* product ����/������ ��ǰ
*/
void ProductHandler::ProdDeleteModifyMenu(Product* product)
{
	/* ����/����/������ �߿� ���� */
	int sel;
	cout << LINE80 << endl;
	cout << "1. ����\t\t2. ����\t\t3. ������" << endl;
	cout << LINE80 << endl;
	cout << "�޴��� �����ϼ���: ";
	sel = GetInt::GetInteger(1, 3);

	if (sel == 1) { // ����
		DeleteProdUsingPtr(product);
		cout << "\n���� �Ϸ�!\n" << endl;
		cout << "�޴��� ���ư��� (0): ";
		GetInt::GetOnlyZero();
	}
	else if (sel == 2) { // ����
		ModifyProdMenu(product);
	}
	else; // ������
}


/**
* @brief ��ǰ ���� ���� �޴�
* @param Product* product ������ ��ǰ
*/
void ProductHandler::ModifyProdMenu(Product* product)
{
	/* ������ ��ǰ ���� ���� */
	cout << LINE80 << endl;
	cout << "1. ��ǰ����       2. ��ǰ��       3. ������       4. ����       5. ������" << endl;
	cout << LINE80 << endl;
	cout << "������ �׸��� �����ϼ���: ";
	int sel = GetInt::GetInteger(1, 5);
	cout << LINE80 << endl;

	try {
		if (sel == 1 || sel == 2 || sel == 3 || sel == 4) {
			cout << "�����÷��� -1�� �Է��ϼ���." << endl;
			if (sel == 1) { // ��ǰ���� ����
				int classif = GetProdClasif();
				product->SetProdClassif(classif);
			}
			else if (sel == 2) { // ��ǰ�� ����
				string name = GetProdName();
				product->SetProdName(name);
			}
			else if (sel == 3) { // ������ ����
				int stock = GetProdStock();
				product->SetProdStock(stock);
			}
			else if (sel == 4) { // ���� ����
				int price = GetProdPrice();
				product->SetProdPrice(price);
			}
		}
		else // ������
			return;

		cout << "\n���� �Ϸ�!\n" << endl;
	}
	catch (int cancel) {// -1�̸� ���� ���
		if (cancel == -1)
			cout << "\n������ ����մϴ�.\n" << endl;
	}

	cout << "�޴��� ���ư��� (0): ";
	GetInt::GetOnlyZero();
}


/**
* @brief ��ǰID�� �̿��� ��ǰ �˻�
* @param int id �˻��� ��ǰID
* @return Product* �˻��� ��ǰ ��ȯ
*/
Product* ProductHandler::SearchProdUsingId(int id) const
{
	/* ��ǰID�� �̿��� ��ǰ �˻� */
	auto i = productList.find(id);

	if (i != productList.end()) // �˻� ����� ������ ��
		return i->second;
	else // �˻� ����� �������� ���� ��
		return nullptr;
}


/**
* @brief ��ǰ���� �̿��� ��ǰ �˻�
* @param string name �˻��� ��ǰ��
* @return vector<Product*> �˻��� ��ǰ�� ��ȯ
*/
vector<Product*> ProductHandler::SearchProdUsingName(string name) const
{
	/* ��ǰ���� �̿��� ��ǰ �˻� */
	vector<Product*> searchResults;

	for (auto i = productList.begin(); i != productList.end(); i++) {
		if (i->second->GetProdName().find(name) != -1)
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief ��ǰ������ ��ǰ �˻�
* @param int classif �˻��� ��ǰ����
* @return vector<Product*> �˻��� ��ǰ�� ��ȯ
*/
vector<Product*> ProductHandler::SearchProdUsingClas(int classif) const
{
	/* ��ǰ������ ��ǰ �˻� */
	vector<Product*> searchResults;

	for (auto i = productList.begin(); i != productList.end(); i++) {
		if (classif == i->second->GetProdClassif())
			searchResults.push_back(i->second);
	}

	return searchResults;
}


/**
* @brief ��ǰID�� �˻��� ��� ���
* @param Product* product �˻��� ��ǰ
*/
void ProductHandler::ShowSearchResult(Product* product) const
{
	/* ��ǰID�� �˻��� ��� ��� */
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

	if (product != nullptr) { // �˻��� ���� ������ ��
		product->ShowProdInfo();
		cout << endl;
	}
	else { // �˻��� ���� �������� ���� ��
		cout << "\n�������� �ʴ� ��ǰID�Դϴ�.\n" << endl;
	}
}



/**
* @brief �˻��� ����� ���(��ǰ��, ��ǰ����, ��ü ��ǰ���� ��ȸ)
* @param vector<Product*>& searchResults �˻��� ��ǰ�� ����Ʈ
*/
void ProductHandler::ShowSearchResults(vector<Product*>& searchResults) const
{
	/* �˻��� ����� ��� */
	int cnt = 1;
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
}


/**
* @brief ��ǰ ���� ����
* @param Product* product �� ����
*/
void ProductHandler::DeleteProdUsingPtr(Product* product)
{
	/* ��ǰ ���� ���� */
	int id = product->GetProdID();
	delete productList.at(id);
	productList.erase(id);
}


/**
* @brief �ߺ����� �ʰ� ��ǰID �Է¹ޱ�
* @return int �Է¹��� ��ǰID ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
int ProductHandler::GetProdId()
{
	/* ��ǰID �Է� �ޱ� */
	cout << "��ǰID�� �Է��ϼ���: ";
	int id;
	while (1) {
		id = GetInt::GetInteger();

		if (id == -1)
			// -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
			throw - 1;
		else if (id < 1000 || id > 9999) {
			// ��ǰID�� 1001���� 9999������ ����Ѵ�.
			cout << "1001���� 9999������ ���ڸ� �Է��ϼ���: ";
		}
		else if (productList.find(id) != productList.end())
			// ��ǰID �ߺ� �˻�
			cout << "�ߺ��� ��ǰID�Դϴ�. �ٽ� �Է��ϼ���. ";
		else
			break;
	}
	return id;
}


/**
* @brief ��ǰ�� �Է¹ޱ�
* @return string �Է¹��� ��ǰ�� ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
string ProductHandler::GetProdName()
{
	/* ��ǰ�� �Է� �ޱ� */
	string name;
	cout << "��ǰ���� �Է��ϼ���: ";
	cin.ignore();	getline(cin, name); // ���� ���
	if (name == "-1")
		throw - 1; // -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
	else
		return name;
}


/**
* @brief ��ǰ���� ���� �ϱ�
* @return int ������ ��ǰ���� ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
int ProductHandler::GetProdClasif()
{
	/* ��ǰ���� ���� �ϱ� */
	int classif;
	cout << "��ǰ����(1. ġ�����  2. ġ�����  3. ������ǰ): ";
	while (1) {
		classif = GetInt::GetInteger();
		if (classif == -1)
			throw - 1; // -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
		else if (classif >= 1 && classif <= 3)
			return classif;
		else
			cout << "�ٽ� �Է��ϼ���: ";
	}
}


/**
* @brief ������ �Է� �ޱ�
* @return int �Է� ���� ������ ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
int ProductHandler::GetProdStock()
{	
	/* ������ �Է� �ޱ� */
	cout << "�������� �Է��ϼ���: ";
	// -1 �̻��� ���ڸ� �Է� �޴´�.
	int stock = GetInt::GetInteger(-1, INT_MAX);
	if (stock == -1)
		throw - 1; // -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
	else
		return stock;
}


/**
* @brief ���� �Է� �ޱ�
* @return int �Է� ���� ���� ��ȯ
* @exception -1�� �ԷµǸ� �Է� �ߴ�
*/
int ProductHandler::GetProdPrice()
{
	/* ���� �Է� �ޱ� */
	cout << "������ �Է��ϼ���: ";
	int price = GetInt::GetInteger(-1, INT_MAX);
	// -1 �̻��� ���ڸ� �Է� �޴´�.
	if (price == -1)
		throw - 1; // -1�� �ԷµǸ� �Է��� �ߴܵǵ��� ���ܸ� ����
	else
		return price;
}


/**
* @brief CSV ���� ������ ������ �� �྿ ��������
* @param istream& file ������ ������ �ִ� ����
* @param char delimiter ���� ����
* @return vector<string> �� ���� ��ȯ
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