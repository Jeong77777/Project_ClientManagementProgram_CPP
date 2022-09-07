#ifndef __GENERIC_HANDLER_H__
#define __GENERIC_HANDLER_H__

#include "ClientHandler.h"
#include "ProductHandler.h"
#include "OrderHandler.h"
#include <iostream>


/**
* @brief �Ѱ� Ŭ����
*/
class GenericHandler
{
public:
	GenericHandler();
	void ShowGenMenu() const;
	void CltMenu();
	void ProdMenu();
	void OrderMenu();

private:
	ClientHandler cltHandler; // �� ���� ����
	ProductHandler prodHandler; // ��ǰ ���� ����
	OrderHandler orderHandler; // �ֹ� ���� ����
};

#endif // __GENERIC_HANDLER_H__
