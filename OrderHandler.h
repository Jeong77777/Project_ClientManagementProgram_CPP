#ifndef __ORDER_HANDLER_H__
#define __ORDER_HANDLER_H__

#include "Order.h"
#include "ClientHandler.h"
#include "ProductHandler.h"
#include <map>
#include <vector>


/**
* @brief 주문 내역을 관리하는 클래스
* @details 고객 정보, 상품 정보와의 연동을 위해서
*	멤버 변수로 ClientHandler, ProductHandler 객체를 참조형으로 포함하고 있다.
*/
class OrderHandler
{
public:
	OrderHandler(ClientHandler&, ProductHandler&);
	~OrderHandler();

	void ShowOrderMenu() const;
	void AddOrderMenu();
	void SearchOrderMenu();
	void SearchOrderUsingNumMenu();
	void SearchOrderUsingCltIdMenu();
	void SearchOrderUsingProdIdMenu();
	void SearchOrderUsingDateMenu();
	void ShowAllOrderInfoMenu();
	void SelectInSearchMenu(vector<Order*>&);
	void OrderDeleteModifyMenu(Order*);
	void ModifyOrderMenu(Order*);	

	Order* SearchOrderUsingNum(int) const;	
	vector<Order*> SearchOrderUsingCltId(int) const;
	vector<Order*> SearchOrderUsingProdId(int) const;
	vector<Order*> SearchOrderUsingDate(string) const;
	void ShowSearchResult(Order*) const;
	void ShowSearchResults(vector<Order*>&) const;
	void ShowOrderInfoRow1(Order*) const;
	void ShowOrderInfoRow2(Order*) const;
	void DeleteOrderUsingPtr(Order*);

	int MakeOrderNum();
	string GetDateString();
	bool CheckValidDate(int, int, int);
	int GetCltID();
	int GetProdID();
	int GetProdNum(int);
	void ChangeProdID(Order*);
	void ChangeProdNum(Order*);

	vector<string> parseCSV(istream&, char);

private:
	map<int, Order*> orderList; // 구매 내역 리스트
	ClientHandler& cltHandler; // 고객 정보 관리 객체
	ProductHandler& prodHandler; // 상품 정보 관리 객체
};

#endif // __ORDER_HANDLER_H__
