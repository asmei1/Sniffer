#pragma once


struct EthernetHeader
{
   unsigned char destMac[6];
   unsigned char sourceMac[6];
};