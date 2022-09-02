#include "Order.h"


Order::Order(int num, string date, int cltID, int prodID, int prodNum)
	: orderNum(num), orderDate(date), orderCltID(cltID), orderProdID(prodID), orderProdNum(prodNum)
{
}

int Order::GetOrderNum() const
{
	return orderNum;
}

string Order::GetOrderDate() const
{
	return orderDate;
}

void Order::SetOrderDate(int& date)
{
	orderDate = date;
}

int Order::GetOrderCltID() const
{
	return orderCltID;
}

void Order::SetOrderCltID(int& cltID)
{
	orderCltID = cltID;
}

int Order::GetOrderProdID() const
{
	return orderProdID;
}

void Order::SetOrderProdID(int& prodID)
{
	orderProdID = prodID;
}

int Order::GetOrderProdNum() const
{
	return orderProdNum;
}

void Order::SetOrderProdNum(int& prodNum)
{
	orderProdNum = prodNum;
}