#pragma once   
#include "IPv4Interface.h"
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

   std::string getName() const;
   std::string getDescription() const;
   std::string getFullDescription() const;
   bool isLoopBack() const;

   bool checkLinkLayer(LinkLayer linkName) const;

   friend std::ostream& operator<<(std::ostream& stream, Adapter& dev);
   friend class AdapterManager;
   pcap_t* adHandler = nullptr;
private:
   bool openAdapter(std::string& errorString);


   std::string name;
   std::string description;
   bool loopback = false;
   std::vector<IPv4Interface> ipv4List;
};
