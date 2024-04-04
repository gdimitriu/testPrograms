#ifndef JSONAPP_H
#define JSONAPP_H

#include <QMainWindow>
#include <QList>
#include <QMenu>
#include <QAction>
#include <QListWidgetItem>
#include "serverobject.h"

namespace Ui {
class JsonApp;
}

class JsonApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit JsonApp(QWidget *parent = 0);
    ~JsonApp();

public slots:
    void loadServers();
    void saveServers();
    void displayServer(QListWidgetItem *item);
    void add();
private:
    void createMenu();
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    Ui::JsonApp *ui;
    QList<ServerObject *> servers;
    QMenu *fileMenu;
    QAction *loadAction;
    QAction *saveAction;
};

#endif // JSONAPP_H
