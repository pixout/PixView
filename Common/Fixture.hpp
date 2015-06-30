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

#include <QString>
#include <QVector>

class Fixture
{
public:
    struct Part
    {
	enum Property
	{
	    Undefined,
	    Intensity,
	    Red,
	    Green,
	    Blue
	};
	typedef QVector< Property > Properties;

	int universe;
	int channel;
	Properties properties;
    };

    Fixture( const QString &path );

    typedef QVector< QVector< Part > > Parts;
    void Load( const QString &path );
    Parts &GetParts() { return parts_; }
private:
    QString name_;
    Parts parts_;
};

