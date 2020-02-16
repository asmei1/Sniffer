#pragma once
#include "Structures/RawFrame.h"
#include "Structures/Types.h"
#include "Structures/IPv4Header.h"

namespace qsn
{
   class Packet
   {
      friend class FrameParser;
   public:
      Packet(const uint8_t* _rawData)
         : rawData(_rawData){}


      //for now, app can only get ipv4 address, it have to be changed
      std::optional<IPv4Addr> getSrcAddr() const;
      std::optional<IPv4Addr> getDstAddr() const;

      int getProtocalNumber() const;
      
   private:
      std::optional<IPv4Header> ipv4H;
      const uint8_t* rawData = nullptr;
   };
}
