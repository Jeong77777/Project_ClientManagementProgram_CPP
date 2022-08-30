// 미완성

#ifndef __SALES_HISTORY_H__
#define __SALES_HISTORY_H__

#include <string>
using namespace std;

class SalesHistory {
public:
	SalesHistory(int, int, int, int, int);

	int getSaleDate() const;
	void setSaleDate(int&);

	int getSaleNumber() const;
	void setSaleNumber(int&);

	int getSaleCltID() const;
	void setSaleCltID(int&);

	int getSaleProdID() const;
	void setSaleProdID(int&);

	int getSaleProdPrice() const;
	void setSaleProdPrice(int&);

	int getSaleProdNum() const;
	void setSaleProdNum(int&);

private:
	int saleDate;       // 판매일자
	int saleNumber;		// 주문번호
	int saleCltID;      // 고객ID
	int saleProdID;     // 상품ID
	int saleProdPrice;  // 판매가격
	int saleProdNum;    // 판매수량
};
#endif          // __SALES_HISTORY_H__