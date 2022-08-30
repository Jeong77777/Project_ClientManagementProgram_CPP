// �̿ϼ�

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
	int saleDate;       // �Ǹ�����
	int saleNumber;		// �ֹ���ȣ
	int saleCltID;      // ��ID
	int saleProdID;     // ��ǰID
	int saleProdPrice;  // �ǸŰ���
	int saleProdNum;    // �Ǹż���
};
#endif          // __SALES_HISTORY_H__