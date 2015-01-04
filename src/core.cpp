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
*  File name: core.cpp
*
*/

#include <iostream>
#include "core.h"
#include "output.h"

SUBNETINFO Subnets[MAX_SUBNETS];
int SubnetsCount = 0;

bool AddSubnet( SUBNETINFO &NewSubnet)
{
	bool Result = false;

	if (SubnetsCount < MAX_SUBNETS){
		Subnets[SubnetsCount] = NewSubnet;
		SubnetsCount++;
		Result = true;
	}

	return Result;
}

bool FindOverlaps( void)
{
	bool Result = false;

	int i, j;

	if ( SubnetsCount > 1){
		std::cout << "\nOVERLAPS:\n";
		
		for ( i = 0; i < SubnetsCount; i ++){
			bool FisrtOverlap = true;
			for ( j = 0; j < SubnetsCount; j ++){
				if (i != j){
					unsigned int MaskToUse;

					if ( Subnets[i].MaskLength <= Subnets[j].MaskLength) MaskToUse = Subnets[i].Mask;
					else MaskToUse = Subnets[j].Mask;

					if ((Subnets[i].Address & MaskToUse) == (Subnets[j].Address & MaskToUse)){
						Result = true;
						if ( FisrtOverlap){
							FisrtOverlap = false;
							std::cout << "\nSUBNET [";
							print_subnet_info( Subnets[i]);
							std::cout << "] WITH: \n";
						}
						std::cout << "    ";
						print_subnet_info( Subnets[j]);
						std::cout << '\n';
					}
				}
			}
		}

		if (!Result ) std::cout << "<not found>\n";
	}
	return Result;
}

