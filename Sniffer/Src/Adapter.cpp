#include "stdafx.h"
#include "Adapter.h"
#include <assert.h>
#include <sstream>

#define PACKET_PART_TO_CAPTURE 65536

std::ostream& operator<<(std::ostream& stream, Adapter& dev)
{
   stream << dev.getFullDescription();

   return stream;
}

Adapter::Adapter(const std::string& name, const std::string& description, bool loopback)
{
   this->name = name;
   this->description = description;
   this->loopback = loopback;
}

void Adapter::addIPv4Interface(const IPv4Interface& ipv4Interface)
{
   this->ipv4List.push_back(ipv4Interface);
}

std::string Adapter::getName() const
{
   return this->name;
}

std::string Adapter::getDescription() const
{
   return this->description;
}

bool Adapter::isLoopBack() const
{
   return this->loopback;
}

std::string Adapter::getFullDescription() const
{
   std::string rV;
   rV += "Name: " + this->name + "\n";
   rV += "Description: " + this->description + "\n";
   rV += "Loopback: ";
   rV += (this->loopback ? "yes" : "no");
   rV += "\n";

   if(false == this->ipv4List.empty())
   {
      rV += "---Address IPv4Address---";
      rV += "\n";
   }

   for(const auto& in : this->ipv4List)
   {
      rV += "\tAddress: " + in.ipv4.toString() + "\n";
      rV += "\tMask: " + in.netmask.toString() + "\n";
      rV += "\tBroadcast: " + in.broadcast.toString() + "\n";
      rV += "\tDestination Address: " + in.destination.toString() + "\n";
   }
   return rV;
}

bool Adapter::openAdapter(std::string& errorString)
{
   bool rV = false;
   char errorBuff[PCAP_ERRBUF_SIZE] = {};

   pcap_t* temp = pcap_open(this->name.c_str(), PACKET_PART_TO_CAPTURE, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, errorBuff);
   if(nullptr != temp)
   {
      rV = true;

      this->adHandler = temp;
      errorString = errorBuff;
   }
   return rV;
}

bool Adapter::checkLinkLayer(LinkLayer linkName) const
{
   assert(nullptr != this->adHandler && "aDHandler cannot be null, openAdapter could be not executed!");

   return pcap_datalink(this->adHandler) == linkName;
}
