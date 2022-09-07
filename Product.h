#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
using namespace std;

/**
* @brief ��ǰ ������ �����ϴ� Ŭ����
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
	int prodID;       // ��ǰID
	int prodClassif;  // ��ǰ����
	string prodName;  // ��ǰ��
	int prodStock;    // ������
	int prodPrice;    // ��ǰ����
};
#endif          // __PRODUCT_H__