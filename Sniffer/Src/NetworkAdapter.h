#pragma once
#include "Adapter.h"

class NetworkAdapter
{
public:
   bool loadAllDevices();
   std::string getLastErrorInfo();

   std::vector<Adapter> getAllAdapters() const;
private:
   std::vector<Adapter> allAdapters;
   std::string lastError;
};

