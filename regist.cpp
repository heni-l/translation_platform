#include "regist.h"
#include "ui_regist.h"
#include "dbms.h"

//构造函数
Regist::Regist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Regist)
{
    ui->setupUi(this);
}

//析构函数
Regist::~Regist()
{
    delete ui;
}

//注册键的槽函数，用于创建账户
void Regist::on_pushButton_regist_clicked()
{
    QString regist_name = this->ui->lineEdit_name->text();
    QString regist_password = this->ui->lineEdit_password->text();
    QString regist_phonenumber = this->ui->lineEdit_PhoneNumber->text();
    QString regist_mailbox = this->ui->lineEdit_mailbox->text();
    QString regist_prove = this->ui->lineEdit_prove->text();
    DBMS dbms;
    QMessageBox msg_box;
    //判断用户名是否已被占用，若是则报错
    if (dbms.UserSearchSucceeded(regist_name)){
            msg_box.setText("用户名已被占用");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
    else{
        if (regist_name != nullptr && regist_password != nullptr && regist_phonenumber != nullptr
            && regist_mailbox != nullptr && regist_prove != nullptr){
            User user(regist_name,regist_password,regist_phonenumber,regist_mailbox,regist_prove);
            //若注册时修改了语言资质证明，则设定初始积分为10
            if (regist_prove != "无"){
                user.InitAccumulatePoints(10);
            }
            dbms.NewUser(user);
            msg_box.setText("注册成功");
            msg_box.setWindowTitle("注册成功");
            msg_box.exec();
            close();
        }
        else {
            msg_box.setText("请输入完整信息");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
    }
}

//取消键的槽函数，用于退出注册
void Regist::on_pushButton_cancel_clicked()
{
    close();
}
