#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createActions();
    createMenus();
    setAttribute(Qt::WA_DeleteOnClose);

    QAction *openPopupAction = new QAction(tr("&Open"), this);
    openPopupAction->setShortcut(tr("Ctrl+O"));
    openPopupAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openPopupAction, SIGNAL(triggered()), this, SLOT(open()));
    isTracking = false;
    isDrawingLine = false;
    isDrawingPoints = false;
    currentLine = nullptr;
    lineList = new QList<QPair<QPoint,QPoint> *>();
}

MainWindow::~MainWindow()
{

}

QMenu *MainWindow::createPopupMenu() {
    return new QMenu(this);
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save spreadsheet file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));


    editAction = new QAction(tr("&Edit"), this);
    editAction->setShortcut(tr("Ctrl+E"));
    editAction->setStatusTip(tr("Edit location"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));

    drawLineAction = new QAction(tr("&Line"), this);
    drawLineAction->setShortcut(tr("Ctrl+L"));
    drawLineAction->setStatusTip(tr("Line between elements"));
    connect(drawLineAction, SIGNAL(triggered()), this, SLOT(drawLine()));

    drawPointsAction = new QAction(tr("&Points"), this);
    drawPointsAction->setShortcut(tr("Ctrl+P"));
    drawPointsAction->setStatusTip(tr("Draw points"));
    connect(drawPointsAction, SIGNAL(triggered()), this, SLOT(drawPoints()));

}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    if ( isTracking ) {
        event->accept();
        return;
    }
    QMenu popupMenu(this);
    popupMenu.addAction(drawLineAction);
    popupMenu.addAction(drawPointsAction);
    popupMenu.exec(event->globalPos());
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(editAction);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() != Qt::RightButton ) {
        isTracking = false;
        return;
    }
    if ( isDrawingLine ) {
        isTracking = true;
        currentLine = new QPair<QPoint, QPoint>();
        currentLine->first = event->pos();
        currentLine->second = event->pos();
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QRect rect = event->rect();
    painter.eraseRect(rect);

    QList<QPair<QPoint,QPoint> *>::iterator itDrawings;
    for ( itDrawings = lineList->begin(); itDrawings != lineList->end(); itDrawings++) {
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap));
        painter.drawLine((*itDrawings)->first, (*itDrawings)->second);
    }
    if ( currentLine != nullptr ) {
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap));
        painter.drawLine(currentLine->first, currentLine->second);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::RightButton && isTracking) {
        isTracking = false;
        currentLine->second = event->pos();
        lineList->append(currentLine);
        currentLine = nullptr;
        update();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ( isTracking ) {
        currentLine->second = event->pos();
        update();
    }
}

void MainWindow::drawLine() {
    isDrawingLine = true;
    isDrawingPoints = false;
}

void MainWindow::drawPoints() {
    isDrawingLine = false;
    isDrawingPoints = true;
}

void MainWindow::newFile() {
    QMessageBox::information(this, tr("NewFile"), tr("This is the callback"), QMessageBox::Yes | QMessageBox::Default);
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text files (*.txt)"));
    if ( !fileName.isEmpty() )
        QMessageBox::information(this, tr("Sucessfull open file"), fileName, QMessageBox::Yes);
}

bool MainWindow::save() {
    QMessageBox::information(this, tr("Sucessfull saved file"), tr("Just OK."), QMessageBox::Yes);
    return true;
}

void MainWindow::edit() {
    QMessageBox::information(this, tr("Sucessfull Edit file"), tr("Just OK."), QMessageBox::Yes);
}
