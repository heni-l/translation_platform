#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QDialog>
#include <subtask.h>

namespace Ui {
class Translate;
}

/*********************************************************************************************
【类名】            Translate
【功能】            用于译者进行翻译
【接口说明】         接口用于进行翻译
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Translate : public QDialog
{
    Q_OBJECT

public:
    explicit Translate(Subtask subtask,QWidget *parent = nullptr);
    virtual ~Translate();
    Translate(const Translate& translate);
    Translate operator=(const Translate& translate);

private slots:
    //暂存键的槽函数，用于暂存当前译文
    void on_pushButton_Temporarystorage_clicked();
    //取消键的槽函数，用于退出当前界面
    void on_pushButton_cancel_clicked();
    //提交键的槽函数，用于提交译文
    void on_pushButton_submit_clicked();
    //查看反馈键的槽函数，用于查看负责人发来的反馈
    void on_pushButton_viewfeedback_clicked();

private:
    Ui::Translate *ui;
    Subtask subtask;
};

#endif // TRANSLATE_H
