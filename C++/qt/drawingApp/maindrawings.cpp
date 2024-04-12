#include <QPainter>
#include <iostream>
#include "maindrawings.h"
#include <QGraphicsView>
#include <QFileDialog>
#include <QFile>
#include <QMenuBar>
#include <QDataStream>

MainDrawings::MainDrawings(QWidget *parent)
    : QMainWindow(parent)
{
    pointsLists = new QLinkedList<QLinkedList<QPoint> *>();
    currentDrawing = nullptr;
    isTracking = false;
    createMenu();
}

void MainDrawings::createMenu()
{
    openFileAction = new QAction(tr("&Open"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(tr("Open a drawing"));
    connect(openFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    saveAsAction = new QAction(tr("&SaveAs"),this);
    saveAsAction->setShortcut(tr("Ctrl+S"));
    saveAsAction->setStatusTip(tr("Save as the drawing"));
    connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveAs()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveAsAction);

}

MainDrawings::~MainDrawings()
{
    for ( QLinkedList<QLinkedList<QPoint> *>::iterator itDrawings = pointsLists->begin(); itDrawings != pointsLists->end(); itDrawings++ ) {
        delete *itDrawings;
    }
    delete pointsLists;
}

void MainDrawings::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QRect rect = event->rect();
    painter.eraseRect(rect);

    QLinkedList<QLinkedList<QPoint> *>::iterator itDrawings;
    QLinkedList<QPoint>::iterator itPoints;
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
        currentDrawing = new QLinkedList<QPoint> ();
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

void MainDrawings::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open drawing"), ".", tr("dat files (*.dat)"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream out(&file);
    pointsLists->clear();
    QLinkedList<QLinkedList<QPoint> *>::iterator it;
    int sz;
    out>>sz;
    for ( int i = 0; i < sz; ++i ) {
        currentDrawing = new QLinkedList<QPoint> ();
        out>>*currentDrawing;
        pointsLists->append(currentDrawing);
        currentDrawing = nullptr;
    }
    update();
    file.close();
}

void MainDrawings::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as ...  "), ".", tr("drawing files (*.dat)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    QLinkedList<QLinkedList<QPoint> *>::iterator it;
    out<<pointsLists->size();
    for ( it = pointsLists->begin(); it != pointsLists->end(); ++it) {
        out<<**it;
    }
    file.close();
}
