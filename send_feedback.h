#ifndef SEND_FEEDBACK_H
#define SEND_FEEDBACK_H

#include <QDialog>
#include "subtask.h"

namespace Ui {
class Send_Feedback;
}

/*********************************************************************************************
【类名】            Send_Feedback
【功能】            用于负责人给译者发送反馈
【接口说明】         接口用于发送反馈
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Send_Feedback : public QDialog
{
    Q_OBJECT

public:
    explicit Send_Feedback(Subtask subtask1,Subtask subtask2 = Subtask(),QWidget *parent = nullptr);
    virtual ~Send_Feedback();
    Send_Feedback(const Send_Feedback& s_f);
    Send_Feedback operator=(const Send_Feedback& s_f);

private slots:
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();
    //发送键的槽函数，用于发送反馈
    void on_pushButton_send_clicked();

private:
    Ui::Send_Feedback *ui;
    Subtask subtask1;
    Subtask subtask2;
};

#endif // SEND_FEEDBACK_H
