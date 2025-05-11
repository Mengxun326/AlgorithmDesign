#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pic1("://pic/pic1.png");
    ui->pic_label->setPixmap(pic1);
    connect(ui->action_A,SIGNAL(triggered()),this,SLOT(on_auther_clicked()));
    connect(ui->action_Y,SIGNAL(triggered()),this,SLOT(on_explain_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_auther_clicked()
{
    myauthor *c = new myauthor();
    c->setWindowModality(Qt::ApplicationModal);
    c->show();
}

void MainWindow::on_explain_clicked()
{
    explain *c = new explain();
    c->setWindowModality(Qt::ApplicationModal);
    c->show();
}

// 快速选择算法实现
int quickSelect(std::vector<int>& nums, int low, int high, int k) {
    int pivotIndex = low + (high - low) / 2;
    std::swap(nums[pivotIndex], nums[high]);
    int storeIndex = low;
    for (int i = low; i < high; ++i) {
        if (nums[i] < nums[high]) {
            std::swap(nums[storeIndex], nums[i]);
            ++storeIndex;
        }
    }
    std::swap(nums[storeIndex], nums[high]);

    if (k == storeIndex) {
        return nums[k];
    } else if (k < storeIndex) {
        return quickSelect(nums, low, storeIndex - 1, k);
    } else {
        return quickSelect(nums, storeIndex + 1, high, k);
    }
}


/**
 * 第K小元素（分治算法）
 * @brief MainWindow::on_pushButton_1_clicked
 * @author WangZhiJie
 */
void MainWindow::on_pushButton_1_clicked()
{
    QString inputText = ui->plainTextEdit_in1->toPlainText();
    std::istringstream iss(inputText.toStdString());
    int n, k;
    if (!(iss >> n)) {
        QMessageBox::warning(this, "错误", "输入格式错误，请检查输入的整数个数n");
        return;
    }
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        if (!(iss >> nums[i])) {
            QMessageBox::warning(this, "错误", "输入格式错误，请检查输入的整数序列");
            return;
        }
    }
    if (!(iss >> k)) {
        QMessageBox::warning(this, "错误", "输入格式错误，请检查输入的k值");
        return;
    }
    if (k > n || k <= 0) {
        QMessageBox::warning(this, "错误", "k值超出范围，请确保1 <= k <= n");
        return;
    }
    int result = quickSelect(nums, 0, n - 1, k - 1);
    ui->plainTextEdit_out1->setPlainText(QString::number(result));
}

/**
 * 选择问题（分治算法）
 * @brief MainWindow::on_pushButton_2_clicked
 * @author WangZhiJie
 */
void MainWindow::on_pushButton_2_clicked()
{
    QString inputText = ui->plainTextEdit_in2->toPlainText();
    std::istringstream iss(inputText.toStdString());

    int n, k;
    // 读取n和k
    if (!(iss >> n >> k) || k < 1 || k >= n || n > 100) {
        QMessageBox::warning(this, "输入错误", "请正确输入n和k，确保1≤k<n≤100");
        return;
    }

    std::vector<int> nums(n);
    // 读取整数数组
    for (int i = 0; i < n; ++i) {
        if (!(iss >> nums[i])) {
            QMessageBox::warning(this, "输入错误", "请正确输入整数数组");
            return;
        }
    }

    int result = quickSelect(nums, 0, n - 1, k - 1);
    ui->plainTextEdit_out2->setPlainText(QString::number(result));
}

// 计算字符串表示的数字
long long calculateNumber(const QString &str) {
    return str.toLongLong();
}

// 动态规划计算最大乘积
long long maxProduct(const QString &numStr, int numMultipliers) {
    int n = numStr.length();
    if (numMultipliers >= n - 1) {
        return calculateNumber(numStr);
    }
    long long dp[n][numMultipliers + 1];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= numMultipliers; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        dp[i][0] = calculateNumber(numStr.left(i + 1));
    }

    for (int j = 1; j <= numMultipliers; ++j) {
        for (int i = j; i < n; ++i) {
            for (int k = j - 1; k < i; ++k) {
                dp[i][j] = std::max(dp[i][j], dp[k][j - 1] * calculateNumber(numStr.mid(k + 1, i - k)));
            }
        }
    }

    return dp[n - 1][numMultipliers];
}

/**
 * 数字串分解（动态规划）
 * @brief MainWindow::on_pushButton_3_clicked
 * @author WangZhiJie
 */
void MainWindow::on_pushButton_3_clicked()
{
    QString input = ui->plainTextEdit_in3->toPlainText().trimmed();
    QStringList lines = input.split('\n', Qt::SkipEmptyParts);

    // 验证输入是否至少有两行
    if (lines.size() < 2) {
        QMessageBox::warning(this, "输入错误", "请输入两行：第一行为x y，第二行为数字字符串");
        return;
    }

    // 解析第一行的 x 和 y
    QStringList params = lines[0].split(' ', Qt::SkipEmptyParts);
    if (params.size() != 2) {
        QMessageBox::warning(this, "输入错误", "第一行应包含两个整数 x 和 y，用空格分隔");
        return;
    }

    bool ok1, ok2;
    int x = params[0].toInt(&ok1);
    int y = params[1].toInt(&ok2);

    // 验证 x 和 y 是否为有效整数
    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "输入错误", "x 和 y 必须是有效的整数");
        return;
    }

    // 根据题目要求调整验证范围
    if (x < 1 || y < 0 || y >= x) {
        QMessageBox::warning(this, "输入错误",
                             QString("无效的参数：x 必须 ≥1，y 必须满足 0 ≤ y < x (当前 x=%1, y=%2)")
                                 .arg(x).arg(y));
        return;
    }

    // 获取第二行的数字字符串
    QString numberStr = lines[1].trimmed();

    // 验证数字字符串长度
    if (numberStr.length() != x) {
        QMessageBox::warning(this, "输入错误",
                             QString("数字字符串长度应为 %1，但实际为 %2")
                                 .arg(x).arg(numberStr.length()));
        return;
    }

    // 计算并显示结果
    long long result = maxProduct(numberStr, y);
    ui->plainTextEdit_out3->setPlainText(QString::number(result));
}

