#ifndef INFO_H
#define INFO_H

#include "user.h"
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class Info;
}

/*********************************************************************************************
【类名】            Info
【功能】            用于显示个人信息以及提供修改信息的接口
【接口说明】         接口用于修改个人信息
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Info : public QDialog
{
    Q_OBJECT

public:
    explicit Info(User user,QWidget *parent = nullptr);
    virtual ~Info();
    Info(const Info& info);
    Info operator=(const Info& info);

private slots:
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();
    //修改信息键的槽函数，用于修改个人信息
    void on_pushButton_changeinfo_clicked();
    //充值键的槽函数，用于充值一定的金额
    void on_pushButton_recharge_clicked();

private:
    Ui::Info *ui;
    User user;
    QSqlQueryModel* model;
};

#endif // INFO_H
