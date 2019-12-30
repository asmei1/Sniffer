#include "stdafx.h"
#include "PacketsStash.h"
#include <QDebug>

using namespace qsn;

void PacketsStash::appendPacket(RawPacket* packet)
{
   std::lock_guard<std::mutex> guard(mutex);

   this->packets.push_back(packet);
   qDebug() << packet->caplen;
}

void PacketsStash::clear()
{
   std::lock_guard<std::mutex> guard(mutex);

   for(auto& p : packets)
   {
      delete p;
   }
   packets.clear();
}

RawPacket* PacketsStash::getPacket(int index) const
{
   std::lock_guard<std::mutex> guard(mutex);

   assert(index < this->packets.size());

   return this->packets.at(index);
}

const std::vector<RawPacket*>& PacketsStash::getPackets() const
{
   std::lock_guard<std::mutex> guard(mutex);

   return this->packets;
}

int PacketsStash::getPacketsCount() const
{
   return this->packets.size();
}
