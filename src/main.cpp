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
#include "Receiver.hpp"
#include "Common/PainterOutput.hpp"
#include "Common/PixelMapper.hpp"
#include "Common/Logger.hpp"

#include <QApplication>
#include <QQuickView>
#include <QHostAddress>

void usage()
{
    qDebug() << "Pixout ArtNet Viewer";
    qDebug() << "Version" << VERSION;
    qDebug() << "Usage: ./pixview <port> <pixel-mapping file> [ < horizontol | vertical > ]";
    qDebug() << "\tport - listen on port (default 6454)";
    qDebug() << "\tpixel-mapping file ( use mapping from file )";
    qDebug() << "\thorizontol or vertical orientation of universes (default is vertical)";
    qDebug() << "\n\t Example: pixview 6454 pxm/demo.pxm horizontal";
}

int main( int argc, char* argv[] )
{
    if( argc < 3 ) {
	usage();
	return EXIT_FAILURE;
    }

    LOGGER.setLevel( 3 );
    LOGGER.setOutput( Logger::Console );
    LOG( 1, "viewer Version: %s ", VERSION );

    int port = atoi( argv[1] );
    const char* pm_file = argv[2];

    QApplication app(argc, argv);

    qmlRegisterType<PainterOutput>("Painter", 1, 0, "PainterItem");
    QQuickView view;
    view.setResizeMode( QQuickView::SizeRootObjectToView );
    view.setSource( QUrl::fromLocalFile( "qml/main.qml" ) );
    PainterOutput *output( view.rootObject()->findChild<PainterOutput*>( "painter" ) );
    Painter painter( output );
    PixelMapper mapper;
    painter.SetPixelMapper( &mapper );
    Receiver receiver( port );

    QObject::connect( &receiver, &Receiver::Received, &painter, &Painter::Draw );
    QObject::connect( &painter, &Painter::ReadyToOutput, output, &PainterOutput::Process );
    QObject::connect( &mapper, &PixelMapper::OnResize, &painter, &Painter::Resize );
    QObject::connect( &mapper, &PixelMapper::OnResize, output, &PainterOutput::setCellSize );

    if ( argc > 3 )
    {
	if ( !strcmp(argv[3], "horizontal") )
	{
	    painter.SetOrientation(Painter::Horizontal);
	}
	else if ( !strcmp(argv[3], "vertical") )
	{
	    painter.SetOrientation(Painter::Vertical);
	}
    }
	
    mapper.Load( pm_file );

    qDebug("Listening on port %u with pixel-mapping file %s and orientation %s",
	   port, pm_file, painter.Orientation() == Painter::Vertical ? "vertical" : "horizontal" );

    view.show();

    return app.exec();
}
