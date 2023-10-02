#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void newFile();
    void open();
    bool save();
    void edit();
private:
    void createActions();
    void createMenus();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *editAction;
};

#endif // MAINWINDOW_H
