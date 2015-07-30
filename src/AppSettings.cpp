#include "AppSettings.hpp"
#include "Common/Logger.hpp"
#include <QUrl>
#include <QFile>
#include <QApplication>

#include <QtQml>

AppSettings::AppSettings(QObject *parent) : QObject(parent),
    port_(6454),position_( Vertical ),app_path_( QString("%1").arg(QCoreApplication::applicationDirPath()) ), universes_(0)
{

}

AppSettings::~AppSettings()
{
}

bool AppSettings::load( const QString &path )
{
    settings_path_ = path ;

    QFile file(settings_path_);
    if( !file.open(QIODevice::ReadWrite))
        return false;    // file could not be created

    if( !file.size() )
        return false;

    LOG( 1, "Loading settings from %s ", qPrintable( settings_path_ ) );


    QDataStream ds(&file);
    ds >> port_;
    ds >> fixture_path_;
    ds >> position_int_;

    emit fixturePathChanged();
    emit onLoaded();

    return true;
}

bool AppSettings::Save( const QString &path )
{
    settings_path_ = path;
    QFile file( settings_path_ );
    if( !file.open( QIODevice::WriteOnly))
    {
        WARN( "Can't create file %s ", qPrintable( settings_path_ ) );
        return false;
    }

    LOG( 1, "Saving settings from %s ", qPrintable( settings_path_ ) );

    QDataStream ds(&file);
    ds << port_;
    ds << fixture_path_;
    ds << position_int_;

    return true;

}

QString AppSettings::stripURLFromPath( const QString &path )
{
    QUrl url(path);

    return url.isLocalFile() ? url.toLocalFile() : path;
}
