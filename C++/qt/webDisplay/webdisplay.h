#ifndef WEBDISPLAY_H
#define WEBDISPLAY_H

#include <QMainWindow>

namespace Ui {
class WebDisplay;
}

class WebDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit WebDisplay(QWidget *parent = 0);
    ~WebDisplay();

private:
    Ui::WebDisplay *ui;
};

#endif // WEBDISPLAY_H
