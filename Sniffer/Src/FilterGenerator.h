#pragma once
#include "Adapter.h"

class FilterGenerator
{
public:
   FilterGenerator(){};

   FilterGenerator& compile(const Adapter& adapter, const std::string& filter, const IPv4Address& netmask = IPv4Interface::NETMASK_C);
private:
   bpf_program filterCode;
};

