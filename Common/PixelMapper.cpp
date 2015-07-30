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
#include "AppSettings.hpp"
#include "Common/PixelMapper.hpp"
#include "Common/Logger.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QUrl>

PixelMapper::PixelMapper( AppSettings *settings )
    : width_( 0 ), height_ ( 0 ), settings_(settings)
{
}

void PixelMapper::Reload()
{
    QUrl url(settings_->fixturePath());
    if( url.isLocalFile() )
    {
        LOG( 2, "Converting URL like fixture path into native path" );
        settings_->fixturePath() = url.toLocalFile();
    }

    LOG( 2, "Loading pixel mapping from file '%s'", qPrintable( settings_->fixturePath() ) );

    QJsonDocument json;
    QFile file( settings_->fixturePath() );

    file.open( QIODevice::ReadOnly | QIODevice::Text );

    if( !file.exists() )
    {
        //todo: exception
        ERR( "File '%s' not found", qPrintable( settings_->fixturePath() ) );
        throw;
    }
    
    QJsonParseError parse_error;
    json = QJsonDocument::fromJson( file.readAll(), &parse_error );
    
    if( json.isEmpty() )
    {
        //todo: exception
        ERR( "Parse error '%s' at offest %d", qPrintable( parse_error.errorString() ), parse_error.offset );
        throw;
    }

    file.close();
    
    QJsonObject pixel_map = json.object();

    QString name;
    int height, width;

    if( !pixel_map.value( "name" ).isString() )
    {
	WARN( "'name' absent" );
    }
    name = pixel_map.value( "name" ).toString();

    if( !pixel_map.value( "height" ).isDouble() )
    {
	ERR( "'height' absent" ); throw;
    }
    height = pixel_map.value( "height" ).toDouble();

    if( !pixel_map.value( "width" ).isDouble() )
    {
	ERR( "'width' absent" ); throw;
    }
    width = pixel_map.value( "width" ).toDouble();

    field_.resize( height );
    for( int y = 0; y < height; ++y )
    {
	field_[ y ].resize( width );
    for( int x = 0; x < width; ++x ) field_[ y ][ x ] = 0;
    }

    width_ = width;
    height_ = height;

    if( !pixel_map.value( "fixtures" ).isArray() )
    {
	ERR( "'fixtures' absent" ); throw;
    }
    else
    {
	QJsonArray fixtures = pixel_map.value( "fixtures" ).toArray();

	fixtures_.resize( fixtures.size() );

	auto it = fixtures.begin();
	auto end = fixtures.end();
	
	for( ;it != end; ++it )
	{
	    if( ( *it ).isObject() )
	    {
		QJsonObject fixtureObject = (*it).toObject();
		QString name, path;
		int universe, channel, x_offset, y_offset;
		if( !fixtureObject.value( "name" ).isString() )
		{
                    WARN( "'name' absent" );
		}
		name = fixtureObject.value( "name" ).toString();

		if( !fixtureObject.value( "path" ).isString() )
		{
                    ERR( "'path' absent" ); throw;
		}
		path = fixtureObject.value( "path" ).toString();

		if( !fixtureObject.value( "universe" ).isDouble() )
		{
                    ERR( "'universe' absent" ); throw;
		}
		universe = fixtureObject.value( "universe" ).toDouble();

		if( !fixtureObject.value( "channel" ).isDouble() )
		{
                    ERR( "'channel' absent" ); throw;
		}
		channel = fixtureObject.value( "channel" ).toDouble();

		if( !fixtureObject.value( "x_offset" ).isDouble() )
		{
                    ERR( "'x_offset' absent" ); throw;
		}
		x_offset = fixtureObject.value( "x_offset" ).toDouble();

		if( !fixtureObject.value( "y_offset" ).isDouble() )
		{
                    ERR( "'y_offset' absent" ); throw;
		    throw;
		}
		y_offset = fixtureObject.value( "y_offset" ).toDouble();

        if( QDir::isRelativePath(path) )
        {
            QFileInfo fi( settings_->fixturePath() );
            path = fi.absolutePath()+QString( QDir::separator() )+path;
        }

		Fixture *fixture = new Fixture( path );

		int height = fixture->GetParts().size();
		for( int y = 0; y < height; ++y )
        {
		    int width = fixture->GetParts()[ y ].size();
		    for( int x = 0; x < width; ++x )
		    {
			Fixture::Part *part = &fixture->GetParts()[ y ][ x ];

			if ( channel + part->properties.size() >= 512 ) // TODO: shouldn't happen
			{
                            WARN( "Fixture '%s' (%d, %d) at offset (%d, %d) in pixel mapping (%d, %d) overlaps universes",
                                  qPrintable( name ), width, height, x_offset, y_offset, width_, height_);
			    channel = 0;
			    ++universe;
			}

			part->universe = universe;
			part->channel = channel;

			if( y_offset + y >= height_ || x_offset + x >= width_ )
			{
                            ERR( "Fixture '%s' (%d, %d) at offset (%d, %d) doesn't fit pixel mapping (%d, %d)",
                                 qPrintable( name ), width, height, x_offset, y_offset, width_, height_ );
			    throw;
			}

			field_[ y_offset + y ] [ x_offset + x ] = part;
			
			channel += part->properties.size();
		    }
		}

		fixtures_.push_back( fixture );
	    }
	}
    }
    emit OnResize( width_, height_ );

    LOG( 3, "PXM: width=%d, height=%d", width_, height_ );
}
