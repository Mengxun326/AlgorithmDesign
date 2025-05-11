#include "explain.h"
#include "ui_explain.h"

explain::explain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::explain)
{
    ui->setupUi(this);
    // 打开资源文件
    QFile file(":/README.md");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法打开README文件!");
        return;
    }

    // 读取文件内容
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    // 显示到plainTextEdit
    ui->plainTextEdit->setPlainText(content);
}

explain::~explain()
{
    delete ui;
}
