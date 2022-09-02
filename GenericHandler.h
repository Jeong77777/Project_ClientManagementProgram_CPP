#ifndef __GENERIC_HANDLER_H__
#define __GENERIC_HANDLER_H__

#include "ClientHandler.h"
#include "ProductHandler.h"
#include "OrderHandler.h"
#include <iostream>

class GenericHandler
{
public:
	GenericHandler();
	void ShowGenMenu() const;
	void CltMenu();
	void ProdMenu();
	void OrderMenu();

private:
	ClientHandler cltManager;
	ProductHandler prodManager;
	OrderHandler orderManager;
};


#endif // __GENERIC_HANDLER_H__
