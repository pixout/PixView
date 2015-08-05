#include "Parser.hpp"
#include <QFile>
#include <QDebug>
#include <QtXml/QtXml>
#include <QStack>
#include <QTextStream>

bool Parser::Init( const QString &in_path, const QString &out_path )
{
    if( !QFile::exists( in_path ) ||
        !QFile::exists( in_path ) )
        return false;

    in_path_ = in_path;
    out_path_ = out_path;
    return true;
}

void Parser::start()
{
    struct Handler: public QXmlDefaultHandler
    {

        struct Fixture
        {
            QString uid;
            QString name;
            QString size;
            QStringList channels;
            QString x;
            QString y;
            QString dmx_universe;
            QString dmx_channel;
            int height;
            int width;
        };

        bool startDocument()
        {
            width = "1";
            height = "1";
            fixtures_stack_.clear();
            return true;
        }

        bool attr( const QXmlAttributes &attributes, QString &dest, const QString &src )
        {
            for( int i=0; i<attributes.count(); ++i )
            {
                if( attributes.qName(i) == src )
                {
                    dest = attributes.value(i);
                    return true;
                }
            }

            return false;
        }

        bool startElement( const QString &/*namespaceURI*/, const QString &/*localName*/, const QString &qName, const QXmlAttributes &attributes )
        {
            if( qName == "matrix_size" )
            {
                if( !attr(attributes, width, "x") )
                    qDebug() << "attr fixture, x not found";

                if( !attr(attributes, height,"y") )
                    qDebug() << "attr fixture, y not found";
            }

            if( qName == "fixture" )
            {
                fixtures_stack_.push( Fixture() );
                fixtures_stack_.top().width = 1;        //default
                fixtures_stack_.top().height = 1;
                fixtures_stack_.top().dmx_universe = "0";
                fixtures_stack_.top().dmx_channel = "0";

//                if( !attr(attributes, fixtures_stack_.top().uid,"unit_uuid") )
//                    qDebug() << "attr fixture,unit_uuid not found";
            }
            else if( qName == "unit_name" && !fixtures_stack_.empty() )
            {
                 if( !attr(attributes, fixtures_stack_.top().name,"value") )
                     qDebug() << "attr unit_name, value not found";
            }
            else if( qName == "short_name" && !fixtures_stack_.empty() )
            {
                 if( !attr(attributes, fixtures_stack_.top().uid,"value") )
                     qDebug() << "attr short_name, value not found";
            }
            else if( qName == "protocol_name" && !fixtures_stack_.empty() )
            {
                 if( !attr(attributes, fixtures_stack_.top().size,"value") )
                     qDebug() << "attr protocol_name, value not found";

                 if( fixtures_stack_.top().size == "1 pixel")
                 {
                     fixtures_stack_.top().width = 1;
                     fixtures_stack_.top().height = 1;
                 }
            }
            else if( qName == "channel" && !fixtures_stack_.empty() )
            {
                 QString name;
                 if( !attr(attributes, name,"name") )
                     qDebug() << "attr channel, name not found";

                 if( name.contains("red", Qt::CaseInsensitive) )
                     name = "red";
                 if( name.contains("green", Qt::CaseInsensitive) )
                     name = "green";
                 if( name.contains("blue", Qt::CaseInsensitive) )
                     name = "blue";

                 fixtures_stack_.top().channels << name;
            }
            else if( qName == "position" && !fixtures_stack_.empty() )
            {
                 if( !attr(attributes, fixtures_stack_.top().x,"x") )
                     qDebug() << "attr position, x not found";

                 if( !attr(attributes, fixtures_stack_.top().y,"y") )
                     qDebug() << "attr position, y not found";
            }
            else if( qName == "dmx_universe" && !fixtures_stack_.empty() )
            {
                if( !attr(attributes, fixtures_stack_.top().dmx_universe,"value") )
                    qDebug() << "attr dmx_universe, value not found";
            }
            else if( qName == "dmx_channel" && !fixtures_stack_.empty() )
            {
                if( !attr(attributes, fixtures_stack_.top().dmx_channel,"value") )
                    qDebug() << "attr dmx_channel, value not found";
            }

            return true;
        }

        QString errorString() const
        {
            return errorStr;
        }

        bool fatalError (const QXmlParseException & exception)
        {
            qWarning() << "Fatal error on line" << exception.lineNumber()
                       << ", column" << exception.columnNumber() << ":"
                       << exception.message();

            errorStr = exception.message();
            return false;
        }

        const QStack<Fixture> &fixtures() const
        {
            return fixtures_stack_;
        }

        QString width;
        QString height;
        QStack<Fixture> fixtures_stack_;
        QString errorStr;
    }handler;

    QXmlSimpleReader xmlReader;
    xmlReader.setContentHandler( &handler );
    xmlReader.setErrorHandler( &handler );

    qDebug() << "Parser starting";
    QFile file( in_path_ );
    bool ok = xmlReader.parse( QXmlInputSource( &file ) );

    if (!ok)
    {
        qDebug() << "Parser failed";
        emit failed(1);
        return;
    }

    qDebug() << "Parser success";
    qDebug() << "Output writting starting";

    QFile data( out_path_ );
    if( !data.open(QFile::WriteOnly | QFile::Truncate) )
    {
        qDebug() << "Writting to output failed";
        emit failed(1);
        return;
    }

    if( handler.fixtures().empty() )
    {
        qDebug() << "no data";
        emit success();
        return;
    }



     QTextStream out( &data );
     out << "{\n\
       \"name\": \"" << (*handler.fixtures().begin()).name << "\",\n\
       \"height\": " << handler.height << ",\n\
       \"width\": " << handler.width << ",\n\
       \"fixtures\" : [\n";

    for( QStack<Handler::Fixture>::const_iterator it = handler.fixtures().begin(); it != handler.fixtures().end(); ++it )
    {
        qDebug() << "Fixture: " << (*it).uid << " " << (*it).x << " " << (*it).y << " " << (*it).dmx_channel << " " << (*it).dmx_universe;
        int universe = atoi(  qPrintable( (*it).dmx_universe ) );
        if( universe > 0 ) universe--;

        out << "\t\t" << "{\n";
        out << "\t\t" << "\"name\":\"" << (*it).name << "\",\n";
        out << "\t\t" << "\"path\":\"../data/fixtures/" << (*it).uid << "\",\n";
        out << "\t\t" << "\"universe\":" << universe << ",\n";
        out << "\t\t" << "\"channel\":" << (*it).dmx_channel << ",\n";
        out << "\t\t" << "\"x_offset\":" << (*it).x << ",\n";
        out << "\t\t" <<  "\"y_offset\":" << (*it).y << "\n";
        out << "\t\t" << "}";

        if( it+1 != handler.fixtures().end() )
            out << ",\n";

         //todo: if file exists from prev. start it will not be truncated
        if( !QFile::exists( (*it).uid ) )
        {
           QFile fxt_data( (*it).uid );
           if( !fxt_data.open(QFile::WriteOnly | QFile::Truncate) )
           {
                qDebug() << "Writting to fxt failed";
                emit failed(1);
                return;
           }

           QTextStream fxt_out( &fxt_data );
           fxt_out << "{\n\
            \"name\": \"" << (*handler.fixtures().begin()).name << "\",\n\
            \"height\": " << (*handler.fixtures().begin()).height << ",\n\
            \"width\": " << (*handler.fixtures().begin()).width << ",\n\
            \"part\" : [\n";

           for( QStringList::const_iterator jt = (*it).channels.begin(); jt != (*it).channels.end(); ++jt )
           {
               fxt_out << "\t\t\"" << (*jt) << "\"";

               if( jt+1 != (*it).channels.end() )
                   fxt_out << ",\n";
           }

           fxt_out << "\n]}";
        }
        else qDebug() << "\tFixture file already exists, skip: " << (*it).uid;
    }

    out << "\n]}";

    qDebug() << "Output writting success";
    emit success();
}
