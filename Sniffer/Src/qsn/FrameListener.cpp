#include "stdafx.h"
#include "FrameListener.h"
#include "Structures/IPv4Header.h"
#include "Structures/EthernetHeader.h"
#include "Printer.h"
#include "Structures/RawFrame.h"
#include "Utils/Logger.hpp"
#include "AdapterManager.h"

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

void FrameListener::startListening(Adapter* openedAdapter, const std::string& dumpFileName)
{
   this->adapterToListening = openedAdapter;

   if(true == this->listening)
   {
      emit Logger::getInstance().log("Listener is already running!", LogWidget::LogLevel::DEBUG_LOG);
   }
   else
   {
      this->listening = true;

      this->adapterToListening->openDumpFile(dumpFileName);
      this->listeningTask = new ListeningWithDumpTask(this->adapterToListening->getRawHandler(), this->packetsStash, this->adapterToListening->getDumpRawPtr());
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

      this->adapterToListening->closeDumpFile();
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

bool FrameListener::loadDumpFile(const std::string& dumpFileName)
{
   assert(true == std::filesystem::exists(dumpFileName) && "Dump file name cannot have to exists!");
   bool loaded = false;

   pcap_t* fp;
   char errbuf[PCAP_ERRBUF_SIZE];
   char source[PCAP_BUF_SIZE];
   if(pcap_createsrcstr(source,			// variable that will keep the source string
      PCAP_SRC_FILE,	            // we want to open a file
      NULL,	               		// remote host
      NULL,			               // port on the remote host
      dumpFileName.c_str(),		   // name of the file we want to open
      errbuf			                  // error buffer
   ) == 0)
   {
      /* Open the capture file */
      if((fp = pcap_open(source,			      // name of the device
         PACKET_PART_TO_CAPTURE,			// portion of the packet to capture
         PCAP_OPENFLAG_PROMISCUOUS,  	// promiscuous mode
         1000,				         // read timeout
         NULL,				               // authentication on the remote machine
         errbuf			                     // error buffer
      )) != NULL)
      {
         QApplication::setOverrideCursor(Qt::WaitCursor);

         ListeningTask(fp, this->packetsStash).run();

         loaded = true;

         QApplication::restoreOverrideCursor();
      }

      // read and dispatch packets until EOF is reached
   }

   return loaded;
}

void FrameListener::ListeningTask::run()
{
   int res;
   pcap_pkthdr* header;
   const u_char* pkt_data;
   while((res = pcap_next_ex(device, &header, &pkt_data)) >= 0)
   {
      if(true == stopRequested())
      {
         pcap_breakloop(device);
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

   while((res = pcap_next_ex(device, &header, &pkt_data)) >= 0)
   {
      if(true == stopRequested())
      {
         pcap_breakloop(device);
      }

      if(res == 0)
      {
         /* Timeout elapsed */
         continue;
      }

      this->stash->appendPacket(RawFrame::of(header, pkt_data));
      pcap_dump((u_char*)dump, header, pkt_data);
   }
}
