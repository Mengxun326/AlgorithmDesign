#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    int dfs(std::vector<std::vector<int>>& heights,
            std::vector<std::vector<int>>& dp,
            int i, int j, int rows, int cols);
    bool isInHorseControl(int x, int y, int horseX, int horseY);
    int calculatePaths(int n, int m, int horseX, int horseY);
};
#endif // MAINWINDOW_H
