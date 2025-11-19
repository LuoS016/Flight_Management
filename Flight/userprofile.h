#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>

namespace Ui {
class UserProfile;
}

class UserProfile : public QWidget
{
    Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = nullptr);
    ~UserProfile();

signals:
    void backRequested(); // 定义返回信号
    void myOrdersRequested();
    void logoutRequested();
private slots:
    void on_btn_back_clicked();
    void on_pushButton_4_clicked(); // 我的订单
    void on_pushButton_8_clicked(); // 注册
    void on_pushButton_7_clicked(); // 登录
    void on_pushButton_9_clicked(); // 注销

private:
    Ui::UserProfile *ui;
};

#endif // USERPROFILE_H
