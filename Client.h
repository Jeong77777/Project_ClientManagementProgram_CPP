#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>
using namespace std;

/**
* @brief �� ������ �����ϴ� Ŭ����
*/
class Client
{
public:
	Client(int = 0, string = "", string = "", string = "");

	int GetCltID() const;

	string GetCltName() const;
	void SetCltName(string);

	string GetCltPhoneNumber() const;
	void SetCltPhoneNumber(string);

	string GetCltAddress() const;
	void SetCltAddress(string);

	void ShowCltInfo() const;

private:
	int cltID;				// ��ID
	string cltName;			// ���̸�
	string cltPhoneNumber;	// ����ȭ��ȣ
	string cltAddress;		// ���ּ�
};
#endif // __CLIENT_H__