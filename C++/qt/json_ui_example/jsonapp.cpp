#include <QFileDialog>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include "jsonapp.h"
#include "ui_jsonapp.h"

JsonApp::JsonApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JsonApp)
{
    ui->setupUi(this);
    createMenu();
}

JsonApp::~JsonApp()
{
    delete ui;
}

void JsonApp::loadServers()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load file with servers"), ".", tr("json files (*.json)"));
    if ( !fileName.isEmpty() ) {
        ui->servers->clear();
        servers.clear();
        QFile loadFile(fileName);
        if (!loadFile.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
            return;
        }
        QByteArray saveData = loadFile.readAll();

        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        read(loadDoc.object());
    }
}

void JsonApp::read(const QJsonObject &json)
{
    QJsonArray serversArray = json["servers"].toArray();

    for (int serversIndex = 0; serversIndex < serversArray.size(); ++serversIndex) {
        QJsonObject levelObject = serversArray[serversIndex].toObject();
        ServerObject *server = new ServerObject(this);
        server->read(levelObject);
        servers.append(server);
        ui->servers->addItem(server->getServerName());
    }
}

void JsonApp::saveServers()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file with servers"), ".", tr("json files (*.json)"));
    if ( !fileName.isEmpty() ) {
        QFile saveFile(fileName);
        if (!saveFile.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
            return;
        }
        QJsonObject object;
        write(object);
        QJsonDocument saveDoc(object);
        saveFile.write(saveDoc.toJson());
    }
}

void JsonApp::write(QJsonObject &json)
{
    QJsonArray serversArray;
    foreach (const ServerObject *server, servers) {
        QJsonObject serverObject;
        server->write(serverObject);
        serversArray.append(serverObject);
    }
    json["servers"] = serversArray;
}

void JsonApp::createMenu()
{
    loadAction = new QAction(tr("&Load"), this);
    loadAction->setShortcut(tr("Ctrl+L"));
    loadAction->setStatusTip(tr("Load servers"));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(loadServers()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save servers"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveServers()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);

    connect(ui->servers, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(displayServer(QListWidgetItem*)));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(add()));
}

void JsonApp::displayServer(QListWidgetItem *item)
{
    QString serverName = item->text();
    for ( int i = 0 ;i < servers.size(); ++i )
    {
        if (servers.at(i)->getServerName() == serverName )
        {
            ServerObject *object = servers.at(i);
            ui->ipValue->clear();
            ui->ipValue->setText(object->getIpName());
            ui->portValue->clear();
            ui->portValue->setText(object->getPortName());
            break;
        }
    }
}

void JsonApp::add()
{
    ServerObject *server = new ServerObject(this, ui->name->text(), ui->ipValue->text(), ui->portValue->text());
    servers.append(server);
    ui->servers->addItem(server->getServerName());
    ui->addButton->clearFocus();
}
