#pragma once
#include "Frame.h"

namespace qsn
{
   class FrameParser
   {
      FrameParser() = default;

   public:
      static FrameParser& getInstance()
      {
         static FrameParser logger;
         return logger;
      }
         
      FrameParser(const FrameParser&) = delete;
      FrameParser& operator= (const FrameParser&) = delete;

      FrameUPtr parse(const RawFrame* rawFrame);

   private:
      EthernetHeader parseEtHeader(const uint8_t* data, int offset = 0) const;
      Packet parsePacket(const uint8_t* data, int offset = 0) const;
   };
}

