// �̿ϼ�

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
	int prodID;       // ��ǰID
	int prodClassif;  // ��ǰ�з�
	string prodName;  // ��ǰ��
	int prodStock;    // ������
	int prodPrice;    // ��ǰ����


};
#endif          // __PRODUCT_H__