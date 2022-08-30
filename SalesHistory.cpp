// ¹Ì¿Ï¼º

#include "SalesHistory.h"


SalesHistory::SalesHistory(int data, int cltID, int prodID, int prodPrice, int prodNum)
	: saleDate(data), saleCltID(cltID), saleProdID(prodID), saleProdPrice(prodPrice), saleProdNum(prodNum)
{
	saleNumber = 0;
}

int SalesHistory::getSaleDate() const
{
	return saleDate;
}

void SalesHistory::setSaleDate(int& date)
{
	saleDate = date;
}

int SalesHistory::getSaleNumber() const
{
	return saleNumber;
}

void SalesHistory::setSaleNumber(int& number)
{
	saleNumber = number;
}

int SalesHistory::getSaleCltID() const
{
	return saleCltID;
}

void SalesHistory::setSaleCltID(int& cltID)
{
	saleCltID = cltID;
}

int SalesHistory::getSaleProdID() const
{
	return saleProdID;
}

void SalesHistory::setSaleProdID(int& prodID)
{
	saleProdID = prodID;
}

int SalesHistory::getSaleProdPrice() const
{
	return saleProdPrice;
}

void SalesHistory::setSaleProdPrice(int& prodPrice)
{
	saleProdPrice = prodPrice;
}

int SalesHistory::getSaleProdNum() const
{
	return saleProdNum;
}

void SalesHistory::setSaleProdNum(int& prodNum)
{
	saleProdNum = prodNum;
}