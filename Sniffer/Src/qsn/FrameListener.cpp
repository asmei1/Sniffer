#include "stdafx.h"
#include "FrameListener.h"
#include "Structures/IPv4Header.h"
#include "Structures/EthernetHeader.h"
#include "Printer.h"
#include "Structures/RawFrame.h"
#include "Utils/Logger.hpp"

using namespace qsn;

FrameListener::FrameListener(FramesStash* packetsStash)
{
   this->packetsStash = packetsStash;
}

FrameListener::~FrameListener()
{
   if(true == isListening())
   {
      stopListening();
   }
}

void FrameListener::startListening(Adapter* openedAdapter)
{
   this->adapterToListening = openedAdapter;

   if(true == this->listening)
   {
      emit Logger::getInstance().log("Listener is already running!", LogWidget::LogLevel::DEBUG_LOG);
   }
   else
   {
      this->listening = true;

      this->listeningTask = new ListeningTask(this->adapterToListening, this->packetsStash);
      this->listeningThread = new std::thread([&]()
      {
            this->listeningTask->run();
      });

      emit Logger::getInstance().log(QString("Start listening..."), LogWidget::LogLevel::INFO);
   }
}

void FrameListener::stopListening()
{
   assert(nullptr != this->adapterToListening && "Adapter cannot be null!");

   if(false == this->listening)
   {
      emit Logger::getInstance().log("Listener is already stopped!", LogWidget::LogLevel::DEBUG_LOG);
   }
   else
   {
      this->listening = false;

      this->listeningTask->stop();
      this->listeningThread->join();

      this->adapterToListening->closeAdapter();

      delete this->listeningTask;
      delete this->listeningThread;
      emit Logger::getInstance().log(QString("Stop listening..."), LogWidget::LogLevel::INFO);
   }
}

bool FrameListener::isListening() const
{
   return this->listening;
}

void FrameListener::ListeningTask::run()
{
   int res;
   pcap_pkthdr* header;
   const u_char* pkt_data;
   
   while((res = pcap_next_ex(adapter->getRawHandler(), &header, &pkt_data)) >= 0)
   {
      if(true == stopRequested())
      {
         pcap_breakloop(adapter->getRawHandler());
      }

      if(res == 0)
      {
         /* Timeout elapsed */
         continue;
      }

      this->stash->appendPacket(RawFrame::of(header, pkt_data));
   }
}

void FrameListener::ListeningWithDumpTask::run()
{
   int res;
   pcap_pkthdr* header;
   const u_char* pkt_data;
   auto dumpPtr = adapter->getDumpRawPtr();

   while((res = pcap_next_ex(adapter->getRawHandler(), &header, &pkt_data)) >= 0)
   {
      if(true == stopRequested())
      {
         pcap_breakloop(adapter->getRawHandler());
      }

      if(res == 0)
      {
         /* Timeout elapsed */
         continue;
      }

      this->stash->appendPacket(RawFrame::of(header, pkt_data));
      if(nullptr != dumpPtr)
      {
         pcap_dump((u_char*)dumpPtr, header, pkt_data);
      }
   }
}
