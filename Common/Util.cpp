/*
Copyright (c) 2013-2015, SIA "Pixout". All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation.

There are special exceptions to the terms and conditions of the GPL as it
is applied to this software.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/
#include "Util.hpp"

static void DumpHelper( const QByteArray &data, unsigned i, unsigned COLUMNS )
{
    printf( " " );
    for( unsigned j = i-COLUMNS; j < i; ++j )
    {
	printf( "%c", isprint( data[j] ) ? data[j] : '.' );
    }
}

void Dump( const QByteArray &data)
{
    const unsigned COLUMNS = 16;
    unsigned i, size = data.size();
    for( i = 0; i < size; ++i )
    {
	if ( i != 0 && ( i % COLUMNS ) == 0)
	{
	    DumpHelper( data, i, COLUMNS );
	}

	if( i % COLUMNS == 0)
	{
	    printf( "\n%08x", i );
	}

	printf( " %02x", (unsigned char) data[i] );
    }
    if ( (i-1) % COLUMNS != 0 )
    {
	for( unsigned k = 0; k < ( COLUMNS - ( ( i-1 ) % COLUMNS ) ) - 1; ++k )
	    printf("   ");
	DumpHelper( data, i-1, COLUMNS );
    }
}
