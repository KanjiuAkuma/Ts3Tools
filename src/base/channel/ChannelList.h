//
// Created by Joscha Vack on 12/7/2019.
//

#ifndef TS3TOOLS_CHANNELLIST_H
#define TS3TOOLS_CHANNELLIST_H

#include "Channel.h"
#include <boost/unordered_map.hpp>

class ChannelList {
private:
    boost::unordered_map<uint64, Channel*> channels;
public:
    void add(uint64 channelId, Channel* channel);
    Channel* get(uint64 channelId);
};

#endif //TS3TOOLS_CHANNELLIST_H
