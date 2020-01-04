#pragma once
#include "Structures/RawFrame.h"
#include "Structures/EthernetHeader.h"

namespace qsn
{
   struct IPv4Header;

   class Frame
   {
      friend class FrameParser;

   public:
      Frame(const RawFrame* _rawFrame)
         : rawFrame(_rawFrame) {}

      timeval getRawTime() const;
      int getCapturedBytesCount() const;

      MacAddr getMacSrcAddr() const;
      MacAddr getMacDstAddr() const;


      Frame(const Frame&) = delete;
      Frame& operator= (const Frame&) = delete;


      IPv4Header* ipv4Header;
   private:
      const RawFrame* rawFrame = nullptr;
      EthernetHeader* eth;
   };

   using FrameUPtr = std::unique_ptr<Frame>;
}
