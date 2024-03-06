#include "listapplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListApplication w;
    w.show();

    return a.exec();
}
