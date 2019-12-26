/**
  * Created by Joscha Vack on 12/13/2019.
  *
  **/

#include "Channel.h"
#include "Macros.h"

#include <boost/range/algorithm/find.hpp>


Channel::Channel(std::string name, uint64 id) : name(name), id(id) {}

void Channel::onClientJoined(Client* client) {
    clients.push_front(client);
}

void Channel::onClientLeft(Client* client) {
    auto ndx = boost::find(clients, client);
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

