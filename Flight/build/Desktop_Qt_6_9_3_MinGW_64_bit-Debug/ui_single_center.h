/********************************************************************************
** Form generated from reading UI file 'single_center.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLE_CENTER_H
#define UI_SINGLE_CENTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Single_Center
{
public:
    QLabel *label_title;
    QPushButton *btn_refresh;
    QTableWidget *tableWidget_orders;
    QPushButton *btn_back;

    void setupUi(QWidget *Single_Center)
    {
        if (Single_Center->objectName().isEmpty())
            Single_Center->setObjectName("Single_Center");
        Single_Center->resize(1000, 700);
        Single_Center->setAutoFillBackground(false);
        Single_Center->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_title = new QLabel(Single_Center);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(10, 9, 981, 51));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_title->setFont(font);
        label_title->setAutoFillBackground(false);
        label_title->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 59, 59); \n"
"color: rgb(255, 255, 255); \n"
"border-radius: 6px;          "));
        btn_refresh = new QPushButton(Single_Center);
        btn_refresh->setObjectName("btn_refresh");
        btn_refresh->setGeometry(QRect(900, 20, 80, 30));
        btn_refresh->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        tableWidget_orders = new QTableWidget(Single_Center);
        tableWidget_orders->setObjectName("tableWidget_orders");
        tableWidget_orders->setGeometry(QRect(10, 70, 981, 580));
        tableWidget_orders->setStyleSheet(QString::fromUtf8("QTableView {\n"
"    background-color: rgb(45, 45, 45);\n"
"    color: #ffffff;\n"
"    gridline-color: rgb(96, 96, 96); \n"
"    border: 1px solid rgb(96, 96, 96); \n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: rgb(45, 45, 45); \n"
"    color: #ffffff;\n"
"    padding: 4px;\n"
"    font-weight: bold;\n"
"    font-size: 13px;\n"
"\n"
"    border: none; \n"
"    border-right: 1px solid rgb(96, 96, 96);\n"
"    border-bottom: 1px solid rgb(255, 255, 255); \n"
"}\n"
"\n"
"QTableCornerButton::section {\n"
"    background-color: rgb(45, 45, 45);\n"
"    border: none;\n"
"    border-right: 1px solid rgb(96, 96, 96);\n"
"    border-bottom: 1px solid #rgb(96, 96, 96);\n"
"}"));
        tableWidget_orders->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableWidget_orders->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        btn_back = new QPushButton(Single_Center);
        btn_back->setObjectName("btn_back");
        btn_back->setGeometry(QRect(800, 20, 81, 31));
        btn_back->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        retranslateUi(Single_Center);

        QMetaObject::connectSlotsByName(Single_Center);
    } // setupUi

    void retranslateUi(QWidget *Single_Center)
    {
        Single_Center->setWindowTitle(QCoreApplication::translate("Single_Center", "\344\270\252\344\272\272\344\270\255\345\277\203 - \346\210\221\347\232\204\350\256\242\345\215\225", nullptr));
        label_title->setText(QCoreApplication::translate("Single_Center", "  \346\210\221\347\232\204\350\256\242\345\215\225", nullptr));
        btn_refresh->setText(QCoreApplication::translate("Single_Center", "\345\210\267\346\226\260", nullptr));
        btn_back->setText(QCoreApplication::translate("Single_Center", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Single_Center: public Ui_Single_Center {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLE_CENTER_H
