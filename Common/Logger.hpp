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

//
// Usage:
//   LOGGER.SetOutput( Logger::Console );
//   LOGGER.SetLevel( 1 );
//
//   LOG( 1, "Render output set to Art-Net" );
//   LOG( 2, "Loading file '%s'", filename );
//   LOG( 3, "Image size (%u,%u)", x, y );
//   LOG( 4, "RGB(%u,%u,%u)", r, g, b );
//   LOG( 5, "Channel %d set to %d", channel, v );
//   WARN( "'name' property is absent" );
//   ERR( "File '%s' not found", file );
//
//   Use higher level for more frequent output
//   Do not recommend use level 1 for hotpath (render processing)
//   level 1 - occasional events (etc. render start, output change)
//   level 2 - periodic events (etc. load fixture)
//   level 3 - frequent events (etc, scene rendering, frame output)
//   level 4 - more frequent events (etc. pixel processing, rgb reading)
//   level 5 - very frequent events (etc. channel reading/writing)
//

#include <QObject>
#include <QDebug>
#include <QString>

class Logger : public QObject
{
    Q_OBJECT
public:
    enum Output { None = 0, Console, Syslog };
    enum Level { Error = -2, Warning = -1 };

    Logger();
    ~Logger();
    static Logger& instance() { static Logger instance; return instance; }
    static void MessageHandler( QtMsgType type, const QMessageLogContext &context, const QString &message );
    void log( int level, const char *file, int line, const char *function, const char *format, ... );
    const QString &error_string() const { return error_string_; };

public slots:
    void setOutput( Output output ) { output_ = output; }
    void setLevel( int level ) { level_ = level; }
    int getLevel() const { return level_; }
    void useContext( bool use_context ) { use_context_ = use_context; }

protected:
    void write( int level, const char *s );
    void writeToNone( int level, const char *s );
    void writeToConsole( int level, const char *s );
    void writeToSyslog( int level, const char *s );

private:
    Output output_;
    int level_;
    bool use_context_;
    QString error_string_;
};

#define LOGGER (Logger::instance())

#define LOG( level, format, ...) LOGGER.log( level,           __FILE__, __LINE__, Q_FUNC_INFO, format, ##__VA_ARGS__ );
#define WARN(       format, ...) LOGGER.log( Logger::Warning, __FILE__, __LINE__, Q_FUNC_INFO, format, ##__VA_ARGS__ );
#define ERR(        format, ...) LOGGER.log( Logger::Error,   __FILE__, __LINE__, Q_FUNC_INFO, format, ##__VA_ARGS__ );
