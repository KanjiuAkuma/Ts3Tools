#pragma once

/**
  * Created by Joscha Vack on 12/26/2019.
  *
  **/

#include "Channel.h"
#include <unordered_map>

class ChannelList {
private:
    std::unordered_map<uint64, Channel*> channels;
public:
    void add(uint64 channelId, Channel* channel);
    Channel* get(uint64 channelId);
};
