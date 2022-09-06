#ifndef __CLIENT_HANDLER_H__
#define __CLIENT_HANDLER_H__

#include "Client.h"
#include <map>
#include <vector>


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
	void ModifyClientMenu(Client*);
	void SelectInSearchMenu(vector<Client*>&);
	void ClientDeleteModifyMenu(Client*);
	void ShowAllCltInfoMenu();

	void DeleteCltUsingPtr(Client*);
	Client* SearchCltUsingId(int id) const;
	vector<Client*> SearchCltUsingName(string) const;
	void ShowSearchResult(Client*) const;
	void ShowSearchResults(vector<Client*>&) const;

	int MakeClientId();
	string GetPhoneNumber();
	string GetName();
	string GetAddress();
	bool IsValidPhoneNumber(string);
	vector<string> parseCSV(istream&, char);	

private:
	map<int, Client*> clientList;

};

#endif // __CLIENT_HANDLER_H__