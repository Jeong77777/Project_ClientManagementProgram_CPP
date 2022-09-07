#ifndef __ORDER_HANDLER_H__
#define __ORDER_HANDLER_H__

#include "Order.h"
#include "ClientHandler.h"
#include "ProductHandler.h"
#include <map>
#include <vector>


/**
* @brief �ֹ� ������ �����ϴ� Ŭ����
* @details �� ����, ��ǰ �������� ������ ���ؼ�
*	��� ������ ClientHandler, ProductHandler ��ü�� ���������� �����ϰ� �ִ�.
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
	map<int, Order*> orderList; // ���� ���� ����Ʈ
	ClientHandler& cltHandler; // �� ���� ���� ��ü
	ProductHandler& prodHandler; // ��ǰ ���� ���� ��ü
};

#endif // __ORDER_HANDLER_H__
