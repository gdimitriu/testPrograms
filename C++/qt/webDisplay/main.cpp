#include "webdisplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebDisplay w;
    w.show();

    return a.exec();
}
