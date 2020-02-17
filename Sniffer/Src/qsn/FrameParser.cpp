#include "stdafx.h"
#include "Structures/IPv4Header.h"
#include "FrameParser.h"

using namespace qsn;

FrameUPtr FrameParser::parse(const RawFrame* rawFrame)
{
   auto frame = std::make_unique<Frame>(rawFrame);

   //localhost IPv6
   if(0x18 == rawFrame->data[0])
   {
      frame->valid = false;
   }
   //localhost IPv4
   else if(0x2 == rawFrame->data[0])
   {
      frame->packet = parsePacket(&rawFrame->data[0],4);
   }
   else//for now, rest 
   {
      frame->eth = parseEtHeader(&rawFrame->data[0]);


      //IPv4
      if(0x0800 == frame->eth->ethernetType)
      {
         frame->packet = parsePacket(&rawFrame->data[0], sizeof(EthernetHeader));
      }
      /*else
      {
         frame->valid = true;
      }*/
   }

   return std::move(frame);
}

EthernetHeader FrameParser::parseEtHeader(const uint8_t* data, int offset) const
{
   assert(data);

   EthernetHeader rV;
   rV = *(EthernetHeader*)data;
   rV.ethernetType = ntohs(rV.ethernetType);

   return rV;
}

Packet FrameParser::parsePacket(const uint8_t* data, int offset) const
{
   assert(data);

   Packet rV{ data };
   rV.ipv4H = *(IPv4Header*)(data + offset);

   
   rV.ipv4H->tlen = ntohs(rV.ipv4H->tlen);
   rV.ipv4H->identification = ntohs(rV.ipv4H->identification);
   rV.ipv4H->flags_fo = ntohs(rV.ipv4H->flags_fo);
   rV.ipv4H->crc = ntohs(rV.ipv4H->crc);
   rV.ipv4H->op_pad = ntohf(rV.ipv4H->op_pad);

   return rV;
}
