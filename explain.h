#ifndef EXPLAIN_H
#define EXPLAIN_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class explain; }
QT_END_NAMESPACE

class explain : public QWidget
{
    Q_OBJECT

public:
    explicit explain(QWidget *parent = nullptr);
    ~explain();

private:
    Ui::explain *ui;
};
#endif // EXPLAIN_H
