#pragma once
#include "stdafx.h"
#include "Structures/IPv4Header.h"
#include "Structures/EthernetHeader.h"
#include <sstream>


namespace qsn
{
   static std::string mac2HexString(const MacAddr& mac, const std::string& delimiter = ":")
   {
      std::stringstream ss;
      for(size_t i = 0; i < mac.size(); i++)
      {
         ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(mac[i]);
         if(i + 1 < mac.size())
         {
            ss << delimiter;
         }
      }

      return ss.str();
   }

   static std::string rawData2Hex(const u_char* data, int size, const std::string& delimiter = " ", int nextLineCharsCount = 16)
   {
      std::stringstream ss;
      for(size_t i = 0; i < size; i++)
      {
         ss << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(data[i]);
         
         if(i + 1 < size)
         {
            ss << delimiter;
         }
         if(i > 0 && i % nextLineCharsCount == 0)
         {
            ss << "\n";
         }
      }

      return ss.str();
   }

   static std::string rawData2String(const u_char* data, int size, bool replaceNotPrintableCharacters = true, int nextLineCharsCount = 16)
   {
      std::stringstream ss;
      for(size_t i = 0; i < size; i++)
      {
         if(true == replaceNotPrintableCharacters && false == isprint(data[i]))
         {
            ss << '.';
         }
         else
         {
            ss << data[i];
         }
         
         if(i > 0 && i % nextLineCharsCount == 0)
         {
            ss << '\n';
         }
      }

      return ss.str();
   }

   static std::string ethernetHeader2String(const EthernetHeader& ethPack)
   {
      return "Dst mac: " + mac2HexString(ethPack.dest) + "\nSrc mac: " + mac2HexString(ethPack.source);
   }

   static std::string ipv42String(const IPv4Addr& addr)
   {
      return std::to_string(addr[0]) + "." + std::to_string(addr[1]) + "." + std::to_string(addr[2]) + "." + std::to_string(addr[3]);
   }

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

   static std::string rawIPv4Desc(const IPv4Header& ip4Header)
   {
      std::string rV;
      //rV += QString(": %1\n").arg(ip4Header.
      rV += std::string("Version: ") + std::to_string(IP_V(ip4Header.ver_ihl)) + "\n";
      rV += std::string("Header length: ") + std::to_string(IP_4_HL(ip4Header.ver_ihl)) + "B\n";
      rV += std::string("Protocol: ") + qsn::protToCStr(ip4Header.proto) + "\n";
      rV += std::string("TTL (time to live): ") + std::to_string(ip4Header.ttl) + "\n";
      rV += std::string("Packet length: ") + std::to_string(ip4Header.tlen) + "\n";
      rV += std::string("CRC: ") + std::to_string(ip4Header.crc) + "\n";
      rV += std::string("Source address: ") + ipv42String(ip4Header.saddr) + "\n";
      rV += std::string("Destination address: ") + ipv42String(ip4Header.daddr) + "\n";
      return rV;
   }

}
