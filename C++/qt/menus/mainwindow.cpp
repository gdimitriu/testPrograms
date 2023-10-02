#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createActions();
    createPopupMenu();
    createMenus();
    setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{

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
