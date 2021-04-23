#include "task.h"
#include "dbms.h"

//构造函数
Task::Task(int taskid,User releasedpreason,QString briefintro,QString content,QString ddloftask,
           QString ddlofrecruitment,int totalpay,QString type,User personincharge,
           QString stateofrecruitmentpersonincharge,QString stateofrecruitmenttranslator,
           User translator1,User translator2,QString dividedcontent1,
           QString dividedcontent2, QString finaltranslationresult,QString stateoftask) :
    m_ReleasedPreason(releasedpreason),
    m_PersonInCharge(personincharge),
    m_Translator1(translator1),
    m_Translator2(translator2)
{
    m_iTaskId = taskid;
    m_qsBriefIntroduction = briefintro;
    m_qsContent = content;
    m_qsDeadlineOfTask = ddloftask;
    m_qsDeadlineOfRecruitmentPersonInCharge = ddlofrecruitment;
    m_iTotalPay = totalpay;
    m_qsType = type;
    m_qsStateOfRecruitmentPersonInCharge = stateofrecruitmentpersonincharge;
    m_qsStateOfRecruitmentTranslator = stateofrecruitmenttranslator;
    m_qsDividedContent1 = dividedcontent1;
    m_qsDividedContent2 = dividedcontent2;
    m_qsFinalTranslationResult = finaltranslationresult;
    m_qsStateOfTask = stateoftask;
}

//拷贝构造函数
Task::Task(const Task& task)
{
    m_iTaskId = task.m_iTaskId;
    m_ReleasedPreason = task.m_ReleasedPreason;
    m_qsBriefIntroduction = task.m_qsBriefIntroduction;
    m_qsContent = task.m_qsContent;
    m_qsDeadlineOfTask = task.m_qsDeadlineOfTask;
    m_qsDeadlineOfRecruitmentPersonInCharge = task.m_qsDeadlineOfRecruitmentPersonInCharge;
    m_iTotalPay = task.m_iTotalPay;
    m_qsType = task.m_qsType;
    m_qsStateOfRecruitmentPersonInCharge = task.m_qsStateOfRecruitmentPersonInCharge;
    m_PersonInCharge = task.m_PersonInCharge;
    m_qsStateOfRecruitmentTranslator = task.m_qsStateOfRecruitmentTranslator;
    m_Translator1 = task.m_Translator1;
    m_Translator2 = task.m_Translator2;
    m_qsDividedContent1 = task.m_qsDividedContent1;
    m_qsDividedContent2 = task.m_qsDividedContent2;
    m_qsFinalTranslationResult = task.m_qsFinalTranslationResult;
    m_qsStateOfTask = task.m_qsStateOfTask;
}

//析构函数
Task::~Task(){}

//赋值重载函数
Task& Task::operator=(const Task& task)
{
    m_iTaskId = task.m_iTaskId;
    m_ReleasedPreason = task.m_ReleasedPreason;
    m_qsBriefIntroduction = task.m_qsBriefIntroduction;
    m_qsContent = task.m_qsContent;
    m_qsDeadlineOfTask = task.m_qsDeadlineOfTask;
    m_qsDeadlineOfRecruitmentPersonInCharge = task.m_qsDeadlineOfRecruitmentPersonInCharge;
    m_iTotalPay = task.m_iTotalPay;
    m_qsType = task.m_qsType;
    m_qsStateOfRecruitmentPersonInCharge = task.m_qsStateOfRecruitmentPersonInCharge;
    m_PersonInCharge = task.m_PersonInCharge;
    m_qsStateOfRecruitmentTranslator = task.m_qsStateOfRecruitmentTranslator;
    m_Translator1 = task.m_Translator1;
    m_Translator2 = task.m_Translator2;
    m_qsDividedContent1 = task.m_qsDividedContent1;
    m_qsDividedContent2 = task.m_qsDividedContent2;
    m_qsFinalTranslationResult = task.m_qsFinalTranslationResult;
    m_qsStateOfTask = task.m_qsStateOfTask;
    return *this;
}

/**********************************以下均为对Task的Get操作****************************************/
int Task::GetTaskId()
{
    return m_iTaskId;
}

User Task::GetReleasedPreason()
{
    return m_ReleasedPreason;
}

QString Task::GetBriefIntroduction()
{
    return m_qsBriefIntroduction;
}

QString Task::GetContent()
{
    return m_qsContent;
}

QString Task::GetDeadlineOfTask()
{
    return m_qsDeadlineOfTask;
}

QString Task::GetDeadlineOfRecruitmentPersonInCharge()
{
    return m_qsDeadlineOfRecruitmentPersonInCharge;
}

int Task::GetTotalPay()
{
    return m_iTotalPay;
}

QString Task::GetType()
{
    return m_qsType;
}

QString Task::GetStateOfRecruitmentPersonInCharge()
{
    return m_qsStateOfRecruitmentPersonInCharge;
}

User Task::GetPersonInCharge()
{
    return m_PersonInCharge;
}

QString Task::GetStateOfRecruitmentTranslator()
{
    return m_qsStateOfRecruitmentTranslator;
}

QString Task::GetDividedContent1()
{
    return m_qsDividedContent1;
}

QString Task::GetDividedContent2()
{
    return m_qsDividedContent2;
}

User Task::GetTranslator1()
{
    return m_Translator1;
}

User Task::GetTranslator2()
{
    return m_Translator2;
}

QString Task::GetFinalTranslationResult()
{
    return m_qsFinalTranslationResult;
}

QString Task::GetStateOfTask()
{
    return m_qsStateOfTask;
}

/**********************************以下均为对Task的Set操作*****************************************/
void Task::SetFinalTranslationResult(QString finaltranslationresult)
{
    m_qsFinalTranslationResult = finaltranslationresult;
}

void Task::CompleteTask()
{
    m_qsStateOfTask = "已结束";
}

/**********************************以下函数用于判断任务是否完成**************************************/
bool Task::TaskComplete()
{
    if (m_qsStateOfTask == "进行中"){
        return false;
    }
    else {
        return true;
    }
}
