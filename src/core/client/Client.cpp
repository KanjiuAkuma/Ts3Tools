/**
  * Created by Joscha Vack on 12/9/2019.
  *
  **/

#include "Client.h"

Client::Client(std::string name, anyID id, uint64 dbId, Channel* channel) : name(name), id(id), dbId(dbId), channel(channel) {}

void Client::onConnect(anyID newId, Channel* newChannel) {
    id = newId;
    channel = newChannel;
}

void Client::onMove(class Channel * newChannel) {
    channel = newChannel;
}

void Client::onDisconnect() {
    channel = nullptr;
    id = 0;
}

std::string Client::getName() {
    return name;
}

bool Client::isConnected() {
    return channel != nullptr;
}

anyID Client::getId() {
    return id;
}

uint64 Client::getDbId() {
    return dbId;
}

Channel* Client::getChannel() {
    return channel;
}

