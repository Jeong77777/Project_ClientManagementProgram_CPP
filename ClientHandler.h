#ifndef __CLIENT_HANDLER_H__
#define __CLIENT_HANDLER_H__

#include "Client.h"
#include <map>
#include <vector>

/**
* @brief 고객 정보를 관리하는 클래스
*/
class ClientHandler
{
public:
	ClientHandler();
	~ClientHandler();

	void ShowClientMenu() const;
	void AddClientMenu();
	void SearchClientMenu();
	void SearchCltUsingIdMenu();
	void SearchCltUsingNameMenu();
	void ShowAllCltInfoMenu();
	void SelectInSearchMenu(vector<Client*>&);
	void ClientDeleteModifyMenu(Client*);
	void ModifyClientMenu(Client*);	

	Client* SearchCltUsingId(int) const;
	vector<Client*> SearchCltUsingName(string) const;
	void ShowSearchResult(Client*) const;
	void ShowSearchResults(vector<Client*>&) const;
	void DeleteCltUsingPtr(Client*);

	int MakeClientId();
	string GetCltPhoneNum();
	string GetCltName();
	string GetCltAddress();
	bool IsValidPhoneNum(string);

	vector<string> parseCSV(istream&, char);

private:
	map<int, Client*> clientList; // 고객 정보 리스트

};

#endif // __CLIENT_HANDLER_H__