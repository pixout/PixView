#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>

class AppSettings : public QObject
{
    Q_OBJECT
    Q_ENUMS(Position)
    Q_PROPERTY(int port MEMBER port_ NOTIFY portChanged)
    Q_PROPERTY(QString fixturePath MEMBER fixture_path_ NOTIFY fixturePathChanged)
    Q_PROPERTY(Position position MEMBER position_ NOTIFY positionChanged)

public:
    explicit AppSettings(QObject *parent = 0);
    ~AppSettings();

     enum Position { Vertical, Horizontal };

signals:
      void portChanged();
      void fixturePathChanged();
      void positionChanged();

private:
      int port_;
      QString fixture_path_;
      Position position_;

};

#endif // APPSETTINGS_H
