#include "stdafx.h"
#include "Adapter.h"
#include <assert.h>
#include <sstream>
#include "AdapterManager.h"
#include "Printer.h"

using namespace qsn;

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

void Adapter::addIPv4Interface(const pcap_addr_t* address)
{
   this->ipv4List.push_back(IPv4Interface::getInterface(address));
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
      rV += "\tAddress: " + ipv42String(in.ipv4) + "\n";
      rV += "\tMask: " + ipv42String(in.netmask) + "\n";
      rV += "\tBroadcast: " + ipv42String(in.broadcast) + "\n";
      rV += "\tDestination Address: " + ipv42String(in.destination) + "\n";
   }
   return rV;
}

pcap_t* Adapter::getRawHandler() const
{
   return this->adHandler;
}

void Adapter::openAdapter()
{
   char errorBuff[PCAP_ERRBUF_SIZE] = {};

   pcap_t* temp = pcap_open(this->name.c_str(), PACKET_PART_TO_CAPTURE, PCAP_OPENFLAG_PROMISCUOUS,
                 1000, NULL, errorBuff);
   if(nullptr != temp)
   {
      this->adHandler = temp;
   }
   else
   {
      throw (errorBuff);
   }
}

void Adapter::closeAdapter()
{
   pcap_close(this->adHandler);
   this->adHandler = nullptr;
}

void Adapter::openDumpFile(const std::string& fileName) 
{
   this->dumpFile = pcap_dump_open(this->adHandler, fileName.c_str());
}

pcap_dumper_t* Adapter::getDumpRawPtr() const
{
   return this->dumpFile;
}

bool Adapter::checkLinkLayer(LinkLayer linkName) const
{
   assert(nullptr != this->adHandler && "aDHandler cannot be null, openAdapter could be not executed!");

   return pcap_datalink(this->adHandler) == linkName;
}
