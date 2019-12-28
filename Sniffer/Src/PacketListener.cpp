#include "stdafx.h"
#include "PacketListener.h"
#include "Structures/IPv4Header.h"
#include "Structures/EthernetHeader.h"
#include "Printer.h"

using namespace qsn;

PacketListener::PacketListener()
{
}

void PacketListener::packetHandling()
{
   int res;
   struct pcap_pkthdr* header;
   qsn::IPv4Header* ih;
   qsn::EthernetHeader* eH;

   struct tm* ltime;
   char timestr[16];
   const u_char* pkt_data;
   u_short sport, dport;
   time_t local_tv_sec;

   while((res = pcap_next_ex(this->adapterToListening->getRawHandler(), &header, &pkt_data)) >= 0) 
   {
      QMutexLocker locker(&this->cancelMutex);
      if(false == this->listening)
      {
         break;
      }
      locker.unlock();

      if(res == 0)
      {
         /* Timeout elapsed */
         continue;
      }
      /*sport = ntohs(ih->);
      dport = ntohs(uh->dport);*/

      /* convert the timestamp to readable format */
      local_tv_sec = header->ts.tv_sec;
      ltime = localtime(&local_tv_sec);
      strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
      eH = (qsn::EthernetHeader*)(pkt_data);
      ih = (qsn::IPv4Header*)(pkt_data + 14);

      emit rawPacketSig(QString("Time: %1, len: %2").arg(timestr).arg(header->len));
      emit rawPacketSig(QString("Raw:\n%1\n%2")
         .arg(qsn::ethernetHeader2String(*eH).c_str())
         .arg(qsn::rawIPv4Desc(*ih).c_str()));
   }
}

void PacketListener::initListener(const Adapter* openedAdapter)
{
   this->adapterToListening = openedAdapter;
}

void PacketListener::startListening()
{
   QMutexLocker locker(&this->cancelMutex);
   this->listening = true;
   QtConcurrent::run(this, &PacketListener::packetHandling);
}

void PacketListener::stopListening()
{
   QMutexLocker locker(&this->cancelMutex);
   this->listening = false;
}

bool PacketListener::isListening() const
{
   return this->listening;
}
