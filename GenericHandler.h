#ifndef __GENERIC_HANDLER_H__
#define __GENERIC_HANDLER_H__

#include "ClientHandler.h"
#include "ProductHandler.h"
#include <iostream>

class GenericHandler
{
public:
	void ShowMenu() const;
	void CltMenu();
	void ProdMenu();

private:
	ClientHandler cltManager;
	ProductHandler prodManager;
};


#endif // __GENERIC_HANDLER_H__
