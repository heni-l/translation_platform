#include "subtask.h"

//构造函数
Subtask::Subtask(Task task,User translator,QString dividedcontent,QString stateoftranslation,
                 QString translationresult,QString feedback):
    Task(task)
{
    m_Translator = translator;
    m_qsDividedContent = dividedcontent;
    m_qsStateOfTranslation = stateoftranslation;
    m_qsTranslationResult = translationresult;
    m_qsFeedback = feedback;
}

//拷贝构造函数
Subtask::Subtask(const Subtask& subtask) : Task(subtask)
{
    m_Translator = subtask.m_Translator;
    m_qsDividedContent = subtask.m_qsDividedContent;
    m_qsStateOfTranslation = subtask.m_qsStateOfTranslation;
    m_qsTranslationResult = subtask.m_qsTranslationResult;
    m_qsFeedback = subtask.m_qsFeedback;
}

//析构函数
Subtask::~Subtask(){}

//赋值重载函数
Subtask Subtask::operator=(const Subtask& subtask)
{
    if (this == &subtask){
        return *this;
    }
    Task::operator=(subtask);
    m_Translator = subtask.m_Translator;
    m_qsDividedContent = subtask.m_qsDividedContent;
    m_qsStateOfTranslation = subtask.m_qsStateOfTranslation;
    m_qsTranslationResult = subtask.m_qsTranslationResult;
    m_qsFeedback = subtask.m_qsFeedback;
    return *this;
}

/**********************************以下均为对Subtask的Get操作*****************************************/
User Subtask::GetTranslator()
{
    return m_Translator;
}

QString Subtask::GetDividedContent()
{
    return m_qsDividedContent;
}

QString Subtask::GetStateOfTranslation()
{
    return m_qsStateOfTranslation;
}

QString Subtask::GetTranslationResult()
{
    return m_qsTranslationResult;
}

QString Subtask::GetFeedback()
{
    return m_qsFeedback;
}

/**********************************以下均为对Subtask的Set操作*****************************************/
void Subtask::SetFeedback(QString feedback)
{
    m_qsFeedback = feedback;
}

void Subtask::CompleteTranslation()
{
    m_qsStateOfTranslation = "已结束";
}

void Subtask::SetTranslationResult(QString translationresult)
{
    m_qsTranslationResult = translationresult;
}
