#pragma once
#include <stdafx.h>
namespace qsn
{
   /**
    * Structure contains a raw data gathered from PacketListener
    */
   struct RawPacket
   {
      timeval time;
      int caplen; 
      int len;
      std::vector<uint8_t> data;


      static RawPacket* of(const pcap_pkthdr* header, const uint8_t* data)
      {
         assert(header != nullptr && data != nullptr);

         RawPacket* rV = new RawPacket;
         rV->time = header->ts;
         rV->caplen = header->caplen;
         rV->len = header->len;
         rV->data.resize(rV->caplen);
         memcpy(&rV->data[0], data, rV->caplen);
         return rV;
      }
   };
}