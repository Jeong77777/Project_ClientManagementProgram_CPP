#ifndef __PRODUCT_HANDLER_H__
#define __PRODUCT_HANDLER_H__

#include "Product.h"
#include <map>
#include <vector>

class ProductHandler
{
public:
	ProductHandler();
	~ProductHandler();

	void ShowProdMenu() const;
	void AddProdMenu();
	void SearchProdMenu();
	void SearchProdUsingIdMenu();
	void ModifyProdMenu(Product*);
	void SearchProdUsingNameMenu();	
	void ProdDeleteModifyMenu(Product*);
	void SelectInSearchMenu(vector<Product*>&);
	void SearchProdUsingClasMenu();
	void ShowAllProdInfoMenu();

	Product* SearchProdUsingId(int) const;
	void DeleteProdUsingPtr(Product*);	
	vector<Product*> SearchProdUsingName(string) const;
	void ShowSearchResult(Product*) const;
	void ShowSearchResults(vector<Product*>&) const;
	vector<Product*> SearchProdUsingClas(int) const;

	int MakeProdId();
	int GetProdClasif();
	vector<string> parseCSV(istream&, char);

private:
	map<int, Product*> productList;

};

#endif // __PRODUCT_HANDLER_H__

