#include "release_task.h"
#include "ui_release_task.h"
#include "dbms.h"
#include <QDate>

//构造函数
Release_Task::Release_Task(User user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Release_Task),
    user(user)
{
    ui->setupUi(this);
    TypeGroup = new QButtonGroup(this);
    TypeGroup->addButton(this->ui->radioButton_EnglishToChinese,1);
    TypeGroup->addButton(this->ui->radioButton_ChineseToEnglish,2);
    this->ui->radioButton_EnglishToChinese->setChecked(true);
}

//析构函数
Release_Task::~Release_Task()
{
    delete TypeGroup;
    delete ui;
}

//发布任务键的槽函数，用于发布任务
void Release_Task::on_pushButton_release_clicked()
{
    QString InputBriefInfo = this->ui->lineEdit_MissionProfile->text();
    QString InputContent = this->ui->plainTextEdit_TranslationContent->toPlainText();
    QString InputDeadlineOfTask = this->ui->dateEdit_ddloftask->text();
    QString InputDeadlineOfRecruitmentPersonInCharge = this->ui->dateEdit_ddlofresp->text();
    //将输入的日期赋成QDate类型
    QDate DeadlineOfTask = QDate::fromString(InputDeadlineOfTask,"yyyy/M/d");
    QDate DeadlineOfRecruitmentPersonInCharge = QDate::fromString(InputDeadlineOfRecruitmentPersonInCharge,"yyyy/M/d");
    int InputTotalPay = 0;
    QMessageBox msg_box;
    InputTotalPay = this->ui->spinBox_money->value();
    QString InputType = TypeGroup->checkedButton()->text();
    if (InputBriefInfo != nullptr && InputContent != nullptr && InputDeadlineOfTask != nullptr
        && InputDeadlineOfRecruitmentPersonInCharge != nullptr && InputTotalPay != 0
        && (InputType == "英译中" || InputType == "中译英")){
        //比较任务截止日期和负责人报名截止日期，若任务截止日期不在负责人报名截止日期之后，则报错
        if (DeadlineOfTask > DeadlineOfRecruitmentPersonInCharge){
            DBMS dbms;
            Task task(dbms.MaxUnusedTaskId(),user,InputBriefInfo,InputContent,InputDeadlineOfTask,
                      InputDeadlineOfRecruitmentPersonInCharge,InputTotalPay,InputType);
            dbms.NewTask(task);
            msg_box.setText("任务发布成功!");
            msg_box.setWindowTitle("成功");
            msg_box.exec();
            close();
        }
        else {
            msg_box.setText("日期设置错误!");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
    }
    else {
        msg_box.setText("请输入完整信息!");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}

//取消键的槽函数，用于退出当前界面
void Release_Task::on_pushButton_cancel_clicked()
{
    close();
}
