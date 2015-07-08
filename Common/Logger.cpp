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
#include "Logger.hpp"
#ifdef __linux__
#include <syslog.h>
#endif

Logger::Logger()
    : output_( Logger::Console ), level_( 3 ), use_context_( true )
{
    qInstallMessageHandler( MessageHandler );
#ifdef __linux__
    openlog( "pixout", 0, LOG_LOCAL0 );
#endif
}

Logger::~Logger()
{
#ifdef __linux__
    closelog( );
#endif
}

void Logger::MessageHandler( QtMsgType type, const QMessageLogContext &context, const QString &message )
{
    switch( type )
    {
    case QtDebugMsg:
        LOGGER.log( 1, context.file, context.line, context.function, qPrintable( message ) );
        break;
    case QtWarningMsg:
        LOGGER.log( Warning, context.file, context.line, context.function, qPrintable( message ) );
        break;
    case QtCriticalMsg:
    case QtFatalMsg:
        LOGGER.log( Error, context.file, context.line, context.function, qPrintable( message ) );
        break;
    default: throw;             // shouldn't happen
    }
}

void Logger::write( int level, const char *s )
{
    switch( output_ )
    {
    case None:    writeToNone(    level, s ); break;
    case Console: writeToConsole( level, s ); break;
    case Syslog:  writeToSyslog(  level, s ); break;
    default: ;                  // TODO
    }
}
void Logger::writeToNone( int, const char * )
{
    // nothing to do
}

void Logger::writeToConsole( int, const char *s )
{
    fprintf( stderr, "%s\n", s ); 
}

void Logger::writeToSyslog( int level, const char *s )
{
#ifdef __linux__
    int priority = LOG_INFO;
    switch( level )
    {
    case Warning: priority = LOG_WARNING; break;
    case Error  : priority = LOG_ERR;     break;
    default: ;                  // nothing to do
    }

    syslog( priority, s );
#endif
}


void Logger::log( int level, const char *file, int line, const char *function, const char *format, ... )
{
    if ( level <= level_ )      // if provided level is enabled
    {
        char s[512];
        va_list vlist;
        va_start( vlist, format );

        if( ( Error == level || Warning == level ) && use_context_ )
        {
            char format_ex[256];
            sprintf( format_ex, "%c(%s:%u %s) %s", level == Error ? '#' : '!', file, line, function, format );
            vsprintf( s, format_ex, vlist );
        }
        else
        {
            vsprintf( s, format, vlist );
        }

        va_end( vlist );
        write( level, s );
    }
}
