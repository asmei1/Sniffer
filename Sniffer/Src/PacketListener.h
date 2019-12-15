#pragma once
#include "Adapter.h"
#include "stdafx.h"

class PacketListener : public QObject
{
   Q_OBJECT;
public:
   PacketListener();
   ~PacketListener() = default;

   void initListener(const Adapter* openedAdapter);
   void startListening();
   void stopListening();
   bool isListening() const;

   void packetHandling();
signals:
   void rawPacketSig(const QString& packet);

private:
   QMutex cancelMutex;
   bool listening = false;
   const Adapter* adapterToListening = nullptr;
};

