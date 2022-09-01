#include "Client.h"
#include <iostream>
#include <iomanip>


Client::Client(int id, string name, string phoneNumber, string address)
	: cltID(id), cltName(name), cltPhoneNumber(phoneNumber), cltAddress(address)
{
}

int Client::getCltID() const
{
	return cltID;
}

string Client::GetCltName() const
{
	return cltName;
}

void Client::SetCltName(string& name)
{
	cltName = name;
}

string Client::GetCltPhoneNumber() const
{
	return cltPhoneNumber;
}

void Client::SetCltPhoneNumber(string& phoneNumber)
{
	cltPhoneNumber = phoneNumber;
}

string Client::GetCltAddress() const
{
	return cltAddress;
}

void Client::SetCltAddress(string& address)
{
	cltAddress = address;
}

void Client::ShowCltInfo() const
{
	cout << setw(8) << left << cltID;
	cout << setw(10) << left << cltName;
	cout << setw(20) << left << cltPhoneNumber;
	cout << setw(30) << left << cltAddress << endl;
}