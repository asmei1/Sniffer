#pragma once
#include "stdafx.h"
#include "Adapter.h"
#include "Stoppable.h"
#include "PacketsStash.h"

namespace qsn
{
   class PacketListener
   {
   public:
      PacketListener(PacketsStash* packetsStash);
      ~PacketListener();

      void initListener(const Adapter* openedAdapter);
      bool isListening() const;


      void startListening();
      void stopListening();
   private:
      class ListeningTask : public Stoppable
      {
      public:
         ListeningTask(const Adapter* adapterToListening, PacketsStash* packetsStash)
            : adapter(adapterToListening), stash(packetsStash)
         {}
         void run() override;

      private:
         const Adapter* adapter;
         PacketsStash* stash;
      };

      bool listening = false;
      const Adapter* adapterToListening = nullptr;
      PacketsStash* packetsStash = nullptr;

      std::thread* listeningThread = nullptr;
      ListeningTask* listeningTask = nullptr;
   };
}
