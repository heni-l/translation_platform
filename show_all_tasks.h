#ifndef SHOW_ALL_TASKS_H
#define SHOW_ALL_TASKS_H

#include "user.h"
#include <QDialog>
#include <QSpinBox>
#include <QSqlQueryModel>

namespace Ui {
class Show_All_Tasks;
}

/*********************************************************************************************
【类名】            Show_All_Tasks
【功能】            用于显示所有任务
【接口说明】         接口用于报名负责或翻译
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Show_All_Tasks : public QDialog
{
    Q_OBJECT

public:
    explicit Show_All_Tasks(User user,QWidget *parent = nullptr);
    virtual ~Show_All_Tasks();
    Show_All_Tasks(const Show_All_Tasks& s_a_t);
    Show_All_Tasks operator=(const Show_All_Tasks& s_a_t);

private slots:
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();
    //参与负责键的槽函数，用于报名负责任务
    void on_pushButton_resp_clicked();
    //参与翻译键的槽函数，用于报名翻译任务
    void on_pushButton_trsl_clicked();

private:
    Ui::Show_All_Tasks *ui;
    User user;
    QSqlQueryModel* model;
};

#endif // SHOW_ALL_TASKS_H
