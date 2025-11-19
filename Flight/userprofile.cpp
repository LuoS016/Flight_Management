#include "userprofile.h"
#include "ui_userprofile.h"
#include "sign_in.h"
#include <QMessageBox>
UserProfile::UserProfile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    connect(ui->btn_back, &QPushButton::clicked, this, &UserProfile::on_btn_back_clicked);
}

UserProfile::~UserProfile()
{
    delete ui;
}
void UserProfile::on_btn_back_clicked()
{
    emit backRequested(); // 发送信号通知主窗口切换回去
}
void UserProfile::on_pushButton_4_clicked()
{
    emit myOrdersRequested();
}
void UserProfile::on_pushButton_8_clicked()
{
    Sign_in *s = new Sign_in();
    s->show();
}
void UserProfile::on_pushButton_7_clicked()
{
    emit logoutRequested();
}
void UserProfile::on_pushButton_9_clicked()
{
    int ret = QMessageBox::question(this, "注销", "确定要退出登录吗？",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        emit logoutRequested();
    }
}
