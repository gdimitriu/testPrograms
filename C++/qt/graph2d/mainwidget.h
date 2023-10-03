#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

class MainWidget : public QWidget
{
    Q_OBJECT
private slots:
    void repaint();
public slots:
   void paintEvent(QPaintEvent * event);
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
private:
    void drawPie(QPainter *painter);
    void drawElipse(QPainter *painter);
    void drawBessier(QPainter *painter);
    void drawRotate(QPainter *painter);
    void drawTranslateAndRotate(QPainter *painter);
    void drawTransform(QPainter *painter);
    int execution;
    QTimer *timer;
    int nrOfDrawings;
    QRect rect;
};

#endif // MAINWIDGET_H
