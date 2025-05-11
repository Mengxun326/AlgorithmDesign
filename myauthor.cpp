#include "myauthor.h"
#include "ui_myauthor.h"

myauthor::myauthor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myauthor)
{
    ui->setupUi(this);
}

myauthor::~myauthor()
{
    delete ui;
}
