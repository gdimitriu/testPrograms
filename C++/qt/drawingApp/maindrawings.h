#ifndef MAINDRAWINGS_H
#define MAINDRAWINGS_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QLinkedList>

class MainDrawings : public QMainWindow
{
    Q_OBJECT
public slots:
   void paintEvent(QPaintEvent * event);
private slots:
   void openFile();
   void saveAs();
public:
    MainDrawings(QWidget *parent = 0);
    ~MainDrawings();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    void createMenu();
    QLinkedList<QLinkedList<QPoint> *> *pointsLists;
    QPoint lastPos;
    QLinkedList<QPoint> *currentDrawing;
    bool isTracking;
    QAction *openFileAction;
    QAction *saveAsAction;
    QMenu *fileMenu;
};

#endif // MAINDRAWINGS_H
