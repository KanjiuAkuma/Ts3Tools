/**
  * Created by Joscha Vack on 12/7/2019.
  *
  **/

#ifndef TS3TOOLS_CLIENTLIST_H
#define TS3TOOLS_CLIENTLIST_H

#include <boost/unordered_map.hpp>
#include <boost/bimap.hpp>
#include <teamspeak/public_definitions.h>

#include "Client.h"


class ClientList {
private:
    boost::unordered_map<anyID, uint64> clientIds {};
    boost::unordered_map<uint64, Client*> clients {};
public:
    ~ClientList();
    void add(anyID clientId, Client* client);

    void addId(anyID clientId, uint64 clientDbId);
    void removeId(anyID clientId);

    bool hasClient(anyID clientId);
    bool hasClient(uint64 clientDbId);

    Client* get(anyID clientId);
    Client* get(uint64 clientDbId);
};

#endif //TS3TOOLS_CLIENTLIST_H
