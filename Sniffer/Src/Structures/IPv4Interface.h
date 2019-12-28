#pragma once
#include "IPv4Address.h"


struct IPv4Interface
{
   IPv4Address ipv4;
   IPv4Address netmask;
   IPv4Address broadcast;
   IPv4Address destination;

   static IPv4Interface getInterface(const pcap_addr_t* address);

   static inline IPv4Address NETMASK_C = { 255, 255, 255, 255 };
};