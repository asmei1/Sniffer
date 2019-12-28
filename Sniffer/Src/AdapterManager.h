#pragma once
#include "Adapter.h"

//A snapshot length of 65535 should be sufficient, on most if not all networks, to capture all the data available from the packet.
#define PACKET_PART_TO_CAPTURE 65536
namespace qsn
{
   class AdapterManager
   {
   public:
      void loadAllDevices();

      const std::vector<Adapter>& getAllAdapters() const;
      const Adapter* getOpenedAdapter() const;

      void openAdapter(const std::string& adapterName);
      void closeAdapter(const std::string& adapterName);
   private:
      Adapter* openedAdapter = nullptr;
      std::vector<Adapter> allAdapters;
   };
}

