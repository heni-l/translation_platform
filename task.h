#ifndef TASK_H
#define TASK_H

#include <QString>
#include "user.h"

/*********************************************************************************************
【类名】            Task
【功能】            用于存放任务信息
【接口说明】         接口用于对任务信息进行操作
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class Task
{
public :
    Task(int taskid = 0,User releasedpreason = User(),QString briefintro = nullptr,QString content = nullptr,
         QString ddloftask = nullptr,QString ddlofrecruitment = nullptr,int totalpay = 0,QString type = nullptr,
         User personincharge = User(),QString stateofrecruitmentpersonincharge = "进行中",
         QString stateofrecruitmenttranslator = "进行中",User translator1 = User(),User translator2 = User(),
         QString dividedcontent1 = nullptr,QString dividedcontent2 = nullptr,
         QString finaltranslationresult = nullptr,QString stateOftask = "进行中");
    Task(const Task& task);
    virtual ~Task();
    Task& operator=(const Task& task);
    int GetTaskId();
    /**********************************以下均为对Task的Get操作****************************************/
    User GetReleasedPreason();
    QString GetBriefIntroduction();
    QString GetContent();
    QString GetDeadlineOfTask();
    QString GetDeadlineOfRecruitmentPersonInCharge();
    int GetTotalPay();
    QString GetType();
    QString GetStateOfRecruitmentPersonInCharge();
    User GetPersonInCharge();
    QString GetStateOfRecruitmentTranslator();
    User GetTranslator1();
    User GetTranslator2();
    QString GetDividedContent1();
    QString GetDividedContent2();
    QString GetFinalTranslationResult();
    QString GetStateOfTask();
    /**********************************以下均为对Task的Set操作*****************************************/
    void SetFinalTranslationResult(QString FinalTranslationResult);
    void CompleteTask();
    /**********************************以下函数用于判断任务是否完成**************************************/
    bool TaskComplete();
private :
    int m_iTaskId;//记录任务的个数，同时为任务的标识
    User m_ReleasedPreason;//任务的发布者
    QString m_qsBriefIntroduction;//任务的简介
    QString m_qsContent;//任务的内容
    QString m_qsDeadlineOfTask;//任务的截止时间
    QString m_qsDeadlineOfRecruitmentPersonInCharge;//招聘负责人的截止时间
    int m_iTotalPay;//任务的总金额
    QString m_qsType;//任务的类型，“英译中”或“中译英”
    User m_PersonInCharge;//任务的负责人
    QString m_qsStateOfRecruitmentPersonInCharge;//招聘负责人的状态，“进行中”或“已结束”
    QString m_qsStateOfRecruitmentTranslator;//招聘译者的状态，“进行中”或“已结束”
    User m_Translator1;//译者1
    User m_Translator2;//译者2
    //将任务内容分为2份
    QString m_qsDividedContent1;
    QString m_qsDividedContent2;
    //最终的翻译结果
    QString m_qsFinalTranslationResult;
    //任务的状态，“进行中”或“已结束”
    QString m_qsStateOfTask;
};

#endif // RELEASED_TASK_H
