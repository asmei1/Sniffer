#pragma once
#include "stdafx.h"


struct IPv4Address
{
   std::array<uint8_t, 4> addr;

   std::string toString() const
   {
      return std::to_string(this->addr[0]) + "." + std::to_string(this->addr[1]) + "." + std::to_string(this->addr[2]) + "." + std::to_string(this->addr[3]);
   }

   static IPv4Address getIPv4(const sockaddr* addr)
   {
      IPv4Address rVAddress;
      auto address = ((struct sockaddr_in*)addr)->sin_addr.s_addr;
      u_char* oktet = ((u_char*)&address);
      rVAddress.addr[0] = oktet[0];
      rVAddress.addr[1] = oktet[1];
      rVAddress.addr[2] = oktet[2];
      rVAddress.addr[3] = oktet[3];

      return rVAddress;
   }
};

