#pragma once
#include "Adapter.h"
#define PACKET_PART_TO_CAPTURE 65536

class AdapterManager
{
public:
   bool loadAllDevices();
   std::string getLastErrorInfo();

   const std::vector<Adapter>& getAllAdapters() const;
   const Adapter* getOpenedAdapter() const;

   bool openAdapter(const std::string& adapterName, std::string& error);
   void closeAdapter(const std::string& adapterName, std::string& error);
private:
   Adapter* openedAdapter = nullptr;
   std::vector<Adapter> allAdapters;
   std::string lastError;
};

