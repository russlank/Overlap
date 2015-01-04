/*
*  Overlap – A small utility that can help network administrators
*            to process large list of IPv4 subnets and discover
*            overlaps among these subnets.
*
*  Copyright (C) 2008 Russlan Kafri <russlank@gmail.com>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License version 2
*  as published by the Free Software Foundation.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program (see the file COPYING included with this
*  distribution); if not, write to the Free Software Foundation, Inc.,
*  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*
*  File name: output.cpp
*
*/

#include <iostream>
#include "core.h"
#include "output.h"

void print_32bit_bin( unsigned int value)
{
	int i;
	int j;

	unsigned int mask = 0x80000000;

	for (i = 0, j = 0; i < 32; i++){
		if ((value & mask) != 0) std::cout << '1';
		else std::cout << '0';
		if (j >= 7) {
			if (i < 31) std::cout << '.';
			j = 0;
		} else j++;
		mask = mask >> 1;
	}
}

void print_ip( unsigned int value)
{
	unsigned int n1, n2, n3, n4;

	n1 = ((value & 0xff000000) >> 24);
	n2 = ((value & 0x00ff0000) >> 16);
	n3 = ((value & 0x0000ff00) >> 8);
	n4 = ((value & 0x000000ff) >> 0);

	std::cout << n1 << '.' << n2 << '.' << n3 << '.' << n4;
}

void print_subnet_info_bin( SUBNETINFO &SubnetInfo)
{
	std::cout << SubnetInfo.Title << " : ";
	print_32bit_bin( SubnetInfo.Address);
	std::cout <<  " / ";
	print_32bit_bin( SubnetInfo.Mask);
}

void print_subnet_info( SUBNETINFO &SubnetInfo)
{
	std::cout << SubnetInfo.Title << " : ";
	
	print_ip( SubnetInfo.Address);
	std::cout <<  "/" << SubnetInfo.MaskLength << " (";
	print_ip( SubnetInfo.Mask);
	std::cout <<  ")";
	if ((SubnetInfo.Address & SubnetInfo.Mask) != SubnetInfo.Address) std::cout <<  "* ";
}

void print_subnet_info_verbose( SUBNETINFO &SubnetInfo)
{
	unsigned int Broadcast, Network;
	print_subnet_info( SubnetInfo);
	std::cout << "\n  BINARY : ";
	print_32bit_bin( SubnetInfo.Address);
	std::cout << "/";
	print_32bit_bin( SubnetInfo.Mask);

	Network = ( SubnetInfo.Address & SubnetInfo.Mask);
	Broadcast = ((SubnetInfo.Address & SubnetInfo.Mask) | ( 0xffffffff ^ SubnetInfo.Mask));
	
	if ( SubnetInfo.MaskLength < 32){
		std::cout << "\n  NETWORK : ";
		print_ip( Network);
		std::cout << " = ";
		print_32bit_bin( Network);
		std::cout << "\n  BROADCAST : ";
		print_ip( Broadcast);
		std::cout << " = ";
		print_32bit_bin( Broadcast);
		if ( SubnetInfo.MaskLength < 31){
			std::cout << "\n  CLIENTS : ";
			print_ip( Network + 1);
			std::cout << " - ";
			print_ip( Broadcast - 1);
			std::cout << " (" << (Broadcast - Network - 1) << ")";
		}
	}
}

void print_subnets( void)
{
	int i;
	
	std::cout << "SUBNETS LIST:" << "\n\n";
	
	for ( i = 0; i < SubnetsCount; i++){
		print_subnet_info_verbose( Subnets[i]);
		std::cout << '\n';
	}
}

void print_about( void)
{
	std::cerr << "\nIP Overlaps Finder v0.02 - by: Russlan Kafri, 2008\n\n";
}
