#include "AppSettings.hpp"
#include "Common/Logger.hpp"
#include <QUrl>
#include <QFile>

AppSettings::AppSettings(QObject *parent) : QObject(parent),
    port_(6454),position_( Vertical )
{
    fixture_path_ = "test";
}

AppSettings::~AppSettings()
{

}

bool AppSettings::Load( const QString &path )
{
    settings_path_ = path;

    QFile file(settings_path_);
    if( !file.open(QIODevice::ReadOnly))
        return true;    // file could not be created

    if( !file.size() )
        return true;

    LOG( 1, "Loading settings from %s ", qPrintable( settings_path_ ) );

    QDataStream ds(&file);
    ds >> port_;
    ds >> fixture_path_;
    ds >> position_int_;

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
