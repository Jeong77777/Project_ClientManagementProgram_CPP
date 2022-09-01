#ifndef __CLIENT_HANDLER_H__
#define __CLIENT_HANDLER_H__

#include "Client.h"
#include <map>
#include <vector>


class ClientHandler
{
public:
	void ShowClientMenu() const;
	void AddClientMenu();
	void SearchClientMenu();
	void SearchCltUsingIdMenu();
	void SearchCltUsingNameMenu();
	void ModifyClientMenu(Client*);
	void SelectInSearchMenu(vector<Client*>&);
	void ClientDeleteModifyMenu(Client*);
	void ShowAllCltInfoMenu();

	void DeleteCltUsingPtr(Client*);
	Client* SearchCltUsingId(int id) const;
	vector<Client*> SearchCltUsingName(string) const;
	void ShowSearchResult(Client*) const;
	void ShowSearchResults(vector<Client*>&) const;
	void ShowAllCltInfo() const;

	int MakeClientId();

private:
	map<int, Client*> clientList;

};

#endif // __CLIENT_HANDLER_H__