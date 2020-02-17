#pragma once
#include "Types.h"

namespace qsn
{
   struct IPv4Interface
   {
      IPv4Addr ipv4;
      IPv4Addr netmask;
      IPv4Addr broadcast;
      IPv4Addr destination;

      static IPv4Interface getInterface(const pcap_addr_t* address);

      static inline IPv4Addr NETMASK_C = { 255, 255, 255, 255 };
   };
}