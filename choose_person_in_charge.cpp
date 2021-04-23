#include "choose_person_in_charge.h"
#include "ui_choose_person_in_charge.h"
#include "dbms.h"

//构造函数
Choose_Person_In_Charge::Choose_Person_In_Charge(int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choose_Person_In_Charge)
{
    ui->setupUi(this);
    taskid = id;
    model=new QSqlQueryModel;
    model->setQuery(QString("select name as 已报名的负责人 from WantToResponse where taskid = '%1'").arg(taskid));
    ui->tableView->setModel(model);
}

//析构函数
Choose_Person_In_Charge::~Choose_Person_In_Charge()
{
    delete model;
    delete ui;
}

//取消键槽函数，点击时关闭界面
void Choose_Person_In_Charge::on_pushButton_cancel_clicked()
{
    close();
}

//确认键的槽函数，用于指定负责人
void Choose_Person_In_Charge::on_pushButton_ok_clicked()
{
    QString InputName = this->ui->lineEdit_name->text();
    QMessageBox msg_box;
    DBMS dbms;
    //若输入的用户报名了负责该任务，则指定该用户为负责人，否则报错
    if (dbms.IHaveWantedToResponse(InputName,taskid)){
        dbms.AddPersonInCharge(taskid,InputName);
        msg_box.setText("指定负责人成功");
        msg_box.setWindowTitle("成功");
        msg_box.exec();
        dbms.DeleteWantToResponse(taskid);
        close();
    }
    else {
        msg_box.setText("用户名错误");
        msg_box.setWindowTitle("错误");
        msg_box.exec();
    }
}
