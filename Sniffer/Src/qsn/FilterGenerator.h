#pragma once
#include "Adapter.h"


namespace qsn
{
   class FilterGenerator
   {
   public:
      FilterGenerator(){};

      FilterGenerator& compile(const Adapter& adapter, const std::string& filter, const IPv4Addr& netmask = IPv4Interface::NETMASK_C);
   private:
      bpf_program filterCode;
   };
}

