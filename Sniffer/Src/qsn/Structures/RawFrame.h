#pragma once
#include <stdafx.h>
namespace qsn
{
   /**
    * Structure contains a raw data gathered from FrameListener
    */
   struct RawFrame
   {
      timeval time;
      int caplen; 
      int len;
      std::vector<u_char> data;

      static RawFrame* of(const pcap_pkthdr* header, const u_char* data)
      {
         assert(header != nullptr && data != nullptr);

         RawFrame* rV = new RawFrame;
         rV->time = header->ts;
         rV->caplen = header->caplen;
         rV->len = header->len;
         rV->data.resize(rV->caplen);
         memcpy(&rV->data[0], data, rV->caplen * sizeof(u_char));

         return rV;
      }
   };
}