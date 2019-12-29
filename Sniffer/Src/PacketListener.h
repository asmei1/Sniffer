#pragma once
#include "stdafx.h"
#include "Adapter.h"
#include "Stoppable.h"

namespace qsn
{
   class PacketListener
   {
   public:
      PacketListener();
      ~PacketListener();

      void initListener(const Adapter* openedAdapter);
      bool isListening() const;


      void startListening();
      void stopListening();
   private:
      class ListeningTask : public Stoppable
      {
      public:
         ListeningTask(const Adapter* adapterToListening)
            : adapter(adapterToListening)
         {}
         void run() override;

      private:
         const Adapter* adapter;
      };

      bool listening = false;
      const Adapter* adapterToListening = nullptr;


      std::thread* listeningThread = nullptr;
      ListeningTask* listeningTask = nullptr;
   };
}
