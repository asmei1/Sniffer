#include "stdafx.h"
#include "IPv4Interface.h"


IPv4Interface IPv4Interface::getInterface(const pcap_addr_t* address)
{
   IPv4Interface rV;
   if(nullptr != address->addr)
   {
      rV.ipv4 = IPv4Address::getIPv4(address->addr);
   }
   if(nullptr != address->netmask)
   {
      rV.netmask = IPv4Address::getIPv4(address->netmask);
   }
   if(nullptr != address->broadaddr)
   {
      rV.broadcast = IPv4Address::getIPv4(address->broadaddr);
   }
   if(nullptr != address->dstaddr)
   {
      rV.destination = IPv4Address::getIPv4(address->dstaddr);
   }

   return rV;
}
