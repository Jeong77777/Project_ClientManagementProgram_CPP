#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>
#include <map>
using namespace std;

class Client
{
public:
	Client(int = 0, string = "", string = "", string = "", string = "");

	int getCltId() const;

	string GetCltName() const;
	void SetCltName(string&);

	string GetCltPhoneNumber() const;
	void SetCltPhoneNumber(string&);

	string GetCltAddress() const;
	void SetCltAddress(string&);

	string GetCltEmail() const;
	void SetCltEmail(string& email);

	void ShowCltInfo() const;

private:
	int cltID;				// ��ID
	string cltName;			// ���̸�
	string cltPhoneNumber;	// ����ȭ��ȣ
	string cltAddress;		// ���ּ�
	string cltEmail;		// ���̸���
};
#endif // __CLIENT_H__