#include "stdafx.h"
#include "PacketsQStash.h"

void PacketsQStash::appendPacket(qsn::RawPacket* packet)
{
   qsn::PacketsStash::appendPacket(packet);
   emit this->appendPacketSig();
}

void PacketsQStash::clear()
{
   qsn::PacketsStash::clear();
   emit this->clearAllPacketsSig();
}
