#pragma once
#include <array>


namespace qsn
{
   using MacAddr = std::array<uint8_t, 6>;
   using IPv4Addr = std::array<uint8_t, 4>;


   static IPv4Addr sockAddr2IPv4(const sockaddr* addr)
   {
      IPv4Addr rVAddress;
      auto address = ((struct sockaddr_in*)addr)->sin_addr.s_addr;
      u_char* oktet = ((u_char*)&address);
      rVAddress[0] = oktet[0];
      rVAddress[1] = oktet[1];
      rVAddress[2] = oktet[2];
      rVAddress[3] = oktet[3];

      return rVAddress;
   }
}
