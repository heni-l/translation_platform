#include "view_result.h"
#include "ui_view_result.h"
#include "dbms.h"

//构造函数
View_Result::View_Result(Subtask subtask1,Subtask subtask2,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::View_Result),
    subtask1(subtask1),
    subtask2(subtask2)
{
    ui->setupUi(this);
    ui->label_name1->setText(subtask1.GetTranslator().Getname());
    ui->label_content1->setText(subtask1.GetDividedContent());
    ui->label_result1->setText(subtask1.GetTranslationResult());
    if (subtask2.GetTranslator().Getname() != nullptr){
        ui->label_name2->setText(subtask2.GetTranslator().Getname());
        ui->label_3->setText("原文：");
        ui->label_4->setText("译文：");
        ui->label_content2->setText(subtask2.GetDividedContent());
        ui->label_result2->setText(subtask2.GetTranslationResult());
    }
}

//析构函数
View_Result::~View_Result()
{
    delete sendfeedback;
    delete ui;
}

//提交键的槽函数，用于负责人向发布者提交最终译文
void View_Result::on_pushButton_submit_clicked()
{
    DBMS dbms;
    QMessageBox msg_box;
    Task task = dbms.GetTask(subtask1.GetTaskId());
    //若有译者2，则需要译者1和译者2都提交译文后，负责人才能提交最终译文
    if (subtask2.GetTranslator().Getname() != nullptr){
        if (subtask1.GetStateOfTranslation() != "进行中"  && subtask2.GetStateOfTranslation() != "进行中"){
            //若任务已有最终译文，则提示"当前任务已提交，等待发布者确认"
            if (task.GetFinalTranslationResult() == nullptr){
                QString FinalTranslationResult = subtask1.GetTranslationResult() + subtask2.GetTranslationResult();
                task.SetFinalTranslationResult(FinalTranslationResult);
                dbms.UpdateTask(task);
                msg_box.setText("任务提交成功，等待发布者确认");
                msg_box.setWindowTitle("成功");
                msg_box.exec();
            }
            else {
                msg_box.setText("当前任务已提交，等待发布者确认");
                msg_box.setWindowTitle("提示");
                msg_box.exec();
            }
        }
        else {
            msg_box.setText("有译者还未提交译文");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
    }
    //若无译者2，则译者1提交译文后，负责人能提交最终译文
    else {
        if (subtask1.GetStateOfTranslation() != "进行中"){
            //若任务已有最终译文，则提示"当前任务已提交，等待发布者确认"
            if (task.GetFinalTranslationResult() == nullptr){
                QString FinalTranslationResult = subtask1.GetTranslationResult();
                task.SetFinalTranslationResult(FinalTranslationResult);
                dbms.UpdateTask(task);
                msg_box.setText("任务提交成功，等待发布者确认");
                msg_box.setWindowTitle("成功");
                msg_box.exec();
            }
            else {
                msg_box.setText("当前任务已提交，等待发布者确认");
                msg_box.setWindowTitle("提示");
                msg_box.exec();
            }
        }
        else {
            msg_box.setText("译者还未提交译文");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
    }
}

//取消键的槽函数，用于退出当前界面
void View_Result::on_pushButton_cancel_clicked()
{
    close();
}

//发送反馈键的槽函数，用于进入发送反馈的界面
void View_Result::on_pushButton_sendfeedback_clicked()
{
    sendfeedback = new Send_Feedback(subtask1,subtask2);
    sendfeedback->show();
}
