#include "info.h"
#include "ui_info.h"
#include "dbms.h"

//构造函数
Info::Info(User user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info),
    user(user)
{
    ui->setupUi(this);
    model=new QSqlQueryModel;
    model->setQuery("select name as 用户名,phonenumber as 手机号,mailbox as 邮箱,prove as 语言资质证明,"
                    "accumulatepoints as 累积积分,balance as 余额 from User where name = '"+user.Getname()+"'");
    ui->tableView->setModel(model);
}

//析构函数
Info::~Info()
{
    delete model;
    delete ui;
}

//取消键的槽函数，用于退出当前界面
void Info::on_pushButton_cancel_clicked()
{
    close();
}

//修改信息键的槽函数，用于确认修改个人信息
void Info::on_pushButton_changeinfo_clicked()
{
    QString new_name = this->ui->lineEdit_name->text();
    QString new_password = this->ui->lineEdit_password->text();
    QString new_phonenumber = this->ui->lineEdit_PhoneNumber->text();
    QString new_mailbox = this->ui->lineEdit_mailbox->text();
    QString new_prove = this->ui->lineEdit_prove->text();
    DBMS dbms;
    QMessageBox msg_box;
    if (new_name == nullptr && new_password == nullptr && new_phonenumber == nullptr
            && new_mailbox == nullptr && new_prove == nullptr){
        msg_box.setText("请输入您要修改的信息");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
    else {
        if (new_name != nullptr && dbms.UserSearchSucceeded(new_name))
        {
            msg_box.setText("用户名已被占用");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
        else {
            QString old_name = user.Getname();
            if (new_name != nullptr){
                user.NewName(new_name);
            }
            if (new_password != nullptr){
                user.NewPassword(new_password);
            }
            if (new_phonenumber != nullptr){
                user.NewPhonenumber(new_phonenumber);
            }
            if (new_mailbox != nullptr){
                user.NewMailbox(new_mailbox);
            }
            if (new_prove != nullptr){
                user.NewProve(new_prove);
            }
            dbms.UpdateUser(old_name,user);
            msg_box.setText("个人信息修改成功");
            msg_box.setWindowTitle("成功");
            msg_box.exec();
            //修改个人信息后刷新界面
            model->setQuery("select name as 用户名,phonenumber as 手机号,mailbox as 邮箱,prove as 语言资质证明,"
                            "accumulatepoints as 累积积分,balance as 余额 from User where name = '"+user.Getname()+"'");
            ui->tableView->setModel(model);
        }
    }
}

//充值键的槽函数，用于充值指定的金额
void Info::on_pushButton_recharge_clicked()
{
    int recharge = this->ui->spinBox->value();
    DBMS dbms;
    QMessageBox msg_box;
    if (recharge == 0){
        msg_box.setText("请输入您要充值的金额");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
    else {
        user.Recharge(recharge);
        dbms.UpdateUser(user.Getname(),user);
        msg_box.setText(QString("充值%1元成功").arg(recharge));
        msg_box.setWindowTitle("充值成功");
        msg_box.exec();
        //充值成功后刷新界面
        model->setQuery("select name as 用户名,phonenumber as 手机号,mailbox as 邮箱,prove as 语言资质证明,"
                        "accumulatepoints as 累积积分,balance as 余额 from User where name = '"+user.Getname()+"'");
        ui->tableView->setModel(model);
    }
}
