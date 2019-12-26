//
// Created by Joscha Vack on 12/7/2019.
//

#ifndef TS3TOOLS_CLIENT_H
#define TS3TOOLS_CLIENT_H

#include <string>
#include <boost/unordered_map.hpp>

#include <teamspeak/public_definitions.h>

class Channel;

enum ClientPermissionId {

};

class Client {
private:
    std::string name;
    anyID id;
    uint64 dbId;
    Channel* channel;
public:
    Client(std::string name, anyID id, uint64 dbId, Channel* channel);

    void onConnect(anyID newId, Channel* newChannel);
    void onMove(Channel* newChannel);
    void onDisconnect();

    std::string getName();
    bool isConnected();
    anyID getId();
    uint64 getDbId();
    Channel* getChannel();
};

#endif //TS3TOOLS_CLIENT_H
