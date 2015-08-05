#pragma once
#include <QObject>
#include <QString>

class Parser : public QObject
{
    Q_OBJECT

public:

    Parser( QObject *o = 0 ) :
        QObject( o )
    {}

    bool Init( const QString &in_path, const QString &out_path  );
    void convert() { start(); }

signals:
    void success();
    void failed(int error);

public slots:

    void start();

private:

    QString in_path_;
    QString out_path_;
};



