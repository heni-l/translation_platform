#include "choose_translator.h"
#include "ui_choose_translator.h"
#include "dbms.h"

//构造函数
Choose_Translator::Choose_Translator(int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choose_Translator)
{
    ui->setupUi(this);
    DBMS dbms;
    taskid = id;
    ui->label_content->setText(dbms.GetTask(id).GetContent());
    model=new QSqlQueryModel;
    model->setQuery(QString("select name as 已报名的译者 from WantToTranslate where taskid = '%1'").arg(taskid));
    ui->tableView->setModel(model);
}

//析构函数
Choose_Translator::~Choose_Translator()
{
    delete model;
    delete ui;
}

//取消键的槽函数，用于退出当前界面
void Choose_Translator::on_pushButton_cancel_clicked()
{
    close();
}

//确认键的槽函数，用于指定译者
void Choose_Translator::on_pushButton_ok_clicked()
{
    //读取输入的译者用户名和任务内容
    QString InputName1 = this->ui->lineEdit_name1->text();
    QString InputName2 = this->ui->lineEdit_name2->text();
    QString InputContent1 = this->ui->lineEdit_content1->text();
    QString InputContent2 = this->ui->lineEdit_content2->text();
    QMessageBox msg_box;
    DBMS dbms;
    //获取当前任务的负责人用户名
    QString nameofpersonincharge = dbms.GetTask(taskid).GetPersonInCharge().Getname();
    //若输入的用户名中有负责人的用户名，则报错
    if (nameofpersonincharge == InputName1 || nameofpersonincharge == InputName1){
        msg_box.setText("任务负责人不能参与翻译任务");
        msg_box.setWindowTitle("提示");
        msg_box.exec();
    }
    else {
        //若未输入用户名，则提示输入用户名
        if (InputName1 == nullptr && InputName2 == nullptr){
            msg_box.setText("请输入用户名");
            msg_box.setWindowTitle("错误");
            msg_box.exec();
        }
        else {
            //若输入了译者2的用户名而没有输入译者1的用户名，则提示"请优先选择译者1"
            if (InputName1 == nullptr){
                msg_box.setText("请优先选择译者1");
                msg_box.setWindowTitle("提示");
                msg_box.exec();
            }
            else {
                //若未指定译者2，则将全部原文交给译者1
                if (InputName2 == nullptr && InputContent1 == nullptr && InputContent2 == nullptr){
                    if (dbms.IHaveWantedToTranslate(InputName1,taskid)){
                        dbms.DivideContentToTranslator(taskid,InputName1);
                        msg_box.setText("指定译者成功");
                        msg_box.setWindowTitle("成功");
                        msg_box.exec();
                        dbms.DeleteWantToTranslate(taskid);
                        close();
                    }
                    else {
                        msg_box.setText("用户名错误");
                        msg_box.setWindowTitle("错误");
                        msg_box.exec();
                    }
                }
                else {
                    //若指定了译者2，则判断任务是否分配正确，若正确，则分配成功，否则提示"请输入正确原文"
                    if (InputName2 != nullptr && InputContent1 != nullptr && InputContent2 != nullptr){
                        if (dbms.IHaveWantedToTranslate(InputName1,taskid) && dbms.IHaveWantedToTranslate(InputName2,taskid)){
                            if (dbms.GetTask(taskid).GetContent() == InputContent1 + InputContent2){
                                dbms.DivideContentToTranslator(taskid,InputName1,InputContent1,InputName2,InputContent2);
                                msg_box.setText("指定译者成功");
                                msg_box.setWindowTitle("成功");
                                msg_box.exec();
                                dbms.DeleteWantToTranslate(taskid);
                                close();
                            }
                            else {
                                msg_box.setText("请输入正确原文");
                                msg_box.setWindowTitle("错误");
                                msg_box.exec();
                            }
                        }
                        else {
                            msg_box.setText("用户名错误");
                            msg_box.setWindowTitle("错误");
                            msg_box.exec();
                        }
                    }
                    else {
                        msg_box.setText("请输入完整信息");
                        msg_box.setWindowTitle("错误");
                        msg_box.exec();
                    }
                }
            }
        }
    }
}
