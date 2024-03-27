#include "displayimages.h"
#include "ui_displayimages.h"
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>

DisplayImages::DisplayImages(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayImages)
{
    ui->setupUi(this);
    openJpegAction = new QAction(tr("&Open Jpeg"), this);
    openJpegAction->setShortcut(tr("Ctrl+J"));
    openJpegAction->setStatusTip(tr("Open a jpeg file"));
    connect(openJpegAction, SIGNAL(triggered()), this, SLOT(openJpeg()));
    saveAsJpegAction = new QAction(tr("&Save as Jpeng"), this);
    saveAsJpegAction->setShortcut(tr("Ctrl+S"));
    saveAsJpegAction->setStatusTip(tr("Save as a jpeg file"));
    connect(saveAsJpegAction, SIGNAL(triggered(bool)), this, SLOT(saveAsJpeg()));
    fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openJpegAction);
    fileMenu->addAction(saveAsJpegAction);
}

DisplayImages::~DisplayImages()
{
    delete ui;
}

void DisplayImages::openJpeg()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open jpeg File"), ".", tr("Jpeg files (*.jpeg);;Jpg files (*.jpg)"));
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
    QPixmap image(fileName);
    int height = image.height();
    int width = image.width();
    item->setPixmap(image);
    ui->graphicsView->setFixedHeight(height);
    ui->graphicsView->setFixedWidth(width);
    this->setFixedHeight(height);
    this->setFixedWidth(width);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addItem(item);
    ui->graphicsView->show();
}

void DisplayImages::saveAsJpeg()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save jpeg File"), ".", tr("Jpeg files (*.jpeg);;Jpg files (*.jpg)"));
    if ( fileName.isEmpty() )
        return;
    QList<QGraphicsItem *> items = ui->graphicsView->scene()->items();
    if ( !items.isEmpty() ) {
        QGraphicsItem *item = items.at(0);
        dynamic_cast<QGraphicsPixmapItem *>(item)->pixmap().save(fileName);
    }
}
