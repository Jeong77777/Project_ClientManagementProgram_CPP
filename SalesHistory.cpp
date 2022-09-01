// ¹Ì¿Ï¼º 
#include "SalesHistory.h"


SalesHistory::SalesHistory(int data, int cltID, int prodID, int prodPrice, int prodNum)
	: saleDate(data), saleCltID(cltID), saleProdID(prodID), saleProdPrice(prodPrice), saleProdNum(prodNum)
{
	saleNumber = 0;
}

int SalesHistory::GetSaleDate() const
{
	return saleDate;
}

void SalesHistory::SetSaleDate(int& date)
{
	saleDate = date;
}

int SalesHistory::GetSaleNumber() const
{
	return saleNumber;
}

void SalesHistory::SetSaleNumber(int& number)
{
	saleNumber = number;
}

int SalesHistory::GetSaleCltID() const
{
	return saleCltID;
}

void SalesHistory::SetSaleCltID(int& cltID)
{
	saleCltID = cltID;
}

int SalesHistory::GetSaleProdID() const
{
	return saleProdID;
}

void SalesHistory::SetSaleProdID(int& prodID)
{
	saleProdID = prodID;
}

int SalesHistory::GetSaleProdPrice() const
{
	return saleProdPrice;
}

void SalesHistory::SetSaleProdPrice(int& prodPrice)
{
	saleProdPrice = prodPrice;
}

int SalesHistory::GetSaleProdNum() const
{
	return saleProdNum;
}

void SalesHistory::SetSaleProdNum(int& prodNum)
{
	saleProdNum = prodNum;
}