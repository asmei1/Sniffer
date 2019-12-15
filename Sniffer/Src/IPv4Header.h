#pragma once
#include "stdafx.h"
#include "IPv4Address.h"
#include "Protocols.h"

//get version of IP
#define IP_V(ip)	(((ip) & 0xF0) >> 4)
//get IPv4 header length
#define IP_4_HL(ip)	(((ip) & 0x0F) * 8)

struct IPv4Header
{
   u_char      ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
   u_char      tos;            // Type of service 
   u_short     tlen;           // Total length 
   u_short     identification; // Identification
   u_short     flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
   u_char      ttl;            // Time to live
   u_char      proto;          // Protocol
   u_short     crc;            // Header checksum
   IPv4Address saddr;          // Source address
   IPv4Address daddr;          // Destination address
   u_int       op_pad;         // Option + Padding
};


