#ifndef PLATFORM_H
#define PLATFORM_H

#include "release_task.h"
#include "show_all_tasks.h"
#include "info.h"
#include "choose_person_in_charge.h"
#include "choose_translator.h"
#include "translate.h"
#include "view_result.h"
#include "view_final_result.h"
#include <QMainWindow>
#include <QSqlQueryModel>

namespace Ui {
class Platform;
}

/*********************************************************************************************
【类名】            Platform
【功能】            用于管理个人信息以及任务
【接口说明】         接口用于对查看个人信息或对任务进行相应的操作
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Platform : public QMainWindow
{
    Q_OBJECT

public:
    explicit Platform(User user,QWidget *parent = nullptr);
    virtual ~Platform();
    Platform(const Platform& platfrom);
    Platform operator=(const Platform& platfrom);

private slots:
    //发布任务键的槽函数，用于进入发布任务的界面
    void on_pushButton_ReleaseTask_clicked();
    //查看全部任务的槽函数，用于进入查看全部任务的界面
    void on_pushButton_AllTask_clicked();
    //查看个人信息的槽函数，用于进入查看个人信息的界面
    void on_pushButton_info_clicked();
    //退出键的槽函数，用于退出当前界面
    void on_pushButton_exit_clicked();
    //刷新键的槽函数，用于刷新当前界面
    void on_pushButton_refresh_clicked();
    //查看负责人报名状态键的槽函数，用于进入查看负责人报名状态的界面
    void on_pushButton_ManageReleased_clicked();
    //查看译者报名状态键的槽函数，用于进入查看译者报名状态的界面
    void on_pushButton_ManageResponsible_clicked();
    //获取原文键的槽函数，用于负责人获取原文
    void on_pushButton_getcontent_clicked();
    //翻译键的槽函数，用于译者进入翻译界面
    void on_pushButton_Translate_clicked();
    //查看译文的槽函数，用于负责人查看译者暂存或提交的译文
    void on_pushButton_viewresult_clicked();
    //查看最终译文的槽函数，用于任务发布者查看最终译文
    void on_pushButton_viewfinalresult_clicked();

private:
    Ui::Platform *ui;
    User user;
    QSqlQueryModel* model1;
    QSqlQueryModel* model2;
    QSqlQueryModel* model3;
    Show_All_Tasks* show_all_tasks;
    Release_Task* rls_task;
    Info* info;
    Choose_Person_In_Charge* c_p_i_c;
    Choose_Translator* c_t;
    Translate* translate;
    View_Result* viewresult;
    View_Final_Result* v_f_r;
};

#endif // PLATFORM_H
