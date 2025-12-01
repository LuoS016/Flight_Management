#ifndef PASSENGER_H
#define PASSENGER_H

#include <QDockWidget>  // 改为 QDockWidget
#include <QSqlDatabase>

namespace Ui {
class passenger;
}

class passenger : public QDockWidget  // 改为继承 QDockWidget
{
    Q_OBJECT

public:
    explicit passenger(QWidget *parent = nullptr);
    explicit passenger(const QString &username, QWidget *parent = nullptr);
    ~passenger();

    void setUsername(const QString &username);

signals:
    void backRequested();

private slots:
    void on_btn_add_clicked();
    void on_btn_refresh_clicked();
    void on_btn_close_clicked();
    void onDeletePassenger();

private:
    Ui::passenger *ui;
    QString currentUsername;

    void initTable();
    void loadPassengers();
    int getUserId();
    bool validateInput();
    void clearInput();
};

#endif // PASSENGER_H
