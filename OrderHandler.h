#ifndef __ORDER_HANDLER_H__
#define __ORDER_HANDLER_H__

#include "Order.h"
#include "ClientHandler.h"
#include "ProductHandler.h"
#include <map>
#include <vector>

class OrderHandler
{
public:
	OrderHandler(ClientHandler&, ProductHandler&);

	void ShowOrderMenu() const;
	void AddOrderMenu();
	void SearchOrderMenu();
//	void SearchOrderUsingOrderNumMenu();
//	void ModifyOrderMenu(Order*);
//	void SearchProdUsingMonthMenu();
//	void SearchProdUsingDataMenu();
//	void OrderDeleteModifyMenu(Order*);
//	void SelectInSearchMenu(vector<Order*>&);
//	void SearchOrderUsingClasMenu();
//	void ShowAllOrderInfoMenu();
//
//	Order* SearchProdUsingId(int id) const;
//	void DeleteProdUsingPtr(Order*);
//	vector<Order*> SearchProdUsingName(string) const;
//	void ShowSearchResult(Order*) const;
//	void ShowSearchResults(vector<Order*>&) const;
//	vector<Order*> SearchProdUsingClas(int) const;
//	void ShowAllProdInfo() const;
//
	int MakeOrderNum();
	string GetDateString();
	bool CheckValidDate(int, int, int);
	int GetCltID();
	int GetProdID();

private:
	map<int, Order*> orderList;
	ClientHandler& cltManager;
	ProductHandler& prodManager;
};


#endif // __ORDER_HANDLER_H__
