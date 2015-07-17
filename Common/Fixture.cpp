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
#include "Fixture.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "Common/Logger.hpp"

Fixture::Fixture( const QString &path )
{
    Load( path );
}

void Fixture::Load( const QString &path )
{
    LOG( 3, "Loading fixture from file '%s'", qPrintable( path ) );

    QJsonDocument json;
    QFile file( path );

    file.open( QIODevice::ReadOnly | QIODevice::Text );

    if( !file.exists() )
    {
        ERR( "File '%s' not found", qPrintable( path ) );
        throw;
    }
    
    QJsonParseError parse_error;
    json = QJsonDocument::fromJson( file.readAll(), &parse_error );
    
    if( json.isEmpty() )
    {
        ERR( "Parse error '%s' at offest %d", qPrintable( parse_error.errorString() ), parse_error.offset );
        throw;
    }

    file.close();
    
    QJsonObject fixture = json.object();

    int height, width;

    if( !fixture.value( "name" ).isString() )
    {
        WARN( "'name' absent" );
    }
    name_ = fixture.value( "name" ).toString();

    if( !fixture.value( "height" ).isDouble() )
    {
        ERR( "'height' absent" ); throw;
    }
    height = fixture.value( "height" ).toDouble();

    if( !fixture.value( "width" ).isDouble() )
    {
        ERR( "'width' absent" ); throw;
    }
    width = fixture.value( "width" ).toDouble();

    if( !fixture.value( "part" ).isArray() ) // there are ( 'width' x 'height' ) equal 'part's
    {
        ERR( "'part' absent" ); throw;
    }
    else
    {
	QJsonArray properties = fixture.value( "part" ).toArray();

	Part part;
	part.properties.resize( properties.size() );

	auto it = properties.begin();
	auto end = properties.end();
	
        int offset = 0;
	for( ;it != end; ++it, ++offset )
	{
            if( !( *it ).isString() )
            {
                ERR( "Property expected" );
                throw;
            }
	    QString property = (*it).toString();
	    Fixture::Part::Property type = Fixture::Part::Property::Undefined;

	    if ( "intensity" == property )
	    {
		type = Fixture::Part::Property::Intensity;
	    }
	    else if ( "red" == property )
	    {
		type = Fixture::Part::Property::Red;
	    }
	    else if ( "green" == property )
	    {
		type = Fixture::Part::Property::Green;
	    }
	    else if ( "blue" == property )
	    {
		type = Fixture::Part::Property::Blue;
	    }
	    else
	    {
                ERR( "Unknown property '%s'", qPrintable( property ) );
                //throw;
	    }

	    part.properties[ offset ] = type;
	}
	
	parts_.resize( height );

	for( int y = 0; y < height; ++y )
	{
	    parts_[ y ].resize( width );
	    for( int x = 0; x < width; ++x )
	    {
		parts_[ y ] [ x ] = part;
	    }
	}
    }
}

