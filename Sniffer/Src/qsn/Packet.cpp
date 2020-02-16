#include "stdafx.h"
#include "Packet.h"

using namespace qsn;

std::optional<IPv4Addr> qsn::Packet::getSrcAddr() const
{
   std::optional<IPv4Addr> rV;
   if(true == this->ipv4H.has_value())
   {
      rV = this->ipv4H->saddr;
   }

   return rV;
}

std::optional<IPv4Addr> qsn::Packet::getDstAddr() const
{
   std::optional<IPv4Addr> rV;
   if(true == this->ipv4H.has_value())
   {
      rV = this->ipv4H->daddr;
   }

   return rV;
}

int Packet::getProtocalNumber() const
{
   int protId = -1;

   if(true == this->ipv4H.has_value())
   {
      protId = this->ipv4H->proto;
   }

   return protId;
}
