#ifndef __CLIENT_HANDLER_H__
#define __CLIENT_HANDLER_H__

#include "Client.h"
#include <map>
#include <vector>


class ClientHandler
{
public:
	void ShowMenu() const;
	void AddClient();
	void DeleteClient(int id);
	void ShowAllAccInfo() const;

	void SearchClient() const;
	vector<Client*> SearchUsingId() const;
	vector<Client*> SearchUsingName() const;
	void ShowSearchResult(vector<Client*>) const;

	int MakeId();

private:
	map<int, Client*> clientList;

};

#endif // __CLIENT_HANDLER_H__