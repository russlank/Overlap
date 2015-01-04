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
*  File name: output.h
*
*/

#ifndef _OVERLAP_OUTPUT
#define _OVERLAP_OUTPUT

void print_32bit_bin( unsigned int value);
void print_subnet_info( SUBNETINFO &SubnetInfo);
void print_subnet_info_verbose( SUBNETINFO &SubnetInfo);
void print_subnets( void);
void print_about( void);

#endif