// 记忆化搜索函数，用于计算从某个点出发的最长滑坡长度
int MainWindow::dfs(std::vector<std::vector<int>>& heights, std::vector<std::vector<int>>& dp, int i, int j, int rows, int cols) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int maxLen = 1;

    for (int k = 0; k < 4; ++k) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && heights[ni][nj] < heights[i][j]) {
            maxLen = std::max(maxLen, 1 + dfs(heights, dp, ni, nj, rows, cols));
        }
    }

    dp[i][j] = maxLen;
    return maxLen;
}

/**
 * 滑雪（动态规划）
 * @brief MainWindow::on_pushButton_4_clicked
 * @author WangZhiJie
 */
void MainWindow::on_pushButton_4_clicked()
{
    QString inputText = ui->plainTextEdit_in4->toPlainText();
    QTextStream in(&inputText);

    int rows, cols;
    in >> rows >> cols;

    std::vector<std::vector<int>> heights(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            in >> heights[i][j];
        }
    }

    std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, -1));
    int maxLength = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maxLength = std::max(maxLength, dfs(heights, dp, i, j, rows, cols));
        }
    }

    QString result = QString::number(maxLength);
    ui->plainTextEdit_out4->setPlainText(result);
}

// 判断点是否在马的控制范围内
bool MainWindow::isInHorseControl(int x, int y, int horseX, int horseY) {
    if (x == horseX && y == horseY) return true;
    int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    for (int i = 0; i < 8; ++i) {
        int newX = horseX + dx[i];
        int newY = horseY + dy[i];
        if (x == newX && y == newY) return true;
    }
    return false;
}

// 计算路径条数
int MainWindow::calculatePaths(int n, int m, int horseX, int horseY) {
    int dp[21][21];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 && j == 0) continue;
            if (isInHorseControl(i, j, horseX, horseY)) {
                dp[i][j] = 0;
            } else {
                dp[i][j] += (i > 0? dp[i - 1][j] : 0);
                dp[i][j] += (j > 0? dp[i][j - 1] : 0);
            }
        }
    }
    return dp[n][m];
}

/**
 * 马拦过河卒（动态规划）
 * @brief MainWindow::on_pushButton_5_clicked
 * @author WangZhiJie
 */
void MainWindow::on_pushButton_5_clicked()
{
    QString input = ui->plainTextEdit_in5->toPlainText();
    QStringList parts = input.split(' ');
    if (parts.size() != 4) {
        QMessageBox::warning(this, "警告", "输入格式错误，请输入n m 马的x坐标 马的y坐标");
        return;
    }

    bool ok;
    int n = parts[0].toInt(&ok);
    if (!ok || n < 0 || n > 20) {
        QMessageBox::warning(this, "警告", "n输入错误，必须是0到20之间的整数");
        return;
    }
    int m = parts[1].toInt(&ok);
    if (!ok || m < 0 || m > 20) {
        QMessageBox::warning(this, "警告", "m输入错误，必须是0到20之间的整数");
        return;
    }
    int horseX = parts[2].toInt(&ok);
    if (!ok || horseX < 0 || horseX > 20) {
        QMessageBox::warning(this, "警告", "马的x坐标输入错误，必须是0到20之间的整数");
        return;
    }
    int horseY = parts[3].toInt(&ok);
    if (!ok || horseY < 0 || horseY > 20) {
        QMessageBox::warning(this, "警告", "马的y坐标输入错误，必须是0到20之间的整数");
        return;
    }
    int paths = calculatePaths(n, m, horseX, horseY);
    ui->plainTextEdit_out5->setPlainText(QString::number(paths));

}

/**
 * 安排工作以达到最大收益（贪心算法）
 * @brief MainWindow::on_pushButton_6_clicked
 * @author WangZhiJie
 */
void MainWindow::on_pushButton_6_clicked()
{
    QString input = ui->plainTextEdit_in6->toPlainText();
    QTextStream in(&input);

    int n, m;
    in >> n >> m;
    if (in.status() != QTextStream::Ok) {
        ui->plainTextEdit_out6->setPlainText("输入格式错误，请按照格式输入：n m");
        return;
    }

    std::vector<int> difficulty(n), profit(n), worker(m);
    for (int i = 0; i < n; ++i) {
        in >> difficulty[i] >> profit[i];
        if (in.status() != QTextStream::Ok) {
            ui->plainTextEdit_out6->setPlainText("输入格式错误，请按照格式输入：difficulty[i] profit[i]");
            return;
        }
    }
    for (int i = 0; i < m; ++i) {
        in >> worker[i];
        if (in.status() != QTextStream::Ok) {
            ui->plainTextEdit_out6->setPlainText("输入格式错误，请按照格式输入：worker[i]");
            return;
        }
    }

    std::sort(difficulty.begin(), difficulty.end());
    std::sort(profit.begin(), profit.end());
    std::sort(worker.begin(), worker.end());

    int maxProfit = 0;
    for (int i = 0; i < m; ++i) {
        auto it = std::upper_bound(difficulty.begin(), difficulty.end(), worker[i]);
        if (it != difficulty.begin()) {
            --it;
            int index = it - difficulty.begin();
            maxProfit += profit[index];
        }
    }

    ui->plainTextEdit_out6->setPlainText(QString::number(maxProfit));
}

