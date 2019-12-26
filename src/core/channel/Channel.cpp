/**
  * Created by Joscha Vack on 12/13/2019.
  *
  **/

#include "Channel.h"
#include "core/Core.h"


Channel::Channel(std::string name, uint64 id) : name(name), id(id) {}

void Channel::onClientJoined(Client* client) {
    clients.push_back(client);
}

void Channel::onClientLeft(Client* client) {
    auto ndx = std::find(clients.begin(), clients.end(), client);
    ASSERT(ndx != clients.end());
    clients.erase(ndx);
}

std::string Channel::getName() {
    return name;
}

uint64 Channel::getId() {
    return id;
}

int Channel::getClientCount() {
    return clients.size();
}

