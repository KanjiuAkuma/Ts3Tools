/**
  * Created by Joscha Vack on 12/9/2019.
  *
  **/


#include "Server.h"
#include "core/Core.h"

#include "GlobalDefinitions.h"

#include <teamspeak/public_definitions_rare.h>

Server::Server(uint64 conId) : conId(conId) {
    logger = Logger::createServerLogger(conId);
    logger->set_level(spdlog::level::debug);
    logger->debug("Opened connection");
}

Server::~Server() {
    logger->debug("Closed connection");
    spdlog::drop(logger->name());
}

bool Server::isConnectionReady() {
    return connectionStatus == STATUS_CONNECTION_ESTABLISHED;
}

/* Api Functions */

unsigned int Server::moveClient(Client* client, Channel* channel, const char* password, const char* retCode) {
    return ts3Functions.requestClientMove(conId, client->getId(), channel->getId(), password, retCode);
}

/* Ts3 Callbacks */

void Server::onClientConnected(anyID clientId, uint64 newChannelId, const std::string& moveMessage) {
    ASSERT(newChannelId != 0);
    Client* client;
    Channel* newChannel = channelList.get(newChannelId);

    uint64 dbId = 0;
    CORE_REQUIRE(ts3Functions.getClientVariableAsUInt64(conId, clientId, CLIENT_DATABASE_ID, &dbId));
    if (!clientList.hasClientDbId(dbId)) {  // new client -> add to client list
        client = loadClient(clientId);
        clientList.add(clientId, client);
    }
    else {
        client = clientList.getByDbId(dbId);
        clientList.addId(clientId, dbId);
    }

    client->onConnect(clientId, newChannel);
    newChannel->onClientJoined(client);

    logger->info("'{}' (id={}, dbid={}) joined server '{}'. Message: '{}'",
                  client->getName(), client->getId(), client->getDbId(), name, moveMessage);
    logger->info("\t\tNew channel: '{}' (cid={}, clientCount={})",
                  newChannel->getName(), newChannel->getId(), newChannel->getClientCount());
}

void Server::onClientMoved(anyID clientId, uint64 oldChannelId, uint64 newChannelId, const std::string& moveMessage) {
    Client* client = clientList.get(clientId);
    Channel* oldChannel = channelList.get(oldChannelId);
    Channel* newChannel = channelList.get(newChannelId);

    client->onMove(newChannel);
    oldChannel->onClientLeft(client);
    newChannel->onClientJoined(client);

    logger->info("'{}' (id={}, dbid={}) moved. Server '{}' . Message: '{}'",
                  client->getName(), client->getId(), client->getDbId(), name, moveMessage);
    logger->info("\t\tTo channel '{}' (cid={}, clientCount={})",
                  oldChannel->getName(), oldChannel->getId(), oldChannel->getClientCount());
    logger->info("\t\tFrom channel '{}' (cid={}, clientCount={})",
                  newChannel->getName(), newChannel->getId(), newChannel->getClientCount());

}

void Server::onClientMovedSubscription(anyID clientId, uint64 oldChannelId, uint64 newChannelId) {
    if (!clientList.hasClient(clientId)) {
        onClientConnected(clientId, newChannelId, "Subscribed");
    }
    else {
        onClientMoved(clientId, newChannelId, oldChannelId, "");
    }
}

void Server::onClientDisconnected(anyID clientId, uint64 oldChannelId, const std::string& moveMessage) {
    ASSERT(oldChannelId != 0);
    Client* client = clientList.get(clientId);
    Channel* oldChannel = channelList.get(oldChannelId);

    clientList.removeId(client->getId());
    client->onDisconnect();
    oldChannel->onClientLeft(client);

    logger->info("'{}' (id={}, dbid={}) left server '{}'. Message: '{}'",
                  client->getName(), client->getId(), client->getDbId(), name, moveMessage);
    logger->info("\t\tOld channel: '{}' (cid={}, clientCount={})",
                  oldChannel->getName(), oldChannel->getId(), oldChannel->getClientCount());
}

void Server::onClientWasMoved(anyID clientId, uint64 oldChannelId, uint64 newChannelId, anyID moverId, const std::string& moveMessage) {
    ASSERT(oldChannelId != 0);
    ASSERT(newChannelId != 0);
    Client* client = clientList.get(clientId);
    Client* mover = clientList.get(moverId);
    Channel* oldChannel = channelList.get(oldChannelId);
    Channel* newChannel = channelList.get(newChannelId);

    client->onMove(newChannel);
    oldChannel->onClientLeft(client);
    newChannel->onClientJoined(client);

    logger->info("'{}' (id={}, dbid={}) was moved by '{}' (id={}, dbid={}). Server '{}'. Message: '{}'",
                  client->getName(), client->getId(), client->getDbId(), mover->getName(), mover->getId(), mover->getDbId(), name, moveMessage);
    logger->info("\t\tFrom channel '{}' (cid={}, clientCount={})",
                  oldChannel->getName(), oldChannel->getId(), oldChannel->getClientCount());
    logger->info("\t\tTo channel '{}' (cid={}, clientCount={})",
                  newChannel->getName(), newChannel->getId(), newChannel->getClientCount());
}

