/*
*  Overlap � A small utility that can help network administrators
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
*  File name: main.cpp
*
*/

#ifndef _OVERLAP_PARSER
#define _OVERLAP_PARSER

#include "core.h"

#define	CHAR_NULL			0
#define CHAR_TAB			'\t'
#define CHAR_EOLN			'\n'
#define CHAR_SPACE			' '
#define CHAR_COMMENT_START	'#'

extern int line;
extern int col;

bool read_input( void);

#endif