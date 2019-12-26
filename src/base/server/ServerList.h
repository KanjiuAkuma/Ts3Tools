//
// Created by Joscha Vack on 12/7/2019.
//

#ifndef TS3TOOLS_SERVERLIST_H
#define TS3TOOLS_SERVERLIST_H

#include <boost/unordered_map.hpp>
#include <teamspeak/public_definitions.h>

#include "base/server/Server.h"

class ServerList {
private:
    boost::unordered_map<uint64, Server*> servers;
public:
    void onConnectionOpened(uint64 conId);
    void onConnectionClosed(uint64 conId);

    bool isServerNotListed(uint64 conId);
    Server* getServer(uint64 conId);
};

#endif //TS3TOOLS_SERVERLIST_H
