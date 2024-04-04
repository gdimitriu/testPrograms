#ifndef SERVEROBJECT_H
#define SERVEROBJECT_H

#include <QJsonObject>
#include <QObject>

class ServerObject : public QObject
{
    Q_OBJECT
public:
    ServerObject(QObject *parent = nullptr);
    ServerObject(QObject *parent, QString name, QString ip, QString port);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    QString getIpName() const;
    QString getPortName() const;
    QString getServerName() const;
signals:

public slots:
private:
    QString ipName;
    QString portName;
    QString serverName;
};

#endif // SERVEROBJECT_H
