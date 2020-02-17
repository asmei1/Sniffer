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

      bool loadDumpFile(const std::string& dumpFileName);
      void startListening(Adapter* openedAdapter, const std::string& dumpFileName);
      void stopListening();
   private:
      class ListeningTask : public Stoppable
      {
      public:
         ListeningTask(pcap_t* deviceToListening, FramesStash* packetsStash)
            : device(deviceToListening), stash(packetsStash)
         {}
         virtual void run() override;

      protected:
         pcap_t* device;
         FramesStash* stash;
      };
      class ListeningWithDumpTask : public ListeningTask
      {
      public:
         ListeningWithDumpTask(pcap_t* deviceToListening, FramesStash* packetsStash, pcap_dumper_t* dumpFile)
            : ListeningTask(deviceToListening, packetsStash), dump(dumpFile)
         {}
         void run() override;

      private:
         pcap_dumper_t* dump;
      };

      bool listening = false;
      Adapter* adapterToListening = nullptr;
      FramesStash* packetsStash = nullptr;

      std::thread* listeningThread = nullptr;
      ListeningTask* listeningTask = nullptr;
   };
}
