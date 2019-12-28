#include "stdafx.h"
#include "IPv4Interface.h"

using namespace qsn;


IPv4Interface IPv4Interface::getInterface(const pcap_addr_t* address)
{
   IPv4Interface rV;
   if(nullptr != address->addr)
   {
      rV.ipv4 = sockAddr2IPv4(address->addr);
   }
   if(nullptr != address->netmask)
   {
      rV.netmask = sockAddr2IPv4(address->netmask);
   }
   if(nullptr != address->broadaddr)
   {
      rV.broadcast = sockAddr2IPv4(address->broadaddr);
   }
   if(nullptr != address->dstaddr)
   {
      rV.destination = sockAddr2IPv4(address->dstaddr);
   }

   return rV;
}
