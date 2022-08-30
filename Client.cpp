#include "Client.h"
#include <iostream>


Client::Client(int id, string name, string phoneNumber, string address, string email)
	: cltID(id), cltName(name), cltPhoneNumber(phoneNumber), cltAddress(address), cltEmail(email)
{
}

int Client::getCltId() const
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

string Client::GetCltEmail() const
{
	return cltEmail;
}

void Client::SetCltEmail(string& email)
{
	cltEmail = email;
}

void Client::ShowCltInfo() const
{
	cout << "고객ID: " << cltID << endl;
	cout << "이름: " << cltName << endl;
	cout << "전화번호: " << cltPhoneNumber << endl;
	cout << "주소: " << cltEmail << endl;
}