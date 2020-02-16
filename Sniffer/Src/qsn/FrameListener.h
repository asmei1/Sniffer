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

      bool isListening() const;


      void startListening(Adapter* openedAdapter, const std::string& dumpFileName);
      void stopListening();
   private:
      class ListeningTask : public Stoppable
      {
      public:
         ListeningTask(Adapter* adapterToListening, FramesStash* packetsStash)
            : adapter(adapterToListening), stash(packetsStash)
         {}
         virtual void run() override;

      protected:
         Adapter* adapter;
         FramesStash* stash;
      };
      class ListeningWithDumpTask : public ListeningTask
      {
      public:
         ListeningWithDumpTask(Adapter* adapterToListening, FramesStash* packetsStash)
            : ListeningTask(adapterToListening, packetsStash)
         {}
         void run() override;
      };

      bool listening = false;
      Adapter* adapterToListening = nullptr;
      FramesStash* packetsStash = nullptr;

      std::thread* listeningThread = nullptr;
      ListeningTask* listeningTask = nullptr;
   };
}
