#pragma once

/**
  * Created by Joscha Vack on 12/26/2019.
  *
  **/

#include <teamspeak/public_definitions.h>

#include <string>
#include <vector>

class Client;

enum ChannelPermissionId {

};

class Channel {
private:
    uint64 id;
    std::string name;
    std::vector<Client*> clients = {};
public:
    Channel(std::string name, uint64 id);

    void onClientJoined(Client* client);
    void onClientLeft(Client* client);

    std::string getName();
    uint64 getId();
    int getClientCount();
};
