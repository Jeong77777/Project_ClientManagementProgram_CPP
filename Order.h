#ifndef __ORDER_H__
#define __ORDER_H__

#include <string>
using namespace std;

class Order {
public:
	Order(int = 0, string = "0000-00-00", int = 0, int = 0, int = 0);

	int GetOrderNum() const;

	string GetOrderDate() const;
	void SetOrderDate(string&);	

	int GetOrderCltID() const;
	void SetOrderCltID(int&);

	int GetOrderProdID() const;
	void SetOrderProdID(int&);

	int GetOrderProdNum() const;
	void SetOrderProdNum(int&);

private:
	int orderNum;		// 주문번호
	string orderDate;       // 주문일자
	int orderCltID;      // 고객ID
	int orderProdID;     // 상품ID
	int orderProdNum;    // 주문수량
};
#endif          // __ORDER_H__