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
#include "Painter.hpp"
#include "AppSettings.hpp"
#include "Common/Output.hpp"
#include "Common/PixelMapper.hpp"
#include "Common/Fixture.hpp"
#include "Common/Logger.hpp"

#include <QColor>
#include <QDebug>
#include <QDateTime>
#include <QTimer>

struct Painter::Impl: public QObject
{
    Impl( AppSettings *settings ) : settings_( settings )
    {
        timer_.setInterval( 1000 );
        connect( &timer_, &QTimer::timeout, this, &Impl::update );
    }

    int calc_universe_in_use() const
    {
        const qint64 cur = QDateTime::currentMSecsSinceEpoch();
        int count = 0;
        foreach (const qint64 value, stats_)
        {
            if( (cur - value) <= 1000 )
                ++count;
        }

        return count;
    }

    void update()
    {
        settings_->setProperty("universes", calc_universe_in_use() );
    }

    void proceed_universe_stat( int universe )
    {
        stats_.insert( universe, QDateTime::currentMSecsSinceEpoch() );

        if( !timer_.isActive() )
            timer_.start();
    }


    QHash<int, qint64> stats_;
    QTimer timer_;
    AppSettings *settings_;

};

Painter::Painter( Output *output, AppSettings *settings )
    : output_( output ), image_( 400, 400, QImage::Format_RGB32 ), orientation_ ( Painter::Vertical ), settings_( settings ),
      impl_( new Painter::Impl( settings ) )
{
    QObject::connect( this, &Painter::OnOrientation, this, &Painter::Resize );
    RePosition();
}

void Painter::Draw( int universe, const QByteArray &data )
{
    int width = image_.width();
    int height = image_.height();

    impl_->proceed_universe_stat( universe );

    LOG(4, "width=%d height=%d data.size=%d", width, height, data.size());

    for( int y = 0; y < height; ++y )
    {
	for( int x = 0; x < width; ++x )
	{
	    const Fixture::Part *part = orientation_ == Painter::Horizontal
		? mapper_->FixturePart( x, y )
		: mapper_->FixturePart( y, x );
        if( !part )
        {
            image_.setPixel( x, orientation_ == Painter::Horizontal ? y : height - y - 1, Qt::black );
            continue;
        }
	    if ( universe == part->universe )
	    {
		int channels = part->properties.size();
		unsigned char /*i=0, */r=0, g=0, b=0;
		for( int offset = 0; offset < channels; ++offset )
		{
            LOG(4, "channels=%d part->channel=%d offset=%d", channels, part->channel, offset);

            int index = part->channel + offset;

            if( index >= data.size() )
            {
//                WARN( "index is out of data: %d >= %d (probably mismatched pixel mapping)", index, data.size() );
                continue;
            }

		    switch( part->properties[offset] )
		    {
		    // case Fixture::Part::Intensity:
		    // 	i = data[index];
		    // 	break;
		    case Fixture::Part::Red:
		    	r = data[index];
		    	break;
		    case Fixture::Part::Green:
		    	g = data[index];
		    	break;
		    case Fixture::Part::Blue:
		    	b = data[index];
		    	break;
		    default:
			qWarning() << "Unknown fixture part property = " << part->properties[offset];
		    }
		}
                image_.setPixel( x, orientation_ == Painter::Horizontal ? y : height - y - 1, qRgb( r, g, b ) );
	    }
        else
        {
            LOG( 4, "universe (%d) != part(%d,%d)->universe(%d)", universe, x, y, part->universe );
        }
	}
    }

    emit ReadyToOutput( image_ );
}

void Painter::Resize( int width, int height )
{
    image_ = orientation_ == Painter::Horizontal
	? QImage( width, height, QImage::Format_RGB32)
	: QImage( height, width, QImage::Format_RGB32);

    clear();
}

void Painter::SetOrientation( enum Orientation orientation )
{
    clear();
    orientation_ = orientation;
    emit OnOrientation( image_.width(), image_.height() );
}

void Painter::RePosition()
{
    switch( settings_->position() )
    {
        case AppSettings::Horizontal:
            SetOrientation(Painter::Horizontal);
            break;

        case AppSettings::Vertical:
            SetOrientation(Painter::Vertical);
            break;
    }
}

void Painter::clear()
{
    image_.fill( 0 );
}
