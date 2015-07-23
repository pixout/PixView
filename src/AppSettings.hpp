#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QUrl>

class AppSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port MEMBER port_ NOTIFY portChanged)
    Q_PROPERTY(QString fixturePath MEMBER fixture_path_ NOTIFY fixturePathChanged)
    Q_PROPERTY(Position position MEMBER position_ NOTIFY positionChanged)
    Q_PROPERTY(QUrl appPath MEMBER app_path_ CONSTANT)

public:
    explicit AppSettings(QObject *parent = 0);
    ~AppSettings();

    Q_INVOKABLE QString stripURLFromPath( const QString &path );
    Q_INVOKABLE bool load( const QString &path );
     bool Save( const QString &path );
     enum Position { Vertical, Horizontal };
    Q_ENUMS(Position)

     int port() const { return port_; }
     const QString& fixturePath() const { return fixture_path_; }
     QString& fixturePath() { return fixture_path_; }
     Position position() const { return position_; }

//     static void declareQML();

signals:
      void portChanged();
      void fixturePathChanged();
      void positionChanged();
      void onLoaded();

private:
      int port_;
      QString fixture_path_;

      union {
      Position position_;
      int position_int_;
      };

      QString settings_path_;
      QUrl app_path_;

};

#endif // APPSETTINGS_H
