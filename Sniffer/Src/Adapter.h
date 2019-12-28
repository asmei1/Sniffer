#pragma once   
#include "Structures/IPv4Interface.h"
#include "stdafx.h"

class Adapter
{
public:
   Adapter(const std::string& name, const std::string& description, bool loopback = false);

   enum LinkLayer
   {
      ETHERNET = DLT_EN10MB,
   };

   void addIPv4Interface(const IPv4Interface& ipv4Interface);
   void addIPv4Interface(const pcap_addr_t* address);

   std::string getName() const;
   std::string getDescription() const;
   std::string getFullDescription() const;
   pcap_t* getRawHandler() const;

   bool isLoopBack() const;

   bool checkLinkLayer(LinkLayer linkName) const;

   friend std::ostream& operator<<(std::ostream& stream, Adapter& dev);
   void openAdapter();
private:
   pcap_t* adHandler = nullptr;


   std::string name;
   std::string description;
   bool loopback = false;
   std::vector<IPv4Interface> ipv4List;
};
