#include "webdisplay.h"
#include "ui_webdisplay.h"

WebDisplay::WebDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WebDisplay)
{
    ui->setupUi(this);
    QUrl url("https://www.hotnews.ro/");
    ui->webEngineView->load(url);
}

WebDisplay::~WebDisplay()
{
    delete ui;
}
