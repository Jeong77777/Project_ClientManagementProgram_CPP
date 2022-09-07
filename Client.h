#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>
using namespace std;

/**
* @brief 고객 정보를 저장하는 클래스
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
	int cltID;				// 고객ID
	string cltName;			// 고객이름
	string cltPhoneNumber;	// 고객전화번호
	string cltAddress;		// 고객주소
};
#endif // __CLIENT_H__