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
#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include "Common/Fixture.hpp"

class AppSettings;

class PixelMapper : public QObject
{
    Q_OBJECT
signals:
    void OnResize( int width, int height );

public:
    PixelMapper( AppSettings *settings );

    const Fixture::Part *FixturePart( unsigned x, unsigned y ) const { return field_.at( y ).at( x ); }

    typedef QVector< Fixture * > Fixtures;
    typedef QVector< QVector< const Fixture::Part * > > Field;

    int Width() const { return width_; }
    int Height() const { return height_; }

protected:
   bool reload_mapping();

private:
    Fixtures fixtures_;
    Field field_;
    int width_, height_;
    AppSettings *settings_;
};
