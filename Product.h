// 미완성

#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
using namespace std;

class Product {
public:
	Product(int, int, string, int, int);

	int getProdID() const;
	void setProdID(int&);

	string getProdName() const;
	void setProdName(string&);

	int getProdPrice() const;
	void setProdPrice(int&);

	int getProdClassif() const;
	void setProdClassif(int&);

	int getProdStock() const;
	void setProdStock(int&);

private:
	int prodID;       // 상품ID
	int prodClassif;  // 상품분류
	string prodName;  // 상품명
	int prodStock;    // 재고수량
	int prodPrice;    // 상품가격


};
#endif          // __PRODUCT_H__