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


void FrameListener::initListener(const Adapter* openedAdapter)
{
   this->adapterToListening = openedAdapter;
}

void FrameListener::startListening()
{
   assert(nullptr != this->adapterToListening && "Adapter cannot be null!");
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
   qsn::IPv4Header* ih;
   qsn::EthernetHeader* eH;

   struct tm* ltime;
   char timestr[16];
   const u_char* pkt_data;
   u_short sport, dport;
   time_t local_tv_sec;
   
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

      ///*sport = ntohs(ih->);
      //dport = ntohs(uh->dport);*/

      ///* convert the timestamp to readable format */
      //local_tv_sec = header->ts.tv_sec;
      //ltime = localtime(&local_tv_sec);
      //strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
      ////eH = (qsn::EthernetHeader*)(pkt_data);
      /*ih = (qsn::IPv4Header*)(pkt_data + 14);
      qDebug() << (qsn::rawIPv4Desc(*ih).c_str());
      qDebug() << "\n";*/
      //qDebug() << (QString("Time: %1, len: %2").arg(timestr).arg(header->len));
      /*emit rawPacketSig(QString("Raw:\n%1\n%2")
         .arg(qsn::ethernetHeader2String(*eH).c_str())
         .arg(qsn::rawIPv4Desc(*ih).c_str()));*/
   }
}