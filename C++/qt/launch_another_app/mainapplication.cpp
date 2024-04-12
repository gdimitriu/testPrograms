#include "mainapplication.h"
#include "ui_mainapplication.h"

MainApplication::MainApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApplication)
{    
    ui->setupUi(this);
    connect(ui->firstEntryButton, SIGNAL(clicked(bool)), this, SLOT(putFirstEntry()));
    connect(ui->secondEntryButton, SIGNAL(clicked(bool)), this, SLOT(putSecondEntry()));
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearEntries()));
}

MainApplication::~MainApplication()
{
    delete ui;
}

void MainApplication::putFirstEntry()
{
    ui->firstEntry->clear();
    ui->firstEntry->setText(QString("first entry"));
    ui->firstEntryButton->clearFocus();
}

void MainApplication::putSecondEntry()
{
    ui->secondEntry->clear();
    ui->secondEntry->setText(QString("second entry"));
    ui->secondEntryButton->clearFocus();
}

void MainApplication::clearEntries()
{
    ui->firstEntry->clear();
    ui->secondEntry->clear();
    ui->clearButton->clearFocus();
}
