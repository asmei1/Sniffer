#include "stdafx.h"
#include "Frame.h"


timeval qsn::Frame::getRawTime() const
{
   return this->rawFrame->time;
}

int qsn::Frame::getCapturedBytesCount() const
{
   return this->rawFrame->caplen;
}

qsn::MacAddr qsn::Frame::getMacSrcAddr() const
{
   return this->eth->source;
}

qsn::MacAddr qsn::Frame::getMacDstAddr() const
{
   return this->eth->dest;
}
