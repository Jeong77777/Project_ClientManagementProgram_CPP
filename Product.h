#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
using namespace std;

class Product {
public:
	Product(int = 0, int = 0, string = "", int = 0, int = 0);

	int getProdID() const;

	string getProdName() const;
	void setProdName(string&);

	int getProdPrice() const;
	void setProdPrice(int&);

	int getProdClassif() const;
	void setProdClassif(int&);

	int getProdStock() const;
	void setProdStock(int&);

	void ShowProdInfo() const;

private:
	int prodID;       // ��ǰID
	int prodClassif;  // ��ǰ�з�
	string prodName;  // ��ǰ��
	int prodStock;    // ������
	int prodPrice;    // ��ǰ����


};
#endif          // __PRODUCT_H__