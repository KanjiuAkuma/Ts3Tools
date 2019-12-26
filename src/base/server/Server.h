//
// Created by Joscha Vack on 12/7/2019.
//

#ifndef TS3TOOLS_SERVER_H
#define TS3TOOLS_SERVER_H

#include <boost/container/list.hpp>
#include <spdlog/spdlog.h>

#include <teamspeak/clientlib_public_definitions.h>

#include "base/client/ClientList.h"
#include "base/channel/ChannelList.h"

class Server {
private:
    std::shared_ptr<spdlog::logger> logger;

    uint64 conId = 0;
    int connectionStatus = STATUS_DISCONNECTED;
    std::string name = "";
    Client* self = nullptr;
    ClientList clientList = ClientList();
    ChannelList channelList = ChannelList();
    friend class CommandProcessor;
    friend class CommandVisitor;
public:
    explicit Server(uint64 conId);
    ~Server();

    bool isConnectionReady();

public: /* Api Functions */
    unsigned int moveClient(Client* client, Channel* channel, const char* password="", const char* retCode=NULL);
public: /* Ts3 Callbacks */
    void onClientConnected(anyID clientId, uint64 newChannelId, const std::string& moveMessage);
    void onClientMoved(anyID clientId, uint64 oldChannelId, uint64 newChannelId, const std::string& moveMessage);
    void onClientMovedSubscription(anyID clientId, uint64 oldChannelId, uint64 newChannelId);
    void onClientDisconnected(anyID clientId, uint64 oldChannelId, const std::string& moveMessage);
    void onClientWasMoved(anyID clientId, uint64 oldChannelId, uint64 newChannelId, anyID moverId, const std::string& moveMessage);
    void onClientKickedFromChannel(anyID clientId, uint64 oldChannelId, uint64 newChannelId, anyID kickerId, const std::string& kickMessage);
    void onClientKickFromServer(anyID clientId, uint64 oldChannelId, anyID kickerId, const std::string& kickMessage);
    void onConnectStatusChangeEvent(int newStatus, unsigned int errorNumber);
public: /* Ts3 Functions */

private: /* Helper */
    Client* loadClient(anyID clientId);
    Channel* loadChannel(uint64 channelId);

    friend class ClientItem;
};

#endif //TS3TOOLS_SERVER_H
