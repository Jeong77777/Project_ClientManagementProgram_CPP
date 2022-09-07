#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
using namespace std;

/**
* @brief 상품 정보를 저장하는 클래스
*/
class Product
{
public:
	Product(int = 0, int = 0, string = "", int = 0, int = 0);

	int GetProdID() const;

	string GetProdName() const;
	void SetProdName(string);

	int GetProdPrice() const;
	void SetProdPrice(int);

	int GetProdClassif() const;
	void SetProdClassif(int);

	int GetProdStock() const;
	void SetProdStock(int);

	void ShowProdInfo() const;

private:
	int prodID;       // 상품ID
	int prodClassif;  // 상품종류
	string prodName;  // 상품명
	int prodStock;    // 재고수량
	int prodPrice;    // 상품가격
};
#endif          // __PRODUCT_H__