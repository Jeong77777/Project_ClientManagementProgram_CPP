// 미완성

#ifndef __SALES_HISTORY_H__
#define __SALES_HISTORY_H__

#include <string>
using namespace std;

class SalesHistory {
public:
	SalesHistory(int, int, int, int, int);

	int GetSaleDate() const;
	void SetSaleDate(int&);

	int GetSaleNumber() const;
	void SetSaleNumber(int&);

	int GetSaleCltID() const;
	void SetSaleCltID(int&);

	int GetSaleProdID() const;
	void SetSaleProdID(int&);

	int GetSaleProdPrice() const;
	void SetSaleProdPrice(int&);

	int GetSaleProdNum() const;
	void SetSaleProdNum(int&);

private:
	int saleNumber;		// 주문번호
	int saleDate;       // 판매일자			
	int saleCltID;      // 고객ID
	int saleProdID;     // 상품ID
	int saleProdPrice;  // 판매가격
	int saleProdNum;    // 판매수량
};
#endif          // __SALES_HISTORY_H__