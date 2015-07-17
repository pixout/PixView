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

     bool Load( const QString &path );
     bool Save();
     enum Position { Vertical, Horizontal };

signals:
      void portChanged();
      void fixturePathChanged();
      void positionChanged();

private:
      int port_;
      QString fixture_path_;

      union {
      Position position_;
      int position_int_;
      };

      QString settings_path_;

};

#endif // APPSETTINGS_H
