#ifndef MAINDRAWINGS_H
#define MAINDRAWINGS_H

#include <QMainWindow>
#include <QMouseEvent>

class MainDrawings : public QMainWindow
{
    Q_OBJECT
public slots:
   void paintEvent(QPaintEvent * event);
public:
    MainDrawings(QWidget *parent = 0);
    ~MainDrawings();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QList<QList<QPoint> *> *pointsLists;
    QPoint lastPos;
    QList<QPoint> *currentDrawing;
    bool isTracking;
};

#endif // MAINDRAWINGS_H
