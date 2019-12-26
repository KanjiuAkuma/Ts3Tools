#pragma once

/**
  * Created by Joscha Vack on 12/7/2019.
  *
  **/


#include "Client.h"

#include <unordered_map>
#include <teamspeak/public_definitions.h>


class ClientList {
private:
    std::unordered_map<anyID, uint64> clientIds {};
    std::unordered_map<uint64, Client*> clients {};
public:
    ~ClientList();
    void add(anyID clientId, Client* client);

    void addId(anyID clientId, uint64 clientDbId);
    void removeId(anyID clientId);

    bool hasClient(anyID clientId);
    bool hasClientDbId(uint64 clientDbId);

    Client* get(anyID clientId);
    Client* getByDbId(uint64 clientDbId);
};