#pragma once
#include "stdafx.h"
#include "Adapter.h"
#include "Utils/Stoppable.h"
#include "FramesStash.h"

namespace qsn
{
   class FrameListener
   {
   public:
      FrameListener(FramesStash* packetsStash);
      ~FrameListener();

      void initListener(const Adapter* openedAdapter);
      bool isListening() const;


      void startListening();
      void stopListening();
   private:
      class ListeningTask : public Stoppable
      {
      public:
         ListeningTask(const Adapter* adapterToListening, FramesStash* packetsStash)
            : adapter(adapterToListening), stash(packetsStash)
         {}
         void run() override;

      private:
         const Adapter* adapter;
         FramesStash* stash;
      };

      bool listening = false;
      const Adapter* adapterToListening = nullptr;
      FramesStash* packetsStash = nullptr;

      std::thread* listeningThread = nullptr;
      ListeningTask* listeningTask = nullptr;
   };
}
