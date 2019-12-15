#pragma once
#include "stdafx.h"

namespace qsn
{
   inline const char* protToCStr(const int protID)
   {
      switch(protID)
      {
      case IPPROTO_TCP:
         return "TCP";
      case IPPROTO_ICMP:
         return "ICMP";
      case IPPROTO_IPV4:
         return "IPv4";
      case IPPROTO_IPV6:
         return "IPv6";
      case IPPROTO_UDP:
         return "UDP";
      default:
         return "Undefined protocol";
      }
   }

   inline std::string protToStr(const int protID)
   {
      return protToCStr(protID);
   }
}