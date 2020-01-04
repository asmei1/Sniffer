#include "stdafx.h"
#include "Structures/IPv4Header.h"
#include "FrameParser.h"

using namespace qsn;

FrameUPtr FrameParser::parse(const RawFrame* rawFrame)
{
   auto frame = std::make_unique<Frame>(rawFrame);
   frame->eth = (EthernetHeader*)&rawFrame->data[0];
   frame->ipv4Header = (IPv4Header*)(&rawFrame->data[0] + 4);

   return std::move(frame);
}
