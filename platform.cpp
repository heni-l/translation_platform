#include "platform.h"
#include "ui_platform.h"
#include "dbms.h"

//构造函数
Platform::Platform(User user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Platform),
    user(user)
{
    ui->setupUi(this);
    ui->label_name->setText(user.Getname());
    model1=new QSqlQueryModel;
    model2=new QSqlQueryModel;
    model3=new QSqlQueryModel;
    model1->setQuery("select taskid as 编号,briefintroduction as 任务简介,content as 任务内容,"
                     "deadlineoftask as 任务截止日期,deadlineofrecruitmentpersonincharge as 负责人报名截止日期,"
                     "totalpay as 任务总金额,type as 任务类型,stateofrecruitmentpersonincharge as 负责人招募,"
                     "nameofpersonincharge as 负责人 from Task where nameofreleasedpreason = '"+user.Getname()+"'");
    model2->setQuery("select taskid as 编号,nameofreleasedpreason as 发布人,briefintroduction as 任务简介,"
                     "content as 任务内容,deadlineoftask as 任务截止日期,totalpay as 任务总金额,type as 任务类型,"
                     "stateofrecruitmenttranslator as 译者招募,nameoftranslator1 as 译者1,"
                     "nameoftranslator2 as 译者2 from Task where nameofpersonincharge = '"+user.Getname()+"'");
    model3->setQuery("select taskid as 编号,nameofpersonincharge as 负责人,briefintroduction as 任务简介,"
                     "deadlineoftask as 任务截止日期,dividedcontent as 任务内容,stateoftranslation as 翻译状态"
                     " from Subtask where nameoftranslator = '"+user.Getname()+"'");
    ui->tableView_MyReleasedTask->setModel(model1);
    ui->tableView_MyResponsibleTask->setModel(model2);
    ui->tableView_MyTranslationTask->setModel(model3);
}

//析构函数
Platform::~Platform()
{
    delete c_t;
    delete c_p_i_c;
    delete show_all_tasks;
    delete rls_task;
    delete info;
    delete translate;
    delete viewresult;
    delete v_f_r;
    delete model1;
    delete model2;
    delete model3;
    delete ui;
}

//发布任务键的槽函数，用于进入发布任务的界面
void Platform::on_pushButton_ReleaseTask_clicked()
{
    rls_task = new Release_Task(user);
    rls_task->show();
}

//查看全部任务的槽函数，用于进入查看全部任务的界面
void Platform::on_pushButton_AllTask_clicked()
{
    show_all_tasks = new Show_All_Tasks(user);
    show_all_tasks->show();
}

//查看个人信息的槽函数，用于进入查看个人信息的界面
void Platform::on_pushButton_info_clicked()
{
    info = new Info(user);
    info->show();
}

//退出键的槽函数，用于退出当前界面
void Platform::on_pushButton_exit_clicked()
{
    close();
}

//刷新键的槽函数，用于刷新当前界面
void Platform::on_pushButton_refresh_clicked()
{
    model1->setQuery("select taskid as 编号,briefintroduction as 任务简介,content as 任务内容,"
                     "deadlineoftask as 任务截止日期,deadlineofrecruitmentpersonincharge as 负责人报名截止日期,"
                     "totalpay as 任务总金额,type as 任务类型,stateofrecruitmentpersonincharge as 负责人招募,"
                     "nameofpersonincharge as 负责人 from Task where nameofreleasedpreason = '"+user.Getname()+"'");
    model2->setQuery("select taskid as 编号,nameofreleasedpreason as 发布人,briefintroduction as 任务简介,"
                     "content as 任务内容,deadlineoftask as 任务截止日期,totalpay as 任务总金额,type as 任务类型,"
                     "stateofrecruitmenttranslator as 译者招募,nameoftranslator1 as 译者1,"
                     "nameoftranslator2 as 译者2 from Task where nameofpersonincharge = '"+user.Getname()+"'");
    model3->setQuery("select taskid as 编号,nameofpersonincharge as 负责人,briefintroduction as 任务简介,"
                     "deadlineoftask as 任务截止日期,dividedcontent as 任务内容,stateoftranslation as 翻译状态"
                     " from Subtask where nameoftranslator = '"+user.Getname()+"'");
    ui->tableView_MyReleasedTask->setModel(model1);
    ui->tableView_MyResponsibleTask->setModel(model2);
    ui->tableView_MyTranslationTask->setModel(model3);
}

