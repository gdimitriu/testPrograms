#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainapplication.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->launchButton, SIGNAL(clicked(bool)), this, SLOT(launchApp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchApp()
{

    app = new MainApplication(this);
//    app->setWindowFlags(Qt::Widget);
//    setCentralWidget(app);
    app->show();
    ui->launchButton->clearFocus();
}
