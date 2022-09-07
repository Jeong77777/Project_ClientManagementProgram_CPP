#ifndef __PRODUCT_HANDLER_H__
#define __PRODUCT_HANDLER_H__

#include "Product.h"
#include <map>
#include <vector>

/**
* @brief 상품 정보를 관리하는 클래스
*/
class ProductHandler
{
public:
	ProductHandler();
	~ProductHandler();

	void ShowProdMenu() const;
	void AddProdMenu();
	void SearchProdMenu();
	void SearchProdUsingIdMenu();
	void SearchProdUsingNameMenu();
	void SearchProdUsingClasMenu();
	void ShowAllProdInfoMenu();
	void SelectInSearchMenu(vector<Product*>&);
	void ProdDeleteModifyMenu(Product*);
	void ModifyProdMenu(Product*);	

	Product* SearchProdUsingId(int) const;
	vector<Product*> SearchProdUsingName(string) const;
	vector<Product*> SearchProdUsingClas(int) const;	
	void ShowSearchResult(Product*) const;
	void ShowSearchResults(vector<Product*>&) const;
	void DeleteProdUsingPtr(Product*);	

	int GetProdId();
	string GetProdName();	
	int GetProdClasif();
	int GetProdStock();
	int GetProdPrice();

	vector<string> parseCSV(istream&, char);

private:
	map<int, Product*> productList; // 상품 정보 리스트

};

#endif // __PRODUCT_HANDLER_H__

