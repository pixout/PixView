#include "AppSettings.hpp"

AppSettings::AppSettings(QObject *parent) : QObject(parent),
    port_(6454),position_( Vertical )
{
    fixture_path_ = "test";
}

AppSettings::~AppSettings()
{

}

