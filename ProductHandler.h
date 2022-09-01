#ifndef __PRODUCT_HANDLER_H__
#define __PRODUCT_HANDLER_H__

#include "Product.h"
#include <map>
#include <vector>

class ProductHandler
{
public:
	void ShowMenu() const;
	void AddProdMenu();
	void SearchProdMenu();
	void SearchProdUsingIdMenu();
	//void SearchProdUsingNameMenu();
	//void ModifyProdMenu(Product*);
	//void SelectInSearchMenu(vector<Product*>&);
	//void ProdDeleteModifyMenu(Product*);
	//void ShowAllProdInfoMenu();

	Product* SearchProdUsingId(int id) const;
	//void DeleteProdUsingPtr(Product*);	
	//vector<Product*> SearchProdUsingName(string) const;
	void ShowSearchResult(Product*) const;
	//void ShowSearchResults(vector<Product*>&) const;
	//void ShowAllProdInfo() const;

	int MakeProdId();

private:
	map<int, Product*> ProductList;

};

#endif // __PRODUCT_HANDLER_H__

