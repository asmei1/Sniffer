#pragma once
#include "Structures/RawFrame.h"

namespace qsn
{
   class FramesStash
   {
   public:
      FramesStash() = default;
      virtual ~FramesStash();

      virtual void appendPacket(RawFrame* packet);
      virtual void clear();

      RawFrame* getPacket(int index) const;

      const std::vector<RawFrame*>& getPackets() const;

      int getPacketsCount() const;

   private:
      mutable std::mutex mutex;
      std::vector<RawFrame*> packets;
   };
}