void Server::onClientKickedFromChannel(anyID clientId, uint64 oldChannelId, uint64 newChannelId, anyID kickerId, const std::string& kickMessage) {
    ASSERT(oldChannelId != 0);
    ASSERT(newChannelId != 0);
    Client* client = clientList.get(clientId);
    Client* kicker = clientList.get(kickerId);
    Channel* oldChannel = channelList.get(oldChannelId);
    Channel* newChannel = channelList.get(newChannelId);

    // basically a client was moved
    client->onMove(newChannel);
    oldChannel->onClientLeft(client);
    newChannel->onClientJoined(client);

    logger->info("'{}' (id={}, dbid={}) was kicked by '{}' (id={}, dbid={}). Server '{}'. Message: '{}'",
                  client->getName(), client->getId(), client->getDbId(),
                  kicker->getName(), kicker->getId(), kicker->getDbId(), name, kickMessage);
    logger->info("\t\tFrom channel '{}' (cid={}, clientCount={})",
                  oldChannel->getName(), oldChannel->getId(), oldChannel->getClientCount());
}

void Server::onClientKickFromServer(anyID clientId, uint64 oldChannelId, anyID kickerId, const std::string& kickMessage) {
    ASSERT(oldChannelId != 0);
    Client* client = clientList.get(clientId);
    Client* kicker = clientList.get(kickerId);
    Channel* oldChannel = channelList.get(oldChannelId);

    // basically a client left
    clientList.removeId(client->getId());
    client->onDisconnect();
    oldChannel->onClientLeft(client);

    logger->info("'{}' (id={}, dbid={}) was kicked by '{}' (id={}, dbid={}) from the Server '{}'. Message: '{}'",
                  client->getName(), client->getId(), client->getDbId(),
                  kicker->getName(), kicker->getId(), kicker->getDbId(), name, kickMessage);
    logger->info("\t\tFrom channel '{}' (cid={}, clientCount={})",
                  oldChannel->getName(), oldChannel->getId(), oldChannel->getClientCount());
}

void Server::onConnectStatusChangeEvent(int newStatus, unsigned int errorNumber) {
    if (errorNumber != 0) {
        logger->error("Connection status changed: {} (error: {})", newStatus, errorNumber);
    }
    else {
        logger->trace("Connection status changed: {}", newStatus);
    }
    connectionStatus = newStatus;

    if (newStatus == STATUS_CONNECTION_ESTABLISHED) { // init server
        // load server name
        char* rawServerName = nullptr;
        ts3Functions.getServerVariableAsString(conId, VIRTUALSERVER_NAME, &rawServerName);
        name = std::string(rawServerName);
        ts3Functions.freeMemory(rawServerName);
        logger->trace("═╦═ Initializing server: '{}'", name);
        logger->trace(" ║");

        // load channel list
        logger->trace(" ╠═\t## Channel list ##");
        logger->trace(" ╚╗");
        uint64* channelIds = nullptr;
        ts3Functions.getChannelList(conId, &channelIds);
        for (int i = 0; channelIds[i]; i++) {
            Channel* c = loadChannel(channelIds[i]);
            channelList.add(channelIds[i], c);
            logger->trace("  ╠══ Channel '{}' id={}", c->getName(), c->getId());
        }
        ts3Functions.freeMemory(channelIds);
        logger->trace(" ╔╝");
        logger->trace(" ║");

        // load client list
        logger->trace(" ╠═\t## Client list ##");
        logger->trace(" ╚╗");
        anyID* clientIds = nullptr;
        ts3Functions.getClientList(conId, &clientIds);
        for (int i = 0; clientIds[i]; i++) {
            Client* c = loadClient(clientIds[i]);
            clientList.add(clientIds[i], c);

            Channel* ch = c->getChannel();
            ch->onClientJoined(c);

            logger->trace("  ╠══ Client '{}' id={}, dbid={} in channel '{}' (id={})",
                          c->getName(), c->getId(), c->getDbId(), ch->getName(), ch->getId());
        }
        ts3Functions.freeMemory(clientIds);
        logger->trace(" ╔╝");
        logger->trace(" ║");

        // set up self
        anyID selfId;
        CORE_REQUIRE(ts3Functions.getClientID(conId, &selfId));
        self = clientList.get(selfId);
        Channel* selfChannel = self->getChannel();
        logger->trace("═╩═ Self: '{}', id={}, dbid={} in channel '{}' (id={})",
                      self->getName(), self->getId(), self->getDbId(), selfChannel->getName(), selfChannel->getId());

        logger->debug("Server '{}' ready", name);
    }
}

/* Ts3 Functions */

/* Helper */

Client* Server::loadClient(anyID clientId) {
    // get db id
    uint64 dbId = 0;
    CORE_REQUIRE(ts3Functions.getClientVariableAsUInt64(conId, clientId, CLIENT_DATABASE_ID, &dbId));

    // get nick
    char* rawNickname = nullptr;
    CORE_REQUIRE(ts3Functions.getClientVariableAsString(conId, clientId, CLIENT_NICKNAME, &rawNickname));
    std::string nickname = std::string(rawNickname);
    ts3Functions.freeMemory(rawNickname);

    uint64 channelId = 0;
    CORE_REQUIRE(ts3Functions.getChannelOfClient(conId, clientId, &channelId));
    Channel* channel = channelList.get(channelId);

    return new Client(nickname, clientId, dbId, channel);
}

Channel* Server::loadChannel(uint64 channelId) {
    char* rawName = nullptr;
    CORE_REQUIRE(ts3Functions.getChannelVariableAsString(conId, channelId, CHANNEL_NAME, &rawName));
    std::string nickname = std::string(rawName);
    ts3Functions.freeMemory(rawName);
    return new Channel(rawName, channelId);
}
