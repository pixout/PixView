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
#include <QPixmap>
#include <QPainter>

#include "PainterOutput.hpp"

PainterOutput::PainterOutput ( QQuickItem * parent )
    : QQuickPaintedItem( parent )
{
    setRenderTarget( QQuickPaintedItem::FramebufferObject );
    setPerformanceHint(QQuickPaintedItem::FastFBOResizing, true);
}

PainterOutput::~PainterOutput()
{
    static QPixmap *doubleBuffer = 0;
    if( doubleBuffer ) delete doubleBuffer;
}

void PainterOutput::Process( const QImage &image )
{
    image_ = image;
    update();
}

//#define WITHOUT_BIG_PIXELS 1

void PainterOutput::paint(QPainter * painter)
{

    //todo: rework this code, repeats code from: Painter::Draw()

    static QPixmap *doubleBuffer = 0;
    if( !doubleBuffer )
    {
	doubleBuffer = new QPixmap( width(), height() );
	doubleBuffer->fill( Qt::black );
    }

    QPainter dbPainter( doubleBuffer );
    const int spaces = 1;

    const int DefWidth = image_.rect().width() / width_;
    const int DefHeight = image_.rect().height() / height_;
    qreal box_w = (width() / (image_.isNull() ? DefWidth : image_.rect().width()))-spaces;
    qreal box_h = (height() / (image_.isNull() ? DefHeight : image_.rect().height()))-spaces;

    if( !image_.isNull() )
    {
#ifdef WITHOUT_BIG_PIXELS
	dbPainter.drawImage(0,0,image_);
#else
	int ystep = 0;
	for( int h = 0; h < image_.height(); ++h)
	{
	    const QRgb *line = reinterpret_cast< QRgb *>( image_.scanLine( h ) );

	    int xstep = 0;
	    for( int w = 0; w < image_.width(); ++w)
	    {
		dbPainter.fillRect( QRectF( (box_w*w)+xstep, (box_h*h)+ystep, box_w, box_h ), QColor( line[w] ));
		xstep += spaces;
	    }

	    ystep += spaces;
	}
#endif
    }
    else
    {
	int ystep = 0;
	for( int h = 0; h < height(); ++h)
	{
	    int xstep = 0;
	    for( int w = 0; w < width(); ++w)
	    {
		dbPainter.setPen( QColor( 255,255,255 ) );
		dbPainter.drawRect( QRectF( (box_w*w)+xstep, (box_h*h)+ystep, box_w, box_h ) );
		xstep += spaces;

	    }
	    ystep += spaces;
	}

    }

    painter->drawPixmap( 0,0, *doubleBuffer );

#if 0
    //todo: we can use only two lines instead of this code with double buffering
    QPainter dbPainter();
    painter->drawImage( QPointF(0,0), image_ );
#endif

}

void PainterOutput::setCellSize( int w, int h )
{
    width_ = w;
    height_ = h;
}
