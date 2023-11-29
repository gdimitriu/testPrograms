#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QContextMenuEvent>
#include <QPair>
#include <QList>
#include <QPoint>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void paintEvent(QPaintEvent * event);
private slots:
    void newFile();
    void open();
    bool save();
    void edit();
    void drawLine();
    void drawPoints();
private:
    void createActions();
    void createMenus();
    virtual QMenu *createPopupMenu();
public:
    MainWindow(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *event);
    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *editAction;
    QAction *drawLineAction;
    QAction *drawPointsAction;
    bool isDrawingLine;
    bool isDrawingPoints;
    bool isTracking;
    QPair<QPoint, QPoint> *currentLine;
    QList<QPair<QPoint, QPoint> *> *lineList;
};

#endif // MAINWINDOW_H
