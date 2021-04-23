#ifndef CHOOSE_TRANSLATOR_H
#define CHOOSE_TRANSLATOR_H

#include <QDialog>
#include <QSqlQueryModel>

/*********************************************************************************************
【类名】            Choose_Translator
【功能】            用于负责人指定译者
【接口说明】         接口用于指定译者或退出当前界面
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

namespace Ui {
class Choose_Translator;
}

class Choose_Translator : public QDialog
{
    Q_OBJECT

public:
    explicit Choose_Translator(int id,QWidget *parent = nullptr);
    virtual ~Choose_Translator();
    Choose_Translator(const Choose_Translator& c_t);
    Choose_Translator operator=(const Choose_Translator& c_t);

private slots:
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();
    //确认键的槽函数，用于指定译者
    void on_pushButton_ok_clicked();

private:
    Ui::Choose_Translator *ui;
    int taskid;
    QSqlQueryModel* model;
};

#endif // CHOOSE_TRANSLATOR_H
