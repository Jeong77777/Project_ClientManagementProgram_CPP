#ifndef __CLIENT_HANDLER_H__
#define __CLIENT_HANDLER_H__

#include "Client.h"
#include <map>
#include <vector>

/**
* @brief �� ������ �����ϴ� Ŭ����
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
	map<int, Client*> clientList; // �� ���� ����Ʈ

};

#endif // __CLIENT_HANDLER_H__