#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "Parser.hpp"

int main(int argc, char* argv[])
{
    if( argc < 3 )
    {
        qCritical() << "Usage: mpx2json /path/file.mpx /path/file.json";
        return 1;
    }

    QCoreApplication app(argc, argv);
    Parser parser(&app);
    parser.Init( argv[1], argv[2] );

    QObject::connect( &parser, SIGNAL( success() ), &app, SLOT( quit() ) );
    QObject::connect( &parser, SIGNAL( failed(int) ), &app, SLOT( quit() ) );

    QTimer::singleShot( 0, &parser, SLOT( start() ) );
    return app.exec();
}
