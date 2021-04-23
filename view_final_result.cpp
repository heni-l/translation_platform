#include "view_final_result.h"
#include "ui_view_final_result.h"
#include "dbms.h"

//构造函数
View_Final_Result::View_Final_Result(Task task,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::View_Final_Result),
    task(task)
{
    ui->setupUi(this);
    ui->label_content->setText(task.GetContent());
    ui->label_finalresult->setText(task.GetFinalTranslationResult());
}

//析构函数
View_Final_Result::~View_Final_Result()
{
    delete ui;
}

//确认键的槽函数，用于确认任务完成并支付酬金
void View_Final_Result::on_pushButton_ok_clicked()
{
    DBMS dbms;
    QMessageBox msg_box;
    User ReleasedPerson = task.GetReleasedPreason();
    //若任务已结束，则提示"当前任务已结束"
    if (task.TaskComplete()){
        msg_box.setText("当前任务已结束");
        msg_box.setWindowTitle("提示");
        msg_box.exec();
    }
    else {
        if (ReleasedPerson.GetBalance() >= task.GetTotalPay()){
            User PersonInCharge = task.GetPersonInCharge();
            User Translator1 = task.GetTranslator1();
            User Translator2 = task.GetTranslator2();
            ReleasedPerson.Pay(task.GetTotalPay());
            dbms.UpdateUser(ReleasedPerson.Getname(),ReleasedPerson);
            //若无译者2，则负责人和译者1各得任务金额的一半
            if (Translator2.Getname() == nullptr){
                Translator1.Recharge(task.GetTotalPay() / 2);
                Translator1.PointsAddOne();
                PersonInCharge.Recharge(task.GetTotalPay() - (task.GetTotalPay() / 2));
                dbms.UpdateUser(Translator1.Getname(),Translator1);
                dbms.UpdateUser(PersonInCharge.Getname(),PersonInCharge);
            }
            //若有译者2，则负责人，译者1和译者2各得任务金额的1/3
            else {
                Translator1.Recharge(task.GetTotalPay() / 3);
                Translator1.PointsAddOne();
                dbms.UpdateUser(Translator1.Getname(),Translator1);
                Translator2.Recharge(task.GetTotalPay() / 3);
                Translator2.PointsAddOne();
                dbms.UpdateUser(Translator2.Getname(),Translator2);
                PersonInCharge.Recharge(task.GetTotalPay() - (task.GetTotalPay() / 3) - (task.GetTotalPay() / 3));
                dbms.UpdateUser(PersonInCharge.Getname(),PersonInCharge);
            }
            task.CompleteTask();
            dbms.UpdateTask(task);
            msg_box.setText(QString("成功结束任务，已支付酬金%1元").arg(task.GetTotalPay()));
            msg_box.setWindowTitle("提示");
            msg_box.exec();
        }
        else {
            msg_box.setText("余额不足!");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
    }
}

//取消键的槽函数，用于退出当前界面
void View_Final_Result::on_pushButton_cancel_clicked()
{
    close();
}
