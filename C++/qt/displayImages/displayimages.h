#ifndef DISPLAYIMAGES_H
#define DISPLAYIMAGES_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>

namespace Ui {
class DisplayImages;
}

class DisplayImages : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplayImages(QWidget *parent = 0);
    ~DisplayImages();

private:
    Ui::DisplayImages *ui;
    QMenu *fileMenu;
    QAction *openJpegAction;
    QAction *saveAsJpegAction;
private slots:
    void openJpeg();
    void saveAsJpeg();

};

#endif // DISPLAYIMAGES_H
