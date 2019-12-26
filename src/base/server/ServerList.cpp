/**
  * Created by Joscha Vack on 12/9/2019.
  *
  **/

#include "ServerList.h"
#include "Macros.h"

void ServerList::onConnectionOpened(uint64 conId) {
    ASSERT(servers.find(conId) == servers.end())
    servers[conId] = new Server(conId);
}

void ServerList::onConnectionClosed(uint64 conId) {
    ASSERT(servers.find(conId) != servers.end())
    delete servers[conId];
    servers.erase(conId);
}

bool ServerList::isServerNotListed(uint64 conId) {
    return servers.find(conId) == servers.end();
}

Server* ServerList::getServer(uint64 conId) {
    ASSERT(servers.find(conId) != servers.end())
    return servers[conId];
}

