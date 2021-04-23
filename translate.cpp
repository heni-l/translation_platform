#include "translate.h"
#include "ui_translate.h"
#include "dbms.h"

//构造函数
Translate::Translate(Subtask subtask,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Translate),
    subtask(subtask)
{
    ui->setupUi(this);
    ui->label_content->setText(subtask.GetDividedContent());
    ui->plainTextEdit_result->setPlainText(subtask.GetTranslationResult());
}

//析构函数
Translate::~Translate()
{
    delete ui;
}

//暂存键的槽函数，用于暂存当前译文
void Translate::on_pushButton_Temporarystorage_clicked()
{
    QString result = this->ui->plainTextEdit_result->toPlainText();
    DBMS dbms;
    QMessageBox msg_box;
    if (result == nullptr){
        msg_box.setText("译文不能为空");
        msg_box.setWindowTitle("提示");
        msg_box.exec();
    }
    else {
        //若任务已提交，则无法更改
        if (subtask.GetStateOfTranslation() == "进行中"){
            subtask.SetTranslationResult(result);
            dbms.UpdateSubtask(subtask);
            msg_box.setText("暂存成功");
            msg_box.setWindowTitle("成功");
            msg_box.exec();
        }
        else {
            msg_box.setText("译文已提交，无法更改");
            msg_box.setWindowTitle("提示");
            msg_box.exec();
        }
    }
}

//取消键的槽函数，用于退出当前界面
void Translate::on_pushButton_cancel_clicked()
{
    close();
}

//提交键的槽函数，用于提交译文
void Translate::on_pushButton_submit_clicked()
{
    QString result = this->ui->plainTextEdit_result->toPlainText();
    DBMS dbms;
    QMessageBox msg_box;
    if (result == nullptr){
        msg_box.setText("译文不能为空");
        msg_box.setWindowTitle("提示");
        msg_box.exec();
    }
    else {
        //若任务已提交，则无法更改
        if (subtask.GetStateOfTranslation() == "进行中"){
            subtask.SetTranslationResult(result);
            subtask.CompleteTranslation();
            dbms.UpdateSubtask(subtask);
            msg_box.setText("提交成功");
            msg_box.setWindowTitle("成功");
            msg_box.exec();
        }
        else {
            msg_box.setText("译文已提交，无法更改");
            msg_box.setWindowTitle("提示");
            msg_box.exec();
        }
    }
}

//查看反馈键的槽函数，用于查看负责人发来的反馈
void Translate::on_pushButton_viewfeedback_clicked()
{
    QMessageBox msg_box;
    msg_box.setText(subtask.GetFeedback());
    msg_box.setWindowTitle("反馈信息");
    msg_box.exec();
}
