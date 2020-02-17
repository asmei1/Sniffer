#include "stdafx.h"
#include "AdapterManager.h"
using namespace qsn;

void AdapterManager::loadAllDevices()
{
   pcap_if_t* allDevs;
   pcap_if_t* d;

   //errBuffer allocate
   char errBuff[PCAP_ERRBUF_SIZE];

   //get devices list
   if(-1 == pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, nullptr, &allDevs, errBuff))
   {
      throw (std::string("Error in pcap_findalldevs_ex") + errBuff);
   }

   //get devices from list
   for(d = allDevs; d != nullptr; d = d->next)
   {
      Adapter temp(d->name, d->description, d->flags & PCAP_IF_LOOPBACK);
     
      for(pcap_addr_t* address = d->addresses; address != nullptr; address = address->next)
      {
         if(address->addr->sa_family == AF_INET)
         {
            temp.addIPv4Interface(IPv4Interface::getInterface(address));
         }
      }

      this->allAdapters.push_back(temp);
   }

   pcap_freealldevs(allDevs);
}


const std::vector<Adapter>& AdapterManager::getAllAdapters() const
{
   return this->allAdapters;
}

Adapter* AdapterManager::getOpenedAdapter() const
{
   return this->openedAdapter;
}

void AdapterManager::openAdapter(const std::string& adapterName)
{
   auto it = std::find_if(this->allAdapters.begin(), this->allAdapters.end(), [adapterName](const Adapter& ad)
      {
         return adapterName == ad.getName();
      });


   if(it != this->allAdapters.end())
   {
      try
      {
         it->openAdapter();
      }
      catch (std::exception& e)
      {
         //rethrow exception from openAdapter function
         throw e;
      }

      this->openedAdapter = &*it;
   }
}

void AdapterManager::closeAdapter(const std::string& adapterName)
{
   assert(false);
}
