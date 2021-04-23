#ifndef VIEW_FINAL_RESULT_H
#define VIEW_FINAL_RESULT_H

#include <QDialog>
#include <task.h>

namespace Ui {
class View_Final_Result;
}

/*********************************************************************************************
【类名】            View_Final_Result
【功能】            用于发布者查看最终译文
【接口说明】         接口用于确认任务完成
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class View_Final_Result : public QDialog
{
    Q_OBJECT

public:
    explicit View_Final_Result(Task task,QWidget *parent = nullptr);
    virtual ~View_Final_Result();
    View_Final_Result(const View_Final_Result& v_f_r);
    View_Final_Result operator=(const View_Final_Result& v_f_r);

private slots:
    //确认键的槽函数，用于确认任务完成并支付酬金
    void on_pushButton_ok_clicked();
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();

private:
    Ui::View_Final_Result *ui;
    Task task;
};

#endif // VIEW_FINAL_RESULT_H
