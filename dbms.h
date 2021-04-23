#ifndef DBMS_H
#define DBMS_H

#include "user.h"
#include "task.h"
#include "subtask.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

/*********************************************************************************************
【类名】            DBMS
【功能】            用于对数据库进行各种操作
【接口说明】         接口用于对数据库进行操作
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class DBMS
{
public:
    DBMS();
    DBMS(const DBMS& dbms);
    virtual ~DBMS();
    DBMS operator=(const DBMS& dbms);
    /**********************************以下均为对User的操作*****************************************/
    //NewUser用于新建用户
    void NewUser(User user);
    //UpdateUser用于更新用户信息
    void UpdateUser(QString oldname,User user);
    //GetUser用于读取用户信息
    User GetUser(QString name);
    //UserMatchingSucceeded用于判断用户输入的用户名和密码是否正确
    bool UserMatchingSucceeded(QString inputname,QString inputpassword);
    //UserSearchSucceeded用于判断是否已有用户使用该用户名
    bool UserSearchSucceeded(QString inputname);
    /**********************************以下均为对Task的操作*****************************************/
    //NewTask用于新建任务
    void NewTask(Task task);
    //UpdateTask用于更新任务信息
    void UpdateTask(Task task);
    //GetTask用于读取任务信息
    Task GetTask(int taskid);
    //MaxUnusedTaskId用于查找最大的未被使用的任务编号
    int MaxUnusedTaskId();
    //TaskIdMMatch用于判断任务编号对应的任务是否存在
    bool TaskIdMatch(int taskid);
    //TaskComplete用于判断任务编号对应的任务是否已完成
    bool TaskComplete(int taskid);
    /**********************************以下均为对Subtask的操作****************************************/
    //NewSubtask用于新建子任务
    void NewSubtask(Subtask subtask);
    //GetSubtask用于读取子任务信息
    Subtask GetSubtask(int taskid,QString name);
    //UpdateSubtask用于更新子任务信息
    void UpdateSubtask(Subtask subtask);
    /**********************************以下均为对User和Task的操作*************************************/
    //IsMyReleasedTask用于判断任务是否是由该用户发布的
    bool IsMyReleasedTask(QString name,int taskid);
    //IsMyResponsibleTask用于判断任务是否是由该用户负责的
    bool IsMyResponsibleTask(QString name,int taskid);
    //IsMySubtask用于判断子任务是否是由该用户翻译的
    bool IsMySubtask(QString name,int taskid);
    //HasResponsiblePerson用于判断任务是否有负责人
    bool HasResponsiblePerson(int taskid);
    //HasTranslator用于判断任务是否有译者
    bool HasTranslator(int taskid);
    //WantToResponse用于用户报名任务的负责工作
    void WantToResponse(int taskid,QString name);
    //IHaveWantedToResponse用于判断用户是否已经报名该任务的负责工作
    bool IHaveWantedToResponse(QString name,int taskid);
    //HasPersonWantToResponse用于判断该任务是否有负责人报名
    bool HasPersonWantToResponse(int taskid);
    //AddPersonInCharge用于为任务选定负责人
    void AddPersonInCharge(int taskid,QString name);
    //DeleteWantToResponse用于删除任务负责人的报名信息
    void DeleteWantToResponse(int taskid);
    //WantToTranslate用于用户报名任务的翻译工作
    void WantToTranslate(int taskid,QString name);
    //IHaveWantedToTranslate用于判断用户是否已经报名该任务的翻译工作
    bool IHaveWantedToTranslate(QString name,int taskid);
    //HasPersonWantToTranslate用于判断任务是否有译者报名
    bool HasPersonWantToTranslate(int taskid);
    //DivideContentToTranslator用于负责人给译者分配任务
    void DivideContentToTranslator(int taskid,QString name1,QString content1 = nullptr,
                                   QString name2 = nullptr,QString content2 = nullptr);
    //DeleteWantToTranslate用于删除任务中译者的报名信息
    void DeleteWantToTranslate(int taskid);
};

#endif // DBMS_H
