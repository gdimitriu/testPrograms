#include "displayimages.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DisplayImages w;
    w.show();

    return a.exec();
}
