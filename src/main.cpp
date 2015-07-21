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
#include "AppSettings.hpp"
#include "Common/PainterOutput.hpp"
#include "Common/PixelMapper.hpp"
#include "Common/Logger.hpp"

#include <QApplication>
#include <QQuickView>
#include <QHostAddress>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>
#include <QDir>

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
    LOGGER.setLevel( 3 );
    LOGGER.setOutput( Logger::Console );
    LOG( 1, "viewer Version: %s ", VERSION );

    const QString settings_path = QDir::fromNativeSeparators(
                QStandardPaths::writableLocation( QStandardPaths::AppLocalDataLocation )+ QDir::separator()+"PixView" + QDir::separator()
                );

    // create settings location if not exists
    QDir ().mkdir( settings_path );
    AppSettings settings;

    if( argc < 3 )
    {
        settings.Load( settings_path + "app.data");
    }
    else {
        settings.setProperty("port", atoi( argv[1] ));
        settings.setProperty("fixturePath", argv[2]);
        settings.setProperty("position", argv[3]);
    }

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    app.setWindowIcon(QIcon(":favicon.png"));
    engine.addImportPath( QStringLiteral("qrc:/"));

    qmlRegisterType<PainterOutput>("Painter", 1, 0, "PainterItem");
    engine.rootContext()->setContextProperty("settings", &settings);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *rootObject = engine.rootObjects().first();
    Q_ASSERT( rootObject );

    PainterOutput *output( rootObject->findChild<PainterOutput*>( "painter" ) );
    Q_ASSERT( output );

    Painter painter( output, &settings );
    PixelMapper mapper;
    painter.SetPixelMapper( &mapper );
    Receiver receiver( settings.port() );

    QObject::connect( &receiver, &Receiver::Received, &painter, &Painter::Draw );
    QObject::connect( &painter, &Painter::ReadyToOutput, output, &PainterOutput::Process );
    QObject::connect( &mapper, &PixelMapper::OnResize, &painter, &Painter::Resize );
    QObject::connect( &mapper, &PixelMapper::OnResize, output, &PainterOutput::setCellSize );

    if( !settings.fixturePath().isEmpty() )
        mapper.Load( settings.fixturePath() );

    LOG(1, "Listening on port %u with pixel-mapping file %s and orientation %s",
       settings.port(), qPrintable(settings.fixturePath()), painter.Orientation() == Painter::Vertical ? "vertical" : "horizontal" );

    QQuickWindow *window = qobject_cast<QQuickWindow *>(rootObject);
    Q_ASSERT( window );
    window->show();

    const int res = app.exec();
    settings.Save( settings_path + "app.data" );
    return res;
}
