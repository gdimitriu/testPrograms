#include "listapplication.h"
#include "ui_listapplication.h"

ListApplication::ListApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListApplication)
{
    ui->setupUi(this);
    ui->itemPosition->addItem("First", QVariant::fromValue(ITEM_POSITION::FIRST));
    ui->itemPosition->addItem("Before", QVariant::fromValue(ITEM_POSITION::BEFORE));
    ui->itemPosition->addItem("Current", QVariant::fromValue(ITEM_POSITION::CURRENT));
    ui->itemPosition->addItem("After", QVariant::fromValue(ITEM_POSITION::AFTER));
    ui->itemPosition->addItem("Last", QVariant::fromValue(ITEM_POSITION::LAST));
    connect(ui->moveButton, SIGNAL(clicked(bool)), this, SLOT(moveItem()));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(addItem()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteItem()));
    connect(ui->replaceButton, SIGNAL(clicked(bool)), this, SLOT(replaceItem()));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(updateSelected(int)));
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearOutputLines()));
    connect(ui->inorderDisplayButton, SIGNAL(clicked(bool)), this, SLOT(inorderDisplay()));
    connect(ui->reverseDisplayButton, SIGNAL(clicked(bool)), this, SLOT(reverseDisplay()));
}

ListApplication::~ListApplication()
{
    delete ui;
}

void ListApplication::addItem()
{
    int currentRow = ui->listWidget->currentRow();
    switch((ITEM_POSITION) ui->itemPosition->currentData().value<ITEM_POSITION>() )
    {
    case ITEM_POSITION::FIRST :
        ui->listWidget->insertItem(0, ui->dataLine->text());
        break;
    case ITEM_POSITION::BEFORE :
        ui->listWidget->insertItem(currentRow - 1, ui->dataLine->text());
        break;
    case ITEM_POSITION::CURRENT :
        ui->listWidget->insertItem(currentRow, ui->dataLine->text());
        break;
    case ITEM_POSITION::AFTER :
        ui->listWidget->insertItem(currentRow + 1, ui->dataLine->text());
        break;
    case ITEM_POSITION::LAST :
        ui->listWidget->addItem(ui->dataLine->text());
        break;
    }
    ui->addButton->clearFocus();
}

void ListApplication::deleteItem()
{
    ui->listWidget->takeItem(ui->listWidget->currentRow());
    ui->deleteButton->clearFocus();
}

void ListApplication::moveItem()
{
    int currentPos = ui->listWidget->currentRow();
    QListWidgetItem *element = ui->listWidget->takeItem(currentPos);
    switch((ITEM_POSITION) ui->itemPosition->currentData().value<ITEM_POSITION>() )
    {
    case ITEM_POSITION::FIRST :
        ui->listWidget->insertItem(0, element);
        break;
    case ITEM_POSITION::BEFORE :
        ui->listWidget->insertItem(currentPos - 1, element);
        break;
    case ITEM_POSITION::CURRENT :
        break;
    case ITEM_POSITION::AFTER :
        ui->listWidget->insertItem(currentPos + 1, element);
        break;
    case ITEM_POSITION::LAST :
        ui->listWidget->addItem(element);
        break;
    }
    ui->moveButton->clearFocus();
}

void ListApplication::replaceItem()
{
    QListWidgetItem *element = ui->listWidget->currentItem();
    element->setText(ui->dataLine->text());
    ui->replaceButton->clearFocus();
}

void ListApplication::updateSelected(int pos)
{
    QListWidgetItem *element = ui->listWidget->currentItem();
    ui->dataLine->setText(element->text());
    repaint();
}

void ListApplication::clearOutputLines()
{
    ui->outputLines->clear();
    ui->clearButton->clearFocus();
}


void ListApplication::inorderDisplay()
{
    int nrOfItems  = ui->listWidget->count();
    for ( int i = 0; i < nrOfItems; ++i )
    {
        ui->outputLines->moveCursor(QTextCursor::End);
        ui->outputLines->insertPlainText(ui->listWidget->item(i)->text() + '\n');
    }
    ui->inorderDisplayButton->clearFocus();
}

void ListApplication::reverseDisplay()
{
    int nrOfItems  = ui->listWidget->count();
    for ( int i = nrOfItems - 1; i >= 0 ; --i )
    {
        ui->outputLines->moveCursor(QTextCursor::End);
        ui->outputLines->insertPlainText(ui->listWidget->item(i)->text() + '\n');
    }
    ui->reverseDisplayButton->clearFocus();
}
