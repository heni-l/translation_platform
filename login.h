#ifndef LOGIN_H
#define LOGIN_H

#include "regist.h"
#include "platform.h"

namespace Ui {
class Login;
}

/*********************************************************************************************
【类名】            Login
【功能】            用于登录或进入注册界面
【接口说明】         接口用于登录或注册
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    virtual ~Login();
    Login(const Login& login);
    Login operator=(const Login& login);

private slots:
    //注册键的槽函数，用于进入注册界面
    void on_pushButton_regist_clicked();
    //登录键的槽函数，用于登录平台
    void on_pushButton_login_clicked();
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();
    //以下两个槽函数用于输入完用户名或密码后按回车键登录
    void on_lineEdit_name_returnPressed();
    void on_lineEdit_password_returnPressed();

private:
    Ui::Login* ui;
    Regist* reg;
    Platform* platform;
};

#endif // LOGIN_H
