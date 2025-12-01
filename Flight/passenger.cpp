#include "passenger.h"
#include "ui_passenger.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
passenger::passenger(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::passenger)
{
    ui->setupUi(this);
    initTable();
}

passenger::passenger(const QString &username, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::passenger),
    currentUsername(username)
{
    ui->setupUi(this);
    initTable();
    loadPassengers();
}
void passenger::setUsername(const QString &username)
{
    currentUsername = username;
    loadPassengers(); // 设置用户名后立即加载乘客数据
}
void passenger::initTable()
{
    // 设置表格属性
    ui->table_passengers->setColumnCount(4);
    QStringList headers;
    headers << "姓名" << "身份证" << "手机号" << "操作";
    ui->table_passengers->setHorizontalHeaderLabels(headers);

    // 设置表格行为
    ui->table_passengers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_passengers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_passengers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_passengers->setAlternatingRowColors(true);

    // 设置列宽
    ui->table_passengers->setColumnWidth(0, 100);  // 姓名
    ui->table_passengers->setColumnWidth(1, 200);  // 身份证
    ui->table_passengers->setColumnWidth(2, 120);  // 手机号
    ui->table_passengers->horizontalHeader()->setStretchLastSection(true); // 操作列自动拉伸

    // 连接信号槽
    connect(ui->btn_add, &QPushButton::clicked, this, &passenger::on_btn_add_clicked);
    connect(ui->btn_refresh, &QPushButton::clicked, this, &passenger::on_btn_refresh_clicked);
    connect(ui->btn_close, &QPushButton::clicked, this, &passenger::on_btn_close_clicked);
}
int passenger::getUserId()
{
    if (currentUsername.isEmpty()) {
        QMessageBox::warning(this, "错误", "用户未登录！");
        return -1;
    }

    QSqlQuery query;
    query.prepare("SELECT UserID FROM users WHERE Username = ?");
    query.addBindValue(currentUsername);

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询用户失败：" + query.lastError().text());
        return -1;
    }

    if (!query.next()) {
        QMessageBox::warning(this, "错误", "用户不存在！");
        return -1;
    }

    return query.value(0).toInt();
}
void passenger::loadPassengers()
{
    int userId = getUserId();
    if (userId == -1) {
        return;
    }

    // 清空表格
    ui->table_passengers->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT PassengerID, Name, IDCard, Phone FROM passengers WHERE UserID = ? ORDER BY CreatedTime DESC");
    query.addBindValue(userId);

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "加载乘客数据失败：" + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->table_passengers->insertRow(row);

        // 获取数据
        int passengerId = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString idCard = query.value(2).toString();
        QString phone = query.value(3).toString();

        // 设置表格项
        ui->table_passengers->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_passengers->setItem(row, 1, new QTableWidgetItem(idCard));
        ui->table_passengers->setItem(row, 2, new QTableWidgetItem(phone));

        // 添加删除按钮
        QPushButton *btnDelete = new QPushButton("删除");
        btnDelete->setProperty("passengerId", passengerId);
        btnDelete->setProperty("passengerName", name);
        connect(btnDelete, &QPushButton::clicked, this, &passenger::onDeletePassenger);

        // 将按钮放入单元格
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->addWidget(btnDelete);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(2, 2, 2, 2);
        widget->setLayout(layout);

        ui->table_passengers->setCellWidget(row, 3, widget);

        row++;
    }

    // 如果没有数据，显示提示
    if (row == 0) {
        ui->table_passengers->setRowCount(1);
        ui->table_passengers->setItem(0, 0, new QTableWidgetItem("暂无乘客信息"));
        for (int i = 1; i < 4; i++) {
            ui->table_passengers->setItem(0, i, new QTableWidgetItem(""));
        }
        // 合并单元格显示提示信息
        ui->table_passengers->setSpan(0, 0, 1, 4);
    }
}
bool passenger::validateInput()
{
    QString name = ui->edit_name->text().trimmed();
    QString idCard = ui->edit_idcard->text().trimmed();
    QString phone = ui->edit_phone->text().trimmed();

    // 检查是否为空
    if (name.isEmpty() || idCard.isEmpty() || phone.isEmpty()) {
        return false;
    }

    // 验证姓名长度
    if (name.length() > 50) {
        QMessageBox::warning(this, "输入错误", "姓名长度不能超过50个字符！");
        return false;
    }

    // 验证身份证格式
    if (idCard.length() != 18) {
        QMessageBox::warning(this, "输入错误", "身份证号码必须是18位！");
        return false;
    }

    // 验证手机号格式
    if (phone.length() != 11) {
        QMessageBox::warning(this, "输入错误", "手机号必须是11位！");
        return false;
    }

    // 简单验证手机号是否为数字
    bool ok;
    phone.toLongLong(&ok);
    if (!ok) {
        QMessageBox::warning(this, "输入错误", "手机号必须为数字！");
        return false;
    }

    return true;
}
void passenger::clearInput()
{
    ui->edit_name->clear();
    ui->edit_idcard->clear();
    ui->edit_phone->clear();
    ui->edit_name->setFocus(); // 将焦点设置回姓名输入框
}

void passenger::on_btn_add_clicked()
{
    if (!validateInput()) {
        return;
    }

    int userId = getUserId();
    if (userId == -1) {
        return;
    }

    QString name = ui->edit_name->text().trimmed();
    QString idCard = ui->edit_idcard->text().trimmed();
    QString phone = ui->edit_phone->text().trimmed();

    QSqlQuery query;
    query.prepare("INSERT INTO passengers (UserID, Name, IDCard, Phone) VALUES (?, ?, ?, ?)");
    query.addBindValue(userId);
    query.addBindValue(name);
    query.addBindValue(idCard);
    query.addBindValue(phone);

    if (query.exec()) {
        QMessageBox::information(this, "成功", "乘客添加成功！");
        clearInput();
        loadPassengers(); // 刷新列表
    } else {
        QString error = query.lastError().text();
        if (error.contains("unique_user_idcard")) {
            QMessageBox::warning(this, "错误", "该身份证号码已存在！");
        } else {
            QMessageBox::critical(this, "错误", "添加失败：" + error);
        }
    }
}

void passenger::on_btn_refresh_clicked()
{
    loadPassengers();
    QMessageBox::information(this, "提示", "乘客列表已刷新！");
}

void passenger::on_btn_close_clicked()
{
    emit backRequested();
    this->close();
}

void passenger::onDeletePassenger()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int passengerId = btn->property("passengerId").toInt();
    QString passengerName = btn->property("passengerName").toString();

    // 确认删除
    int ret = QMessageBox::question(this, "确认删除",
                                    QString("确定要删除乘客\"%1\"吗？").arg(passengerName),
                                    QMessageBox::Yes | QMessageBox::No);

    if (ret != QMessageBox::Yes) {
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM passengers WHERE PassengerID = ?");
    query.addBindValue(passengerId);

    if (query.exec()) {
        QMessageBox::information(this, "成功", "乘客删除成功！");
        loadPassengers(); // 刷新列表
    } else {
        QMessageBox::critical(this, "错误", "删除失败：" + query.lastError().text());
    }
}
passenger::~passenger()
{
    delete ui;
}
