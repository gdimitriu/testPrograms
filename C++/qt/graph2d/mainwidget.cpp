
#include "mainwidget.h"
#include <iostream>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    execution = 0;
    nrOfDrawings = 6;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(1000);
}

MainWidget::~MainWidget()
{

}

void MainWidget::repaint() {
    QWidget::repaint();
}

void MainWidget::paintEvent(QPaintEvent * event ) {
    std::cout<<"PaintEvent="<<execution<<std::endl;
    std::cout.flush();

    QPainter painter(this);
    rect = event->rect();
    painter.eraseRect(rect);

    switch (execution) {
    case 0:
        drawElipse(&painter);
        break;
    case 1:
        drawPie(&painter);
        break;
    case 2:
        drawBessier(&painter);
        break;
    case 3:
        drawRotate(&painter);
        break;
    case 4:
        drawTranslateAndRotate(&painter);
        break;
    case 5:
        drawTransform(&painter);
        break;
    }
    ++execution;
    if ( execution == nrOfDrawings ) {
        execution = 0;
    }
}

void MainWidget::drawElipse(QPainter *painter) {
    painter -> setRenderHint(QPainter::Antialiasing, true);
    painter -> setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    painter -> setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter -> drawEllipse(80, 80, 400, 240);
}

void MainWidget::drawPie(QPainter *painter) {
   painter -> setRenderHint(QPainter::Antialiasing);
   painter -> setRenderHint(QPainter::Antialiasing, true);
   painter -> setPen(QPen(Qt::black, 15, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
   painter -> setBrush(QBrush(Qt::blue, Qt::DiagCrossPattern));
   painter -> drawPie(80, 80, 400, 240, 60 * 16, 270 * 16);
}

void MainWidget::drawBessier(QPainter *painter) {
    painter -> setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.moveTo(80, 320);    
    path.cubicTo(200, 80, 320, 80, 480, 320);
    painter -> setPen(QPen(Qt::black, 8));
    painter -> drawPath(path);
}

void MainWidget::drawRotate(QPainter *painter) {
    QMatrix matrix;
    matrix.rotate(45.0);
    painter -> setMatrix(matrix);
    painter -> drawText(rect, Qt::AlignCenter, tr("This is a rotated text."));
}

void MainWidget::drawTranslateAndRotate(QPainter *painter) {
    QMatrix matrix;
    matrix.translate(200.0, -100.0);
    matrix.rotate(45.0);
    matrix.translate(-10.0, -20.0);
    painter -> setMatrix(matrix);
    painter -> drawText(rect, Qt::AlignCenter, tr("This is a translated and rotate text."));
}

void MainWidget::drawTransform(QPainter *painter) {
    painter -> translate(-10.0, -20.0);
    painter -> rotate(45.0);
    painter -> translate(+10.0, +20.0);
    painter -> drawText(rect, Qt::AlignCenter, tr("Text"));
}
