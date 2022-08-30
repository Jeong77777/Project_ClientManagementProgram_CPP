#ifndef __GENERIC_HANDLER_H__
#define __GENERIC_HANDLER_H__

#include "ClientHandler.h"
#include <iostream>

class GenericHandler
{
public:
	void ShowMenu() const;
	void CltMenu();

private:
	ClientHandler cltManager;
};


#endif // __GENERIC_HANDLER_H__
