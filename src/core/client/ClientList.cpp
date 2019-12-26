/**
  * Created by Joscha Vack on 12/9/2019. 
  *
  **/


#include "ClientList.h"
#include "core/Core.h"


ClientList::~ClientList() {
    for (const auto& it : clients) {
        delete it.second;
    }
}

void ClientList::add(anyID clientId, Client* client) {
    ASSERT(clientIds.find(client->getDbId()) == clientIds.end());
    clients[client->getDbId()] = client;
    clientIds[clientId] = client->getDbId();
}

void ClientList::addId(anyID clientId, uint64 clientDbId) {
    ASSERT(clientIds.find(clientId) == clientIds.end());
    clientIds[clientId] = clientDbId;
}

void ClientList::removeId(anyID clientId) {
    ASSERT(clientIds.find(clientId) != clientIds.end());
    clientIds.erase(clientId);
}

bool ClientList::hasClient(anyID clientId) {
    return clientIds.find(clientId) != clientIds.end();
}

bool ClientList::hasClientDbId(uint64 clientDbId) {
    return clients.find(clientDbId) != clients.end();
}

Client* ClientList::get(anyID clientId) {
    ASSERT(clientIds.find(clientId) != clientIds.end());
    uint64 clientDbId = clientIds[clientId];
    ASSERT(clients.find(clientDbId) != clients.end())
    return clients[clientDbId];
}

Client* ClientList::getByDbId(uint64 clientDbId) {
    ASSERT(clients.find(clientDbId) != clients.end())
    return clients[clientDbId];
}

