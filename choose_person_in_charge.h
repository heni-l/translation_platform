#ifndef CHOOSE_PERSON_IN_CHARGE_H
#define CHOOSE_PERSON_IN_CHARGE_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class Choose_Person_In_Charge;
}

/*********************************************************************************************
【类名】            Choose_Person_In_Charge
【功能】            用于发布者指定负责人
【接口说明】         接口用于指定负责人或退出当前界面
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Choose_Person_In_Charge : public QDialog
{
    Q_OBJECT

public:
    explicit Choose_Person_In_Charge(int id,QWidget *parent = nullptr);
    virtual ~Choose_Person_In_Charge();
    Choose_Person_In_Charge(const Choose_Person_In_Charge& c_p_i_c);
    Choose_Person_In_Charge operator=(const Choose_Person_In_Charge& c_p_i_c);

private slots:
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();
    //确认键的槽函数，用于指定负责人
    void on_pushButton_ok_clicked();

private:
    Ui::Choose_Person_In_Charge *ui;
    int taskid;
    QSqlQueryModel* model;
};

#endif // CHOOSE_PERSON_IN_CHARGE_H
