#ifndef RELEASE_TASK_H
#define RELEASE_TASK_H

#include "user.h"
#include <QMainWindow>
#include <QButtonGroup>
#include <QRadioButton>
#include <QString>

namespace Ui {
class Release_Task;
}

/*********************************************************************************************
【类名】            Regist
【功能】            用于发布任务
【接口说明】         接口用于发布任务
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Release_Task : public QMainWindow
{
    Q_OBJECT

public:
    explicit Release_Task(User user,QWidget *parent = nullptr);
    virtual ~Release_Task();
    Release_Task(const Release_Task& r_t);
    Release_Task operator=(const Release_Task& r_t);

private slots:
    //发布任务键的槽函数，用于发布任务
    void on_pushButton_release_clicked();
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();

private:
    Ui::Release_Task *ui;
    QButtonGroup* TypeGroup;
    User user;
};

#endif // RELEASE_TASK_H
