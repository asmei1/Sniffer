#include "stdafx.h"
#include "NetworkAdapter.h"


bool NetworkAdapter::loadAllDevices()
{
   bool success = true;

   pcap_if_t* allDevs;
   pcap_if_t* d;

   char errBuff[PCAP_ERRBUF_SIZE];

   //get devices list
   if(-1 == pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, nullptr, &allDevs, errBuff))
   {
      this->lastError = std::string("Error in pcap_findalldevs_ex ") + errBuff;
      success = false;
   }
   else
   {
      for( d = allDevs; d != nullptr; d = d->next)
      {
         Adapter temp(d->name, d->description, d->flags & PCAP_IF_LOOPBACK);

         
         for(pcap_addr_t* address = d->addresses; address != nullptr; address = address->next)
         {
            if (address->addr->sa_family == AF_INET)
            {
               temp.addIPv4Interface(IPv4Interface::getInterface(address));
            }
         }

         this->allAdapters.push_back(temp);
      }
   }

   pcap_freealldevs(allDevs);

   return success;
}

std::string NetworkAdapter::getLastErrorInfo()
{
   std::string temp = this->lastError;
   this->lastError = "";
   return temp;
}

std::vector<Adapter> NetworkAdapter::getAllAdapters() const
{
   return this->allAdapters;
}
