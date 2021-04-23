#ifndef VIEW_RESULT_H
#define VIEW_RESULT_H

#include <QDialog>
#include "subtask.h"
#include "send_feedback.h"

namespace Ui {
class View_Result;
}

/*********************************************************************************************
【类名】            View_Result
【功能】            用于负责人查看译者暂存或提交的译文
【接口说明】         接口用于合并译文并提交或向译者发送反馈信息
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class View_Result : public QDialog
{
    Q_OBJECT

public:
    explicit View_Result(Subtask subtask1,Subtask subtask2 = Subtask(),QWidget *parent = nullptr);
    virtual ~View_Result();
    View_Result(const View_Result& v_r);
    View_Result operator=(const View_Result& v_r);

private slots:
    //提交键的槽函数，用于负责人向发布者提交最终译文
    void on_pushButton_submit_clicked();
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();
    //发送反馈键的槽函数，用于进入发送反馈的界面
    void on_pushButton_sendfeedback_clicked();

private:
    Ui::View_Result *ui;
    Send_Feedback* sendfeedback;
    Subtask subtask1;
    Subtask subtask2;
};

#endif // VIEW_RESULT_H
