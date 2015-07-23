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
#include "Receiver.hpp"
#include "AppSettings.hpp"
#include "Common/Fixture.hpp"
#include "Common/Logger.hpp"

Receiver::Receiver( AppSettings *settings ) : settings_(settings)
{
    QObject::connect( &socket_, &QUdpSocket::readyRead, this, &Receiver::ReadData );
    Reconnect();
}

void Receiver::ReadData()
{
    while (socket_.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket_.pendingDatagramSize());

        socket_.readDatagram( datagram.data(), datagram.size() );

        ProcessData( datagram );
    }
}

void Receiver::ProcessData(const QByteArray &datagram)
{
    static int prev_sequence = -1;
    if( memcmp( "Art-Net", datagram.data(), 7 ) )
    {
        qWarning() << "Skipped broken datagram";
        return;
    }
    unsigned size = ((unsigned char)datagram[16] << 8) + (unsigned char)datagram[17];
    unsigned universe = (unsigned char)datagram[14] + ((unsigned char)datagram[15] << 8);
    int sequence = (unsigned char)datagram[12];
    if( prev_sequence == -1 || ( prev_sequence+1 == sequence || ( prev_sequence == 255 && sequence == 0 ) ) )
        ;
    else
        LOG( 5, "*************** FRAME OUT OF ORDER ( %d >> %d ) ****************", prev_sequence, sequence );
        
    prev_sequence = sequence;
    QByteArray data(datagram.data() + 18, size);

    if( sequence == 0 )
        LOG( 5, "universe = %d channels = %d sequence = %d", universe, size, sequence );

    emit Received( universe, data );
}

void Receiver::Reconnect()
{
    LOG( 1, "Connecting to port %d", settings_->port() );
    socket_.close();
    socket_.bind( QHostAddress::Any, settings_->port() );
}
