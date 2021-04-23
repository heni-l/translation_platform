#include "show_all_tasks.h"
#include "ui_show_all_tasks.h"
#include "dbms.h"

//构造函数
Show_All_Tasks::Show_All_Tasks(User user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_All_Tasks),
    user(user)
{
    ui->setupUi(this);
    model=new QSqlQueryModel;
    model->setQuery("select taskid as 编号,nameofreleasedpreason as 发布人,briefintroduction as 任务简介,"
                    "content as 任务内容,deadlineoftask as 任务截止日期,deadlineofrecruitmentpersonincharge as 负责人报名截止日期,"
                    "totalpay as 任务总金额,type as 任务类型,stateofrecruitmentpersonincharge as 负责人招募,"
                    "nameofpersonincharge as 负责人,stateofrecruitmenttranslator as 译者招募 from Task");
    ui->tableView->setModel(model);
}

//析构函数
Show_All_Tasks::~Show_All_Tasks()
{
    delete model;
    delete ui;
}

//取消键的槽函数，用于退出当前界面
void Show_All_Tasks::on_pushButton_cancel_clicked()
{
    close();
}

//参与负责键的槽函数，用于报名负责任务
void Show_All_Tasks::on_pushButton_resp_clicked()
{
    int InputId = 0;
    InputId = this->ui->spinBox_id->value();
    DBMS dbms;
    QMessageBox msg_box;
    if (dbms.TaskIdMatch(InputId)){
        if (dbms.HasResponsiblePerson(InputId)){
            msg_box.setText("该任务已有负责人");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
        else {
            if (dbms.IsMyReleasedTask(user.Getname(),InputId)){
                msg_box.setText("任务发布者不能同时负责该任务");
                msg_box.setWindowTitle("提示");
                msg_box.exec();
            }
            else {
                if (user.CanBeResponsibleForTask()){
                    if (dbms.IHaveWantedToResponse(user.Getname(),InputId)){
                        msg_box.setText("您已报名负责该任务");
                        msg_box.setWindowTitle("错误");
                        msg_box.exec();
                    }
                    else {
                        dbms.WantToResponse(InputId,user.Getname());
                        msg_box.setText("报名负责成功,等待发布者审核");
                        msg_box.setWindowTitle("成功");
                        msg_box.exec();
                    }
                }
                else {
                    msg_box.setText("积分不足");
                    msg_box.setWindowTitle("错误");
                    msg_box.exec();
                }
            }
        }
    }
    else {
        msg_box.setText("任务编号错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}

//参与翻译键的槽函数，用于报名翻译任务
void Show_All_Tasks::on_pushButton_trsl_clicked()
{
    int InputId = 0;
    InputId = this->ui->spinBox_id->value();
    DBMS dbms;
    QMessageBox msg_box;
    if (dbms.TaskIdMatch(InputId)){
        if (dbms.HasTranslator(InputId)){
            msg_box.setText("该任务已有译者");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
        else {
            if (dbms.IsMyReleasedTask(user.Getname(),InputId)){
                msg_box.setText("任务发布者不能同时翻译该任务");
                msg_box.setWindowTitle("提示");
                msg_box.exec();
            }
            else {
                if (dbms.IHaveWantedToTranslate(user.Getname(),InputId)){
                    msg_box.setText("您已报名翻译该任务");
                    msg_box.setWindowTitle("错误");
                    msg_box.exec();
                }
                else {
                    dbms.WantToTranslate(InputId,user.Getname());
                    msg_box.setText("报名翻译成功,等待负责人审核");
                    msg_box.setWindowTitle("成功");
                    msg_box.exec();
                }
            }
        }
    }
    else {
        msg_box.setText("任务编号错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}
