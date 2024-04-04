#include "serverobject.h"

ServerObject::ServerObject(QObject *parent) : QObject(parent)
{

}

ServerObject::ServerObject(QObject *parent, QString name, QString ip, QString port) : QObject(parent),
    ipName(ip), portName(port), serverName(name)
{

}

void ServerObject::read(const QJsonObject &json)
{
    serverName = json["name"].toString();
    ipName = json["ip"].toString();
    portName = json["port"].toString();
}

void ServerObject::write(QJsonObject &json) const
{
    json["name"] = serverName;
    json["ip"] = ipName;
    json["port"] = portName;
}

QString ServerObject::getIpName() const
{
    return ipName;
}

QString ServerObject::getPortName() const
{
    return portName;
}

QString ServerObject::getServerName() const
{
    return serverName;
}
