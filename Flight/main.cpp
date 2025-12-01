<<<<<<< HEAD
<<<<<<< HEAD
#include "MainWindow.h"
#include <QApplication>
#include <QSqlDatabase>
=======
#include "MainWindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
>>>>>>> 251e7ba (修复ODBC连接和QSqlQuery使用问题，解决函数序列错误)
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase dbcon;
    dbcon = QSqlDatabase::addDatabase("QODBC");  // ODBC 驱动
<<<<<<< HEAD
    dbcon.setHostName("127.0.0.1");                // MySQL 服务器ip地址，本机
    dbcon.setPort(3306);                          // 端口号，默认
    dbcon.setDatabaseName("root");           // ODBC 数据源名称
    bool ok = dbcon.open();
    if(!ok)
        qDebug() << "Error,  persondatabase 数据库文件打开失败！";
    else
        qDebug() << "Sucess, persondatabase 数据库文件打开成功！";
=======
    
    // 设置ODBC连接选项，避免"函数序列错误"
    // SQL_ATTR_ODBC_VERSION设置为SQL_OV_ODBC3，确保使用正确的ODBC版本
    dbcon.setConnectOptions("SQL_ATTR_ODBC_VERSION=3;");
    
    // 方法1：尝试直接使用数据源名称（不加DSN=前缀）
    QString dsn = "root";  // ODBC 数据源名称
    dbcon.setDatabaseName(dsn);
    
    bool ok = dbcon.open();
    if(!ok) {
        qDebug() << "方法1失败，尝试方法2...";
        qDebug() << "错误信息：" << dbcon.lastError().text();
        
        // 方法2：使用完整的Unicode驱动连接字符串
        // 注意：需要根据实际安装的MySQL ODBC驱动名称调整
        // 常见的驱动名称：MySQL ODBC 8.0 Unicode Driver, MySQL ODBC 8.1 Unicode Driver 等
        dbcon.close();
        QString connectionString = "DRIVER={MySQL ODBC 8.0 Unicode Driver};"
                                   "SERVER=127.0.0.1;"
                                   "PORT=3306;"
                                   "DATABASE=flight;"
                                   "USER=root;"
                                   "PASSWORD=328168;"
                                   "OPTION=3;";
        dbcon.setDatabaseName(connectionString);
        ok = dbcon.open();
        
        if(!ok) {
            qDebug() << "方法2也失败，尝试方法3...";
            qDebug() << "错误信息：" << dbcon.lastError().text();
            
            // 方法3：尝试使用DSN但包含用户名和密码
            dbcon.close();
            dbcon.setDatabaseName(QString("DSN=%1;UID=root;PWD=328168").arg(dsn));
            ok = dbcon.open();
        }
    }
    
    if(!ok) {
        qDebug() << "Error,  persondatabase 数据库文件打开失败！";
        qDebug() << "最终错误信息：" << dbcon.lastError().text();
        qDebug() << "错误代码：" << dbcon.lastError().nativeErrorCode();
        qDebug() << "提示：请检查ODBC数据源名称是否正确，或尝试使用完整的连接字符串";
    } else {
        qDebug() << "Sucess, persondatabase 数据库文件打开成功！";
        // Unicode ODBC驱动通常已经正确处理字符集，不需要额外的SET语句
        // 如果确实需要设置字符集，可以在第一次实际查询前执行
    }
>>>>>>> 251e7ba (修复ODBC连接和QSqlQuery使用问题，解决函数序列错误)

    MainWindow w;
    w.show();
    return a.exec();
}
<<<<<<< HEAD
=======
#include "MainWindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase dbcon;
    dbcon = QSqlDatabase::addDatabase("QODBC");  // ODBC 驱动
    dbcon.setHostName("127.0.0.1");                // MySQL 服务器ip地址，本机
    dbcon.setPort(3306);                          // 端口号，默认
    dbcon.setDatabaseName("root");           // ODBC 数据源名称
    bool ok = dbcon.open();
    if(!ok)
        qDebug() << "Error,  persondatabase 数据库文件打开失败！";
    else
        qDebug() << "Sucess, persondatabase 数据库文件打开成功！";

    MainWindow w;
    w.show();
    return a.exec();
}
>>>>>>> 424bc0a8b89776bc4a6d5328940fb4156ce50bcf
=======
>>>>>>> 251e7ba (修复ODBC连接和QSqlQuery使用问题，解决函数序列错误)
