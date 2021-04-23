#ifndef SUBTASK_H
#define SUBTASK_H

#include "task.h"

/*********************************************************************************************
【类名】            Subtask
【功能】            继承自Task类，用于存放子任务信息
【接口说明】         接口用于对子任务信息进行操作
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Subtask : public Task
{
public:
    Subtask(Task task = Task(),User translator = User(),QString dividedcontent = nullptr,
            QString stateoftranslation = "进行中",QString translationresult = nullptr,
            QString feedback = "当前无反馈信息");
    Subtask(const Subtask& subtask);
    virtual ~Subtask();
    Subtask operator=(const Subtask& subtask);
    /**********************************以下均为对Subtask的Get操作*****************************************/
    User GetTranslator();
    QString GetDividedContent();
    QString GetStateOfTranslation();
    QString GetTranslationResult();
    QString GetFeedback();
    /**********************************以下均为对Subtask的Set操作*****************************************/
    void CompleteTranslation();
    void SetFeedback(QString feedback);
    void SetTranslationResult(QString translationresult);
private:
    User m_Translator;//子任务的翻译者
    QString m_qsDividedContent;//子任务的内容
    QString m_qsStateOfTranslation;//翻译的状态，“进行中”或“已结束”
    QString m_qsTranslationResult;//翻译结果
    QString m_qsFeedback;//负责人的反馈信息
};

#endif // SUBTASK_H
