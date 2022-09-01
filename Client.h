#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>
using namespace std;

class Client
{
public:
	Client(int = 0, string = "", string = "", string = "");

	int getCltId() const;

	string GetCltName() const;
	void SetCltName(string&);

	string GetCltPhoneNumber() const;
	void SetCltPhoneNumber(string&);

	string GetCltAddress() const;
	void SetCltAddress(string&);

	void ShowCltInfo() const;

private:
	int cltID;				// 绊按ID
	string cltName;			// 绊按捞抚
	string cltPhoneNumber;	// 绊按傈拳锅龋
	string cltAddress;		// 绊按林家
};
#endif // __CLIENT_H__