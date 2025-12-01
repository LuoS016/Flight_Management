#include "edit_infor.h"
#include "ui_edit_infor.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QBuffer>
#include <QPixmap>
#include <QIODevice>
edit_infor::edit_infor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_infor)
{
    ui->setupUi(this);
}

edit_infor::edit_infor(QString userID,QString username,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_infor)
    , avatarChanged(false)  // 初始化为false，表示还没有选择新头像
{
    ui->setupUi(this);
    ui->old_name->setText(username);
    this->username=username;
    this->userID=userID;
    
    // 从数据库加载当前的简介和头像
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法加载用户信息";
    } else {
        QSqlQuery query;
        query.prepare("SELECT jianjie, avatar FROM users WHERE IDCard = ?");
        query.addBindValue(userID);
        if (query.exec() && query.next()) {
            this->jianjie = query.value(0).toString();
            ui->new_jianjie->setText(this->jianjie);
            
            // 加载当前头像到预览（但不标记为已更改）
            QByteArray avatarData = query.value(1).toByteArray();
            if (!avatarData.isEmpty()) {
                QPixmap pixmap;
                if (pixmap.loadFromData(avatarData)) {
                    this->Avatar = pixmap;
                    ui->label_5->setPixmap(pixmap.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
            }
        }
    }
    //connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&edit_infor::on_buttonBox_accepted);
}
void edit_infor:: on_buttonBox_accepted(){
    QString newUsername = ui->new_name->text().trimmed();
    QString newjianjie=ui->new_jianjie->text().trimmed();
    emit change_name(this->username,newUsername);
    emit change_jianjie(this->jianjie,newjianjie);
    this->close();
}
void edit_infor::accept()
{
    QString newUsername = ui->new_name->text().trimmed();
    QString newjianjie = ui->new_jianjie->text().trimmed();

    if (newUsername.isEmpty()) {
        return;
    }
    QSqlQuery query;
    QString sql;
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法修改记录！";
        return;
    }
    query.prepare("SELECT UserID FROM users WHERE IDCard = ?");
    query.addBindValue(this->userID);
    if (!query.exec() || !query.next()) {
        qDebug() << "无法找到用户，IDCard = " << this->userID;
        QMessageBox::warning(this, "警告", "无法找到用户信息");
        return;
    }
    QString actualUserID = query.value(0).toString();
    QByteArray avatarData;
    // 只有用户选择了新头像时才保存（使用avatarChanged标志）
    qDebug() << "accept()中检查头像，avatarChanged=" << this->avatarChanged << "，this->Avatar.isNull()=" << this->Avatar.isNull() << "，尺寸：" << this->Avatar.width() << "x" << this->Avatar.height();
    if (this->avatarChanged && !this->Avatar.isNull()) {
        QBuffer buffer(&avatarData);
        buffer.open(QIODevice::WriteOnly);
        this->Avatar.save(&buffer, "PNG");
        qDebug() << "准备保存新头像，大小：" << avatarData.size() << "字节，Avatar尺寸：" << this->Avatar.width() << "x" << this->Avatar.height();
    } else {
        qDebug() << "用户未选择新头像，不更新头像字段（保持数据库中的旧头像）";
    }
    if (this->avatarChanged && !this->Avatar.isNull()) {
        sql = "UPDATE users SET username=?, jianjie=?, avatar=? WHERE UserID=?";
        query.prepare(sql);
        query.addBindValue(newUsername);
        query.addBindValue(newjianjie);
        query.addBindValue(avatarData);
        query.addBindValue(actualUserID);
        qDebug() << "更新用户信息（包含头像），UserID=" << actualUserID;
    } else {
        sql = "UPDATE users SET username=?, jianjie=? WHERE UserID=?";
        query.prepare(sql);
        query.addBindValue(newUsername);
        query.addBindValue(newjianjie);
        query.addBindValue(actualUserID);
        qDebug() << "更新用户信息（不包含头像），UserID=" << actualUserID;
    }

    if (!query.exec()) {
        qDebug() << "修改记录失败：" << query.lastError().text();
        qDebug() << "执行的 SQL：" << sql;
        QMessageBox::warning(this, "警告", "执行sql失败");
        return;
    }
    if (query.numRowsAffected() > 0) {
        qDebug() << "成功修改" << query.numRowsAffected() << "条记录，UserID=" << actualUserID;
        emit change_name(this->username, newUsername);
        emit change_jianjie(this->jianjie,newjianjie);
        if (this->avatarChanged && !this->Avatar.isNull()) {
            emit change_avatar(this->Avatar);
        }
        QDialog::accept();
    } else {
        qDebug() << "未找到匹配的记录（或新值与旧值一致），无修改";
        QMessageBox::warning(this, "警告", "未找到匹配的记录（或新值与旧值一致），无修改");
        return;
    }
}
edit_infor::~edit_infor()
{
    delete ui;
}

void edit_infor::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("选择头像"),QString(),tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (filePath.isEmpty()) {
        return;
    }
    QPixmap image(filePath);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("无效图片"), tr("无法加载所选文件。"));
        return;
    }
    QPixmap scaledPixmap = image.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_5->setPixmap(scaledPixmap);
    this->Avatar = scaledPixmap;
    this->avatarChanged = true;
    qDebug() << "选择新头像，更新this->Avatar，尺寸：" << this->Avatar.width() << "x" << this->Avatar.height() << "，avatarChanged=true";
    emit change_avatar(scaledPixmap);
}

