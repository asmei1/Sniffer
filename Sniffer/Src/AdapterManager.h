#pragma once
#include "Adapter.h"
#define PACKET_PART_TO_CAPTURE 65536

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

