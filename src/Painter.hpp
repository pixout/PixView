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
#include <QImage>

class Output;
class PixelMapper;
class AppSettings;

class Painter : public QObject
{
    Q_OBJECT
signals:
    void ReadyToOutput( const QImage &image );
    void OnOrientation( int width, int height);

public:
    enum Orientation
    {
	Vertical,
	Horizontal
    };

    Painter( Output *output, AppSettings *settings );
    void SetPixelMapper( PixelMapper *mapper) { mapper_ = mapper; }
    void SetOrientation( Orientation orientation );
    Orientation Orientation() const { return orientation_; }

public slots:
    void Draw( int universe, const QByteArray &data );
    void Resize( int width, int height);
    void RePosition();

private:
    Output *output_;
    QImage image_;
    PixelMapper *mapper_;
    enum Orientation orientation_;
    AppSettings *settings_;

    void clear();
};
