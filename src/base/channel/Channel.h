//
// Created by Joscha Vack on 12/7/2019.
//

#ifndef TS3TOOLS_CHANNEL_H
#define TS3TOOLS_CHANNEL_H

#include <boost/container/slist.hpp>

#include <teamspeak/public_definitions.h>

class Client;

enum ChannelPermissionId {

};

class Channel {
private:
    uint64 id;
    std::string name;
    boost::container::slist<Client*> clients = {};
public:
    Channel(std::string name, uint64 id);

    void onClientJoined(Client* client);
    void onClientLeft(Client* client);

    std::string getName();
    uint64 getId();
    int getClientCount();
};

#endif //TS3TOOLS_CHANNEL_H
