#include "stdafx.h"
#include "FramesStash.h"
//#include <QDebug>

using namespace qsn;

void FramesStash::appendPacket(RawFrame* packet)
{
   std::lock_guard<std::mutex> guard(mutex);

   this->packets.push_back(packet);
   //qDebug() << packet->caplen;
}

void FramesStash::clear()
{
   std::lock_guard<std::mutex> guard(mutex);

   for(auto& p : packets)
   {
      delete p;
   }
   packets.clear();
}

RawFrame* FramesStash::getPacket(int index) const
{
   std::lock_guard<std::mutex> guard(mutex);

   assert(index < this->packets.size());

   return this->packets.at(index);
}

const std::vector<RawFrame*>& FramesStash::getPackets() const
{
   std::lock_guard<std::mutex> guard(mutex);

   return this->packets;
}

int FramesStash::getPacketsCount() const
{
   return this->packets.size();
}
