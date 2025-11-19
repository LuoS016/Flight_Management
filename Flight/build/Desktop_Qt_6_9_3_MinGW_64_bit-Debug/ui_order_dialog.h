/********************************************************************************
** Form generated from reading UI file 'order_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDER_DIALOG_H
#define UI_ORDER_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_OrderDialog
{
public:
    QGroupBox *groupBox_ticket;
    QLabel *label_type_label;
    QLabel *label_type;
    QLabel *label_ticketNo_label;
    QLabel *label_ticketNo;
    QLabel *label_route_label;
    QLabel *label_route;
    QLabel *label_departure_label;
    QLabel *label_departure;
    QLabel *label_arrival_label;
    QLabel *label_arrival;
    QLabel *label_price_label;
    QLabel *label_price;
    QLabel *label_company_label;
    QLabel *label_company;
    QLabel *label_available_label;
    QLabel *label_available;
    QGroupBox *groupBox_passenger;
    QLabel *label_name;
    QLineEdit *lineEdit_name;
    QLabel *label_id;
    QLineEdit *lineEdit_id;
    QLabel *label_phone;
    QLineEdit *lineEdit_phone;
    QLabel *label_count;
    QSpinBox *spinBox_count;
    QLabel *label_total_label;
    QLabel *label_total;
    QPushButton *btn_confirm;
    QPushButton *btn_cancel;

    void setupUi(QDialog *OrderDialog)
    {
        if (OrderDialog->objectName().isEmpty())
            OrderDialog->setObjectName("OrderDialog");
        OrderDialog->resize(500, 450);
        OrderDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        groupBox_ticket = new QGroupBox(OrderDialog);
        groupBox_ticket->setObjectName("groupBox_ticket");
        groupBox_ticket->setGeometry(QRect(20, 20, 460, 180));
        groupBox_ticket->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_type_label = new QLabel(groupBox_ticket);
        label_type_label->setObjectName("label_type_label");
        label_type_label->setGeometry(QRect(20, 30, 60, 20));
        label_type_label->setStyleSheet(QString::fromUtf8(""));
        label_type = new QLabel(groupBox_ticket);
        label_type->setObjectName("label_type");
        label_type->setGeometry(QRect(70, 30, 100, 20));
        label_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_ticketNo_label = new QLabel(groupBox_ticket);
        label_ticketNo_label->setObjectName("label_ticketNo_label");
        label_ticketNo_label->setGeometry(QRect(220, 30, 60, 20));
        label_ticketNo_label->setStyleSheet(QString::fromUtf8(""));
        label_ticketNo = new QLabel(groupBox_ticket);
        label_ticketNo->setObjectName("label_ticketNo");
        label_ticketNo->setGeometry(QRect(290, 30, 150, 20));
        label_ticketNo->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_route_label = new QLabel(groupBox_ticket);
        label_route_label->setObjectName("label_route_label");
        label_route_label->setGeometry(QRect(20, 60, 60, 20));
        label_route = new QLabel(groupBox_ticket);
        label_route->setObjectName("label_route");
        label_route->setGeometry(QRect(80, 60, 350, 20));
        label_route->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_departure_label = new QLabel(groupBox_ticket);
        label_departure_label->setObjectName("label_departure_label");
        label_departure_label->setGeometry(QRect(20, 90, 60, 20));
        label_departure = new QLabel(groupBox_ticket);
        label_departure->setObjectName("label_departure");
        label_departure->setGeometry(QRect(60, 90, 121, 20));
        label_departure->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_arrival_label = new QLabel(groupBox_ticket);
        label_arrival_label->setObjectName("label_arrival_label");
        label_arrival_label->setGeometry(QRect(220, 90, 60, 20));
        label_arrival = new QLabel(groupBox_ticket);
        label_arrival->setObjectName("label_arrival");
        label_arrival->setGeometry(QRect(270, 90, 150, 20));
        label_arrival->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_price_label = new QLabel(groupBox_ticket);
        label_price_label->setObjectName("label_price_label");
        label_price_label->setGeometry(QRect(20, 120, 60, 20));
        label_price = new QLabel(groupBox_ticket);
        label_price->setObjectName("label_price");
        label_price->setGeometry(QRect(90, 120, 100, 20));
        label_price->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_company_label = new QLabel(groupBox_ticket);
        label_company_label->setObjectName("label_company_label");
        label_company_label->setGeometry(QRect(220, 120, 60, 20));
        label_company = new QLabel(groupBox_ticket);
        label_company->setObjectName("label_company");
        label_company->setGeometry(QRect(290, 120, 150, 20));
        label_company->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_available_label = new QLabel(groupBox_ticket);
        label_available_label->setObjectName("label_available_label");
        label_available_label->setGeometry(QRect(20, 150, 60, 20));
        label_available = new QLabel(groupBox_ticket);
        label_available->setObjectName("label_available");
        label_available->setGeometry(QRect(90, 150, 100, 20));
        label_available->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        groupBox_passenger = new QGroupBox(OrderDialog);
        groupBox_passenger->setObjectName("groupBox_passenger");
        groupBox_passenger->setGeometry(QRect(20, 210, 460, 150));
        groupBox_passenger->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_name = new QLabel(groupBox_passenger);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(20, 30, 60, 20));
        lineEdit_name = new QLineEdit(groupBox_passenger);
        lineEdit_name->setObjectName("lineEdit_name");
        lineEdit_name->setGeometry(QRect(90, 28, 200, 25));
        lineEdit_name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_id = new QLabel(groupBox_passenger);
        label_id->setObjectName("label_id");
        label_id->setGeometry(QRect(20, 65, 60, 20));
        lineEdit_id = new QLineEdit(groupBox_passenger);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(90, 63, 200, 25));
        lineEdit_id->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_phone = new QLabel(groupBox_passenger);
        label_phone->setObjectName("label_phone");
        label_phone->setGeometry(QRect(20, 100, 60, 20));
        lineEdit_phone = new QLineEdit(groupBox_passenger);
        lineEdit_phone->setObjectName("lineEdit_phone");
        lineEdit_phone->setGeometry(QRect(90, 98, 200, 25));
        lineEdit_phone->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_count = new QLabel(groupBox_passenger);
        label_count->setObjectName("label_count");
        label_count->setGeometry(QRect(310, 30, 60, 20));
        spinBox_count = new QSpinBox(groupBox_passenger);
        spinBox_count->setObjectName("spinBox_count");
        spinBox_count->setGeometry(QRect(380, 28, 60, 25));
        spinBox_count->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        spinBox_count->setMinimum(1);
        spinBox_count->setMaximum(10);
        spinBox_count->setValue(1);
        label_total_label = new QLabel(groupBox_passenger);
        label_total_label->setObjectName("label_total_label");
        label_total_label->setGeometry(QRect(310, 65, 60, 20));
        label_total = new QLabel(groupBox_passenger);
        label_total->setObjectName("label_total");
        label_total->setGeometry(QRect(380, 65, 51, 20));
        btn_confirm = new QPushButton(OrderDialog);
        btn_confirm->setObjectName("btn_confirm");
        btn_confirm->setGeometry(QRect(280, 380, 80, 30));
        btn_cancel = new QPushButton(OrderDialog);
        btn_cancel->setObjectName("btn_cancel");
        btn_cancel->setGeometry(QRect(380, 380, 80, 30));

        retranslateUi(OrderDialog);

        QMetaObject::connectSlotsByName(OrderDialog);
    } // setupUi

    void retranslateUi(QDialog *OrderDialog)
    {
        OrderDialog->setWindowTitle(QCoreApplication::translate("OrderDialog", "\345\241\253\345\206\231\350\256\242\345\215\225\344\277\241\346\201\257", nullptr));
        groupBox_ticket->setTitle(QCoreApplication::translate("OrderDialog", "\347\245\250\345\212\241\344\277\241\346\201\257", nullptr));
        label_type_label->setText(QCoreApplication::translate("OrderDialog", "\347\261\273\345\236\213\357\274\232", nullptr));
        label_type->setText(QString());
        label_ticketNo_label->setText(QCoreApplication::translate("OrderDialog", "\347\274\226\345\217\267\357\274\232", nullptr));
        label_ticketNo->setText(QString());
        label_route_label->setText(QCoreApplication::translate("OrderDialog", "\350\267\257\347\272\277\357\274\232", nullptr));
        label_route->setText(QString());
        label_departure_label->setText(QCoreApplication::translate("OrderDialog", "\345\207\272\345\217\221\357\274\232", nullptr));
        label_departure->setText(QString());
        label_arrival_label->setText(QCoreApplication::translate("OrderDialog", "\345\210\260\350\276\276\357\274\232", nullptr));
        label_arrival->setText(QString());
        label_price_label->setText(QCoreApplication::translate("OrderDialog", "\345\215\225\344\273\267\357\274\232", nullptr));
        label_price->setText(QString());
        label_company_label->setText(QCoreApplication::translate("OrderDialog", "\345\205\254\345\217\270\357\274\232", nullptr));
        label_company->setText(QString());
        label_available_label->setText(QCoreApplication::translate("OrderDialog", "\345\217\257\347\224\250\357\274\232", nullptr));
        label_available->setText(QString());
        groupBox_passenger->setTitle(QCoreApplication::translate("OrderDialog", "\344\271\230\345\256\242\344\277\241\346\201\257", nullptr));
        label_name->setText(QCoreApplication::translate("OrderDialog", "\345\247\223\345\220\215\357\274\232", nullptr));
        lineEdit_name->setPlaceholderText(QCoreApplication::translate("OrderDialog", "\350\257\267\350\276\223\345\205\245\344\271\230\345\256\242\345\247\223\345\220\215", nullptr));
        label_id->setText(QCoreApplication::translate("OrderDialog", "\350\272\253\344\273\275\350\257\201\357\274\232", nullptr));
        lineEdit_id->setPlaceholderText(QCoreApplication::translate("OrderDialog", "\350\257\267\350\276\223\345\205\245\350\272\253\344\273\275\350\257\201\345\217\267", nullptr));
        label_phone->setText(QCoreApplication::translate("OrderDialog", "\347\224\265\350\257\235\357\274\232", nullptr));
        lineEdit_phone->setPlaceholderText(QCoreApplication::translate("OrderDialog", "\350\257\267\350\276\223\345\205\245\350\201\224\347\263\273\347\224\265\350\257\235", nullptr));
        label_count->setText(QCoreApplication::translate("OrderDialog", "\346\225\260\351\207\217\357\274\232", nullptr));
        label_total_label->setText(QCoreApplication::translate("OrderDialog", "\346\200\273\344\273\267\357\274\232", nullptr));
        label_total->setStyleSheet(QCoreApplication::translate("OrderDialog", "color: red; font-weight: bold;", nullptr));
        label_total->setText(QCoreApplication::translate("OrderDialog", "0.00 \345\205\203", nullptr));
        btn_confirm->setText(QCoreApplication::translate("OrderDialog", "\347\241\256\350\256\244\350\256\242\347\245\250", nullptr));
        btn_cancel->setText(QCoreApplication::translate("OrderDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderDialog: public Ui_OrderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDER_DIALOG_H
