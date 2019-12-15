#include "stdafx.h"
#include "PacketListener.h"
#include "IPv4Header.h"
#include "Printer.h"

PacketListener::PacketListener()
{
}

void PacketListener::packetHandling()
{
   int res;
   struct pcap_pkthdr* header;
   IPv4Header* ih;

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

      ih = (IPv4Header*)(pkt_data + 14);

      emit rawPacketSig(QString("Time: %1, len: %2").arg(timestr).arg(header->len));
      emit rawPacketSig(QString("Raw:\n %1").arg(qsn::rawIPv4Desc(*ih).c_str()));
      //printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);
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
