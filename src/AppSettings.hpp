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
#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QUrl>

class AppSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port MEMBER port_ NOTIFY portChanged)
    Q_PROPERTY(QString fixturePath MEMBER fixture_path_ NOTIFY fixturePathChanged)
    Q_PROPERTY(Position position MEMBER position_ NOTIFY positionChanged)
    Q_PROPERTY(QUrl appPath MEMBER app_path_ CONSTANT)
    Q_PROPERTY(int universes MEMBER universes_ NOTIFY universesChanged)

public:
    explicit AppSettings(QObject *parent = 0);
    ~AppSettings();

    Q_INVOKABLE QString stripURLFromPath( const QString &path );
    Q_INVOKABLE bool load( const QString &path );
     bool Save( const QString &path );
     enum Position { Vertical, Horizontal };
    Q_ENUMS(Position)

     int port() const { return port_; }
     const QString& fixturePath() const { return fixture_path_; }
     QString& fixturePath() { return fixture_path_; }
     Position position() const { return position_; }
     int universes() const { return universes_; }

//     static void declareQML();

signals:
      void portChanged();
      void fixturePathChanged();
      void positionChanged();
      void onLoaded();
      void universesChanged();

private:
      int port_;
      QString fixture_path_;

      union {
      Position position_;
      int position_int_;
      };

      QString settings_path_;
      QUrl app_path_;
      int universes_;

};

#endif // APPSETTINGS_H
