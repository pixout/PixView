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
#include <QQuickPaintedItem>
#include <QImage>

#include <Common/Output.hpp>

class PainterOutput : public QQuickPaintedItem, public Output
{
    Q_OBJECT
public:
    class Painter;
    PainterOutput (QQuickItem * parent = 0);
    virtual ~PainterOutput();

    virtual void Process(const QImage &image);

    void paint(QPainter * painter);

public slots:
    void setCellSize( int w, int h );

private:
    QImage image_;
    int width_;
    int height_;
};
