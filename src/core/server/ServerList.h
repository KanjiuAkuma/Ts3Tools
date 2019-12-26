#pragma once

/**
  * Created by Joscha Vack on 12/26/2019.
  *
  **/

#include "Server.h"

#include <unordered_map>
#include <teamspeak/public_definitions.h>

class ServerList {
private:
    std::unordered_map<uint64, Server*> servers;
public:
    void onConnectionOpened(uint64 conId);
    void onConnectionClosed(uint64 conId);

    bool isServerNotListed(uint64 conId);
    Server* getServer(uint64 conId);
};
