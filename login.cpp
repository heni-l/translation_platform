#include "login.h"
#include "ui_login.h"
#include "dbms.h"

//构造函数
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

//析构函数
Login::~Login()
{
    delete reg;
    delete platform;
    delete ui;
}

//注册键的槽函数，用于进入注册界面
void Login::on_pushButton_regist_clicked()
{
   reg = new Regist;
   reg->show();
}

//登录键的槽函数，匹配用户名和密码并登录平台
void Login::on_pushButton_login_clicked()
{
    QString Inputname = this->ui->lineEdit_name->text();
    QString Inputpassword = this->ui->lineEdit_password->text();
    DBMS dbms;
    if(dbms.UserMatchingSucceeded(Inputname,Inputpassword)){
        platform = new Platform(dbms.GetUser(Inputname));
        platform->show();
        //close();
    }
    //若用户名和密码不匹配，则报错
    else{
        QMessageBox msg_box;
        msg_box.setText("用户名或密码错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}

//取消键的槽函数，用于退出当前界面
void Login::on_pushButton_cancel_clicked()
{
    close();
}

//以下两个槽函数用于输入完用户名或密码后按回车键登录，内容与登录键的槽函数相同，只是增加了按回车键登录的功能
void Login::on_lineEdit_name_returnPressed()
{
    QString Inputname = this->ui->lineEdit_name->text();
    QString Inputpassword = this->ui->lineEdit_password->text();
    DBMS dbms;
    if(dbms.UserMatchingSucceeded(Inputname,Inputpassword)){
        platform = new Platform(dbms.GetUser(Inputname));
        platform->show();
        //close();
    }
    else{
        QMessageBox msg_box;
        msg_box.setText("用户名或密码错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}

void Login::on_lineEdit_password_returnPressed()
{
    QString Inputname = this->ui->lineEdit_name->text();
    QString Inputpassword = this->ui->lineEdit_password->text();
    DBMS dbms;
    if(dbms.UserMatchingSucceeded(Inputname,Inputpassword)){
        platform = new Platform(dbms.GetUser(Inputname));
        platform->show();
        //close();
    }
    else{
        QMessageBox msg_box;
        msg_box.setText("用户名或密码错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}