//查看负责人报名状态键的槽函数，用于进入查看负责人报名状态的界面
void Platform::on_pushButton_ManageReleased_clicked()
{
    int InputTaskId = 0;
    DBMS dbms;
    QMessageBox msg_box;
    InputTaskId = this->ui->spinBox_released->value();
    if (dbms.IsMyReleasedTask(user.Getname(),InputTaskId)){
        if (!dbms.HasResponsiblePerson(InputTaskId)) {
            if (dbms.HasPersonWantToResponse(InputTaskId)){
                c_p_i_c = new Choose_Person_In_Charge(InputTaskId);
                c_p_i_c->show();
            }
            else {
                msg_box.setText("当前任务无负责人报名");
                msg_box.setWindowTitle("提示");
                msg_box.exec();
            }
        }
        else {
            msg_box.setText("当前任务负责人报名已结束");
            msg_box.setWindowTitle("提示");
            msg_box.exec();
        }
    }
    else {
        msg_box.setText("任务编号错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }

}

//查看译者报名状态键的槽函数，用于进入查看译者报名状态的界面
void Platform::on_pushButton_ManageResponsible_clicked()
{
    int InputTaskId = 0;
    DBMS dbms;
    QMessageBox msg_box;
    InputTaskId = this->ui->spinBox_responsible->value();
    if (dbms.IsMyResponsibleTask(user.Getname(),InputTaskId)){
        if (!dbms.HasTranslator(InputTaskId)){
            if (dbms.HasPersonWantToTranslate(InputTaskId)){
                c_t = new Choose_Translator(InputTaskId);
                c_t->show();
            }
            else {
                msg_box.setText("当前任务无译者报名");
                msg_box.setWindowTitle("提示");
                msg_box.exec();
            }
        }
        else {
            msg_box.setText("当前任务译者报名已结束");
            msg_box.setWindowTitle("提示");
            msg_box.exec();
        }
    }
    else {
        msg_box.setText("任务编号错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}

//获取原文键的槽函数，用于负责人获取原文
void Platform::on_pushButton_getcontent_clicked()
{
    int InputTaskId = 0;
    DBMS dbms;
    QMessageBox msg_box;
    InputTaskId = this->ui->spinBox_responsible->value();
    if (dbms.IsMyResponsibleTask(user.Getname(),InputTaskId)){
        msg_box.setText(dbms.GetTask(InputTaskId).GetContent());
        msg_box.setWindowTitle("任务原文");
        msg_box.exec();
    }
    else {
        msg_box.setText("任务编号错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}

//翻译键的槽函数，用于译者进入翻译界面
void Platform::on_pushButton_Translate_clicked()
{
    int InputTaskId = 0;
    DBMS dbms;
    QMessageBox msg_box;
    InputTaskId = this->ui->spinBox_translation->value();
    if (dbms.IsMySubtask(user.Getname(),InputTaskId)){
        Subtask subtask = dbms.GetSubtask(InputTaskId,user.Getname());
        translate = new Translate(subtask);
        translate->show();
    }
    else {
        msg_box.setText("任务编号错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}

//查看译文的槽函数，用于负责人查看译者暂存或提交的译文
void Platform::on_pushButton_viewresult_clicked()
{
    int InputTaskId = 0;
    DBMS dbms;
    QMessageBox msg_box;
    InputTaskId = this->ui->spinBox_responsible->value();
    if (dbms.IsMyResponsibleTask(user.Getname(),InputTaskId)){
        if (dbms.HasTranslator(InputTaskId)){
            QString name1 = dbms.GetTask(InputTaskId).GetTranslator1().Getname();
            QString name2 = dbms.GetTask(InputTaskId).GetTranslator2().Getname();
            if (name2 == nullptr){
                viewresult = new View_Result(dbms.GetSubtask(InputTaskId,name1));
                viewresult->show();
            }
            else {
                viewresult = new View_Result(dbms.GetSubtask(InputTaskId,name1),dbms.GetSubtask(InputTaskId,name2));
                viewresult->show();
            }
        }
        else {
            msg_box.setText("当前任务未指定译者");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
    }
    else {
        msg_box.setText("任务编号错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}

//查看最终译文的槽函数，用于任务发布者查看最终译文
void Platform::on_pushButton_viewfinalresult_clicked()
{
    int InputTaskId = 0;
    DBMS dbms;
    QMessageBox msg_box;
    InputTaskId = this->ui->spinBox_released->value();
    if (dbms.IsMyReleasedTask(user.Getname(),InputTaskId)){
        if (dbms.HasResponsiblePerson(InputTaskId)){
            Task task = dbms.GetTask(InputTaskId);
            if (task.GetFinalTranslationResult() != nullptr){
                v_f_r = new View_Final_Result(dbms.GetTask(InputTaskId));
                v_f_r->show();
            }
            else {
                msg_box.setText("负责人还未提交最终译文");
                msg_box.setWindowTitle("提示");
                msg_box.exec();
            }
        }
        else {
            msg_box.setText("当前任务未指定负责人");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
    }
    else {
        msg_box.setText("任务编号错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}
