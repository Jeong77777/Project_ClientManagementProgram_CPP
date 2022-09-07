#ifndef __GENERIC_HANDLER_H__
#define __GENERIC_HANDLER_H__

#include "ClientHandler.h"
#include "ProductHandler.h"
#include "OrderHandler.h"
#include <iostream>


/**
* @brief 총괄 클래스
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
	ClientHandler cltHandler; // 고객 정보 관리
	ProductHandler prodHandler; // 상품 정보 관리
	OrderHandler orderHandler; // 주문 내역 관리
};

#endif // __GENERIC_HANDLER_H__
