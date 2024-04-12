#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QMainWindow>

namespace Ui {
class MainApplication;
}

class MainApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainApplication(QWidget *parent = 0);
    ~MainApplication();

private slots:
    void putFirstEntry();
    void putSecondEntry();
    void clearEntries();
private:
    Ui::MainApplication *ui;
};

#endif // MAINAPPLICATION_H
