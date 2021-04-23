#ifndef REGIST_H
#define REGIST_H

#include <QMainWindow>

namespace Ui {
class Regist;
}

/*********************************************************************************************
【类名】            Regist
【功能】            用于注册账户
【接口说明】         接口用于确认信息并注册账户
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Regist : public QMainWindow
{
    Q_OBJECT

public:
    explicit Regist(QWidget *parent = nullptr);
    virtual ~Regist();
    Regist(const Regist& regist);
    Regist operator=(const Regist& regist);

private slots:
    //注册键的槽函数，用于创建账户
    void on_pushButton_regist_clicked();
    //取消键的槽函数，用于退出注册
    void on_pushButton_cancel_clicked();

private :
    Ui::Regist *ui;
};

#endif // REGIST_H
