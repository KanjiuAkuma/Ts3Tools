/**
  * Created by Joscha Vack on 12/13/2019.
  *
  **/

#include "ChannelList.h"
#include "Macros.h"

void ChannelList::add(uint64 channelId, Channel* channel) {
    ASSERT(channels.find(channelId) == channels.end());
    channels[channelId] = channel;
}

Channel* ChannelList::get(uint64 channelId) {
    ASSERT(channels.find(channelId) != channels.end());
    return channels[channelId];
}
