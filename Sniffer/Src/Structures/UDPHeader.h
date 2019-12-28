#pragma once
#include "stdafx.h"

struct UDPHeader
{
   u_short sport;          // Source port
   u_short dport;          // Destination port
   u_short len;            // Datagram length
   u_short crc;            // Checksum
};

