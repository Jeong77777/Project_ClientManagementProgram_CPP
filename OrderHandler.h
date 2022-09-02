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
	void SearchOrderUsingNumMenu();
//	void ModifyOrderMenu(Order*);
//	void SearchProdUsingMonthMenu();
//	void SearchProdUsingDataMenu();
//	void OrderDeleteModifyMenu(Order*);
//	void SelectInSearchMenu(vector<Order*>&);
//	void SearchOrderUsingClasMenu();
//	void ShowAllOrderInfoMenu();
//
	Order* SearchOrderUsingNum(int) const;
//	void DeleteProdUsingPtr(Order*);
//	vector<Order*> SearchProdUsingName(string) const;
	void ShowSearchResult(Order*) const;
//	void ShowSearchResults(vector<Order*>&) const;
	void ShowOrderInfoRow1(Order* order) const;
	void ShowOrderInfoRow2(Order* order) const;
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
