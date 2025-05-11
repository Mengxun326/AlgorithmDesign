#ifndef MYAUTHOR_H
#define MYAUTHOR_H

#include <QWidget>

namespace Ui {
class myauthor;
}

class myauthor : public QWidget
{
    Q_OBJECT

public:
    explicit myauthor(QWidget *parent = nullptr);
    ~myauthor();

private:
    Ui::myauthor *ui;
};

#endif // MYAUTHOR_H
