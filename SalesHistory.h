// �̿ϼ�

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
	int saleNumber;		// �ֹ���ȣ
	int saleDate;       // �Ǹ�����			
	int saleCltID;      // ��ID
	int saleProdID;     // ��ǰID
	int saleProdPrice;  // �ǸŰ���
	int saleProdNum;    // �Ǹż���
};
#endif          // __SALES_HISTORY_H__