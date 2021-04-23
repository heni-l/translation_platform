#include "send_feedback.h"
#include "ui_send_feedback.h"
#include "dbms.h"

//构造函数
Send_Feedback::Send_Feedback(Subtask subtask1,Subtask subtask2,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Send_Feedback),
    subtask1(subtask1),
    subtask2(subtask2)
{
    ui->setupUi(this);
    ui->name1->setText(subtask1.GetTranslator().Getname());
    if (subtask2.GetTranslator().Getname() != nullptr){
        ui->name2->setText(subtask2.GetTranslator().Getname());
    }
}

//析构函数
Send_Feedback::~Send_Feedback()
{
    delete ui;
}

//取消键的槽函数，用于退出当前界面
void Send_Feedback::on_pushButton_cancel_clicked()
{
    close();
}

//发送键的槽函数，用于发送反馈
void Send_Feedback::on_pushButton_send_clicked()
{
    DBMS dbms;
    QMessageBox msg_box;
    if (subtask2.GetTranslator().Getname() != nullptr){
        QString feedback1 = this->ui->plainTextEdit_feedback1->toPlainText();
        QString feedback2 = this->ui->plainTextEdit_feedback2->toPlainText();
        if (feedback1 == nullptr && feedback2 == nullptr){
            msg_box.setText("请输入反馈信息");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
        else {
            if (feedback1 != nullptr){
                subtask1.SetFeedback(feedback1);
                dbms.UpdateSubtask(subtask1);
            }
            if (feedback2 != nullptr){
                subtask2.SetFeedback(feedback2);
                dbms.UpdateSubtask(subtask2);
            }
            msg_box.setText("反馈信息发送成功");
            msg_box.setWindowTitle("成功");
            msg_box.exec();
        }
    }
    else {
        QString feedback1 = this->ui->plainTextEdit_feedback1->toPlainText();
        if (feedback1 == nullptr){
            msg_box.setText("请输入反馈信息");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
        else {
            subtask1.SetFeedback(feedback1);
            dbms.UpdateSubtask(subtask1);
            msg_box.setText("反馈信息发送成功");
            msg_box.setWindowTitle("成功");
            msg_box.exec();
        }
    }
}
