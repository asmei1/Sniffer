#pragma once
#include "Structures/RawFrame.h"
#include "Structures/EthernetHeader.h"
#include "Structures/IPv4Header.h"
#include "Packet.h"

namespace qsn
{

   class Frame
   {
      friend class FrameParser;

   public:
      Frame(const RawFrame* _rawFrame)
         : rawFrame(_rawFrame) {}

      timeval getRawTime() const;
      int getCapturedBytesCount() const;

      std::optional<MacAddr> getMacSrcAddr() const;
      std::optional<MacAddr> getMacDstAddr() const;

      std::optional<Packet> getPacket() const;

      bool isValid() const;

      Frame(const Frame&) = delete;
      Frame& operator= (const Frame&) = delete;


   private:
      const RawFrame* rawFrame = nullptr;

      std::optional<EthernetHeader> eth;
      std::optional<Packet> packet;


      bool valid = true;
   };

   using FrameUPtr = std::unique_ptr<Frame>;
}
