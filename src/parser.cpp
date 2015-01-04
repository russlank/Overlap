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
*  File name: parser.cpp
*
*/

#include <iostream>
#include "parser.h"
#include "core.h"
#include "error.h"

char next_char = CHAR_NULL;
int line = 1;
int col = 1;

void read_next( void)
{
	std::cin.read( &next_char, 1);
	
	if (std::cin.fail()) {
		next_char = CHAR_NULL;
	} else {
#ifdef _MY_DEBUG
		std::cout << next_char;
#endif
		if (next_char != CHAR_EOLN) {
			col ++;
		} else {
			col = 1;
			line++;
		}
	}
}

void skip_blank( void)
{
	bool finish = false;

	do {
		switch (next_char){
			case CHAR_SPACE:
			case CHAR_TAB:
			case CHAR_EOLN:
				read_next();
				break;
			case CHAR_COMMENT_START:
				while ((next_char != CHAR_EOLN) && (next_char != CHAR_NULL)) read_next();
				break;
			default:
				finish = true;
		}
	} while (!finish);
}

bool read_int( unsigned int &value)
{
	bool found = false;
	
#ifdef _MY_DEBUG
	std::cout << "bool read_int( unsigned int &value)\n";
#endif

	skip_blank();
	
	value = 0;

	while ((next_char >= '0') && (next_char <= '9')){
		value = value * 10 + (next_char - '0');
		found = true;
		read_next();
	}

#ifdef _MY_DEBUG
	std::cout << "value = " << value << '\n';
#endif

	return found;
}

bool read_int_ex( unsigned int &value, unsigned int min, unsigned int max)
{
	bool found = false;
	
	if ( read_int( value)){
		if (( value >= min) && ( value <= max)){
			found = true;
		}
	}

	return found;
}

bool read_char( char c)
{
	bool found = false;

	skip_blank();

	if (next_char == c){
		found = true;
		read_next();
	} else {
		error("unexpected character");
	}

	return found;
}

bool read_identifier( char *buffer, int buffer_size)
{
	bool found = false;
	bool stop = false;

	int len = 0;

#ifdef _MY_DEBUG
	std::cout << "bool read_identifier( char *buffer, int buffer_size)\n";
#endif

	skip_blank();

	do {
		if (((next_char >= '0') && (next_char <= '9')) || ((next_char >= 'a') && (next_char <= 'z')) || ((next_char >= 'A') && (next_char <= 'Z')) || (next_char == '_') || (next_char == '-') || (next_char == '.')) {
			if (len < (buffer_size - 1)){
				found = true;
				buffer[len] = next_char;
				len++;
			} else {
				found = false;
				stop = true;
				error("ID is too long");
			}
			read_next();
		} else {
			stop = true;
		}
	} while (!stop);

	if (len < buffer_size){
		buffer[len] = 0;
	}

#ifdef _MY_DEBUG
	std::cout << "buffer[] = " << buffer << "\n";
#endif
	
	return found;
}

bool read_ip_address( unsigned int &ip_address)
{
#ifdef _MY_DEBUG
	std::cout << "bool read_ip_address( unsigned int &ip_address)\n";
#endif
	
	bool found = false;
	
	unsigned int n1, n2, n3, n4;

	if ( read_int_ex( n1, 0, 255)){
		if (read_char( '.')) {
			if ( read_int_ex( n2, 0, 255)){
				if ( read_char( '.')) {
					if ( read_int_ex( n3, 0, 255)) {
						if (read_char( '.')){
							if ( read_int_ex( n4, 0, 255)){
								ip_address = (( n1 << 24) | ( n2 << 16) | ( n3 << 8) | ( n4));
#ifdef _MY_DEBUG
	std::cout << "n1 = " << n1 << "n2 = " << n2 << "n3 = " << n3 << "n4 = " << n4 << '\n';
#endif
								found = true;
							}
						}
					}
				}
			}
		}
	}

	if (!found){
		error("IP address expected");
	}
	
	return found;
}

bool read_subnet( unsigned int &net_address, unsigned int &net_mask, unsigned int &net_mask_length)
{
	bool found = false;

	if ( read_ip_address( net_address)){
		if ( read_char('/')){
			unsigned int subnet_ones;
			if ( read_int_ex( subnet_ones, 0, 32)){
				net_mask_length = subnet_ones;
				net_mask = (0xffffffff ^ ((1 << (32 - subnet_ones)) - 1));
				found = true;
			}
		}
	}
	
	return found;
}

bool read_subnet_line( SUBNETINFO &SubnetInfo)
{
	bool found = false;

	if ( read_identifier( SubnetInfo.Title, SUBNET_TITLE_MAX_LENGTH)){
		if ( read_char(':')) 
			found = read_subnet( SubnetInfo.Address, SubnetInfo.Mask, SubnetInfo.MaskLength);
	}

	return found;
}



bool read_input( void)
{
	SUBNETINFO Mask;

	read_next();
	
	while ( read_subnet_line(Mask)) AddSubnet( Mask);

	return true;
}