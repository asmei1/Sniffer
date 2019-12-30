#pragma once
#include "stdafx.h"
#include "PacketsStash.h"

class PacketsQStash : public QObject, public qsn::PacketsStash
{
   Q_OBJECT;
public:

   void appendPacket(qsn::RawPacket* packet) override;
   void clear() override;

signals:
   void appendPacketSig();
   void clearAllPacketsSig();
};

