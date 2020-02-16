#pragma once   
#include "Structures/IPv4Interface.h"
#include "stdafx.h"
namespace qsn
{
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


      /**
       * \brief Check and return, if this adapter is a loopback
       * \return 
       */
      bool isLoopBack() const;


      /**
       * \brief Check and return, if this adapter is a given link layer
       * \param linkName Link layer to check.
       * \return 
       */
      bool checkLinkLayer(LinkLayer linkName) const;


      void openAdapter();
      void closeAdapter();


      //-------------------DUMP FILES-------------------
      /**
       * \brief Create dump file.Execute this function after open adapter;
       * \param fileName Path with file name to create and open for dumping.
       */
      void openDumpFile(const std::string& fileName);
      pcap_dumper_t* getDumpRawPtr() const;
      void closeDumpFile();



      friend std::ostream& operator<<(std::ostream& stream, Adapter& dev);
   private:
      pcap_t* adHandler = nullptr;
      pcap_dumper_t* dumpFile = nullptr;

      std::string name;
      std::string description;
      bool loopback = false;
      std::vector<IPv4Interface> ipv4List;
   };
}
