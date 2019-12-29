#pragma once
#include "Structures/RawPacket.h"

namespace qsn
{
   class PacketsStash
   {
   public:
      PacketsStash() = default;
      virtual ~PacketsStash() = default;

      virtual void appendPacket(RawPacket* packet);
      virtual void clear();

      RawPacket* getPacket(int index) const;

      const std::vector<RawPacket*>& getPackets() const;

   private:
      mutable std::mutex mutex;
      std::vector<RawPacket*> packets;
   };
}

