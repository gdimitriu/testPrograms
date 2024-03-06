#ifndef LISTAPPLICATION_H
#define LISTAPPLICATION_H

#include <QMainWindow>

namespace Ui {
class ListApplication;
}

class ListApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListApplication(QWidget *parent = 0);
    ~ListApplication();
    enum class ITEM_POSITION {FIRST = 0, BEFORE = 1, CURRENT = 2, AFTER = 3, LAST = 4};
    Q_ENUM(ITEM_POSITION)

private:
    Ui::ListApplication *ui;

private slots:
    void addItem();
    void deleteItem();
    void moveItem();
    void replaceItem();
    void updateSelected(int pos);
};

#endif // LISTAPPLICATION_H
