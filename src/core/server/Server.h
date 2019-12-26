#pragma once

/**
  * Created by Joscha Vack on 12/26/2019.
  *
  **/

#include "core/client/ClientList.h"
#include "core/channel/ChannelList.h"

#include <vector>
#include <spdlog/spdlog.h>
#include <teamspeak/clientlib_public_definitions.h>

class Server {
private:
    std::shared_ptr<spdlog::logger> logger;

    uint64 conId = 0;
    int connectionStatus = STATUS_DISCONNECTED;
    std::string name = "";
    Client* self = nullptr;
    ClientList clientList = ClientList();
    ChannelList channelList = ChannelList();
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
};
