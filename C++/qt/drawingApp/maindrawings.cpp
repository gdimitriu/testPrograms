#include <QPainter>
#include <iostream>
#include "maindrawings.h"

MainDrawings::MainDrawings(QWidget *parent)
    : QMainWindow(parent)
{
    pointsLists = new QList<QList<QPoint> *>();
    currentDrawing = nullptr;
    isTracking = false;
}

MainDrawings::~MainDrawings()
{
    for ( QList<QList<QPoint> *>::iterator itDrawings = pointsLists->begin(); itDrawings != pointsLists->end(); itDrawings++ ) {
        delete *itDrawings;
    }
    delete pointsLists;
}
void MainDrawings::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QRect rect = event->rect();
    painter.eraseRect(rect);

    QList<QList<QPoint> *>::iterator itDrawings;
    QList<QPoint>::iterator itPoints;
    for ( itDrawings = pointsLists->begin(); itDrawings != pointsLists->end(); itDrawings++) {
        itPoints = (*itDrawings)->begin();
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap));
        for ( ; itPoints != (*itDrawings)->end(); itPoints++) {
            painter.drawPoint(*itPoints);
        }
    }
}

void MainDrawings::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() != Qt::RightButton ) {
        isTracking = false;
        return;
    }
    isTracking = true;
    if ( currentDrawing == nullptr )
        currentDrawing = new QList<QPoint> ();
    pointsLists->append(currentDrawing);
    currentDrawing->append(event->pos());
    update();
}

void MainDrawings::mouseReleaseEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::RightButton ) {
        currentDrawing->append(event->pos());
        currentDrawing = nullptr;
        isTracking = false;
        update();
    }
}

void MainDrawings::mouseMoveEvent(QMouseEvent *event)
{
    if ( isTracking ) {
        currentDrawing->append(event->pos());
        update();
    }
}
