#pragma once
#include "stdafx.h"
#include "IPv4Header.h"

namespace qsn
{
   static std::string rawIPv4Desc(const IPv4Header& ip4Header)
   {
      std::string rV;
      //rV += QString(": %1\n").arg(ip4Header.
      rV += std::string("Version: ") + std::to_string(IP_V(ip4Header.ver_ihl)) + "\n";
      rV += std::string("Header length: ") + std::to_string(IP_4_HL(ip4Header.ver_ihl)) + "B\n";
      rV += std::string("Procotol: ") + qsn::protToCStr(ip4Header.proto) + "\n";
      rV += std::string("TTL (time to live): ") + std::to_string(ip4Header.ttl) + "\n";
      rV += std::string("Packet length: ") + std::to_string(ip4Header.tlen) + "\n";
      rV += std::string("CRC: ") + std::to_string(ip4Header.crc) + "\n";
      rV += std::string("Source address: ") + ip4Header.saddr.toString() + "\n";
      rV += std::string("Destination address: ") + ip4Header.daddr.toString() + "\n";
      return rV;
   }
}
