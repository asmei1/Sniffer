#include "stdafx.h"
#include "Frame.h"

using namespace qsn;

timeval Frame::getRawTime() const
{
   return this->rawFrame->time;
}

int Frame::getCapturedBytesCount() const
{
   return this->rawFrame->caplen;
}

std::optional<MacAddr> Frame::getMacSrcAddr() const
{
   std::optional<MacAddr> rV;
   if(true == this->eth.has_value())
   {
      rV = this->eth.value().source;
   }
   return rV;
}

std::optional<MacAddr> Frame::getMacDstAddr() const
{
   std::optional<MacAddr> rV;
   if(true == this->eth.has_value())
   {
      rV = this->eth.value().dest;
   }
   return rV;
}

std::optional<Packet> Frame::getPacket() const
{
   std::optional<Packet> rV;
   if(true == this->packet.has_value())
   {
      rV = this->packet.value();
   }
   return rV;
}

bool Frame::isValid() const
{
   return this->valid;
}
