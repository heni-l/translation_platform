#include "dbms.h"
#include "qvariant.h"
#include <QDebug>

//构造函数和析构函数
DBMS::DBMS(){}
DBMS::~DBMS(){}

//NewUser用于新建用户
void DBMS::NewUser(User user)
{
    QSqlQuery query;
    query.exec(QString("insert into User values('%1','%2','%3','%4','%5','%6',0)")
               .arg(user.Getname()).arg(user.GetPassword()).arg(user.GetPhoneNumber())
               .arg(user.GetMailbox()).arg(user.GetProve()).arg(user.GetPoints()));
}

//UpdateUser用于更新用户信息
void DBMS::UpdateUser(QString oldname,User user)
{
    QSqlQuery query;
    query.exec(QString("update User set name = '%1',password = '%2',phonenumber = '%3',mailbox = '%4',"
                       "prove = '%5',accumulatepoints = '%6',balance = '%7' where name = '%8'").arg(user.Getname())
               .arg(user.GetPassword()).arg(user.GetPhoneNumber()).arg(user.GetMailbox()).arg(user.GetProve())
               .arg(user.GetPoints()).arg(user.GetBalance()).arg(oldname));
}

//GetUser用于读取用户信息，并返回User类型的用户
User DBMS::GetUser(QString name)
{
    if (name == nullptr){
        return User();
    }
    else {
        QSqlQuery query;
        query.exec("select * from User WHERE name = '"+name+"'");
        query.first();
        return  User(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),
                     query.value(3).toString(),query.value(4).toString(),query.value(5).toInt(),query.value(6).toInt());
    }
}

//UserMatchingSucceeded用于判断用户输入的用户名和密码是否正确，若正确，返回true，否则返回false
bool DBMS::UserMatchingSucceeded(QString inputname,QString inputpassword)
{
     QSqlQuery query;
     query.exec("select * from User");
     while (query.next()) {
         if (inputname == query.value(0).toString() && inputpassword == query.value(1).toString()){
             return true;
         }
     }
     return  false;
}

//UserSearchSucceeded用于判断是否已有用户使用该用户名，若有则返回true，否则返回false
bool DBMS::UserSearchSucceeded(QString inputname)
{
    QSqlQuery query;
    query.exec("select * from User");
    while (query.next()) {
        if (inputname == query.value(0).toString()){
            return true;
        }
    }
    return false;
}

//NewTask用于新建任务
void DBMS::NewTask(Task task)
{
    QSqlQuery query;
    query.exec(QString("insert into Task (taskid,nameofreleasedpreason,briefintroduction,content,deadlineoftask,"
                       "deadlineofrecruitmentpersonincharge,totalpay,type,stateofrecruitmentpersonincharge,stateofrecruitmenttranslator,"
                       "stateoftask) values('%1','%2','%3','%4','%5','%6','%7','%8','进行中','进行中','进行中')")
               .arg(MaxUnusedTaskId()).arg(task.GetReleasedPreason().Getname()).arg(task.GetBriefIntroduction())
               .arg(task.GetContent()).arg(task.GetDeadlineOfTask())
               .arg(task.GetDeadlineOfRecruitmentPersonInCharge()).arg(task.GetTotalPay()).arg(task.GetType()));
}

//UpdateTask用于更新任务信息
void DBMS::UpdateTask(Task task)
{
    QSqlQuery query;
    query.exec(QString("update Task set stateofrecruitmentpersonincharge = '%1',nameofpersonincharge = '%2',"
                       "stateofrecruitmenttranslator = '%3',nameoftranslator1 = '%4',nameoftranslator2 = '%5',"
                       "dividedcontent1 = '%6',dividedcontent2 = '%7',finaltranslationresult = '%8',stateoftask = '%9'"
                       " where taskid = '%10'")
               .arg(task.GetStateOfRecruitmentPersonInCharge()).arg(task.GetPersonInCharge().Getname())
               .arg(task.GetStateOfRecruitmentTranslator()).arg(task.GetTranslator1().Getname())
               .arg(task.GetTranslator2().Getname()).arg(task.GetDividedContent1()).arg(task.GetDividedContent2())
               .arg(task.GetFinalTranslationResult()).arg(task.GetStateOfTask()).arg(task.GetTaskId()));
}

//GetTask用于读取任务信息，并返回Task类型的任务
Task DBMS::GetTask(int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from Task where taskid = '%1'").arg(taskid));
    query.first();
    return Task(query.value(0).toInt(),GetUser(query.value(1).toString()),query.value(2).toString(),
                query.value(3).toString(),query.value(4).toString(),query.value(5).toString(),query.value(6).toInt(),
                query.value(7).toString(),GetUser(query.value(9).toString()),query.value(8).toString(),
                query.value(10).toString(),GetUser(query.value(11).toString()),GetUser(query.value(12).toString()),
                query.value(13).toString(),query.value(14).toString(),query.value(15).toString(),query.value(16).toString());
}

//MaxUnusedTaskId用于查找最大的未被使用的任务编号，在新建任务时使用
int DBMS::MaxUnusedTaskId()
{
    QSqlQuery query;
    query.exec("select * from Task");
    int count;
    count = 1;
    while (query.next()) {
        if (count != query.value(0).toInt()){
            return count;
        }
        else {
            count++;
        }
    }
    return count;
}

//TaskComplete用于判断任务编号对应的任务是否已完成，若已完成返回true，否则返回false
bool DBMS::TaskComplete(int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from Task where taskid = '%1'").arg(taskid));
    query.next();
    if (query.value(16).toString() == "进行中"){
        return false;
    }
    else {
        return true;
    }
}

//AddPersonInCharge用于为任务选定负责人，并将招募负责人的状态改为“已结束”
void DBMS::AddPersonInCharge(int taskid,QString name)
{
    QSqlQuery query;
    QString sql = "已结束";
    query.exec(QString("update Task set stateofrecruitmentpersonincharge = '%1',nameofpersonincharge = '%2'"
                       "where taskid = '%3'").arg(sql).arg(name).arg(taskid));
}

//TaskIdMMatch用于判断任务编号对应的任务是否存在，若存在返回true，否则返回false
bool DBMS::TaskIdMatch(int taskid)
{
    QSqlQuery query;
    query.exec("select * from Task");
    while (query.next()) {
        if (taskid == query.value(0).toInt()){
            return true;
        }
    }
    return false;
}

//NewSubtask用于新建子任务
void DBMS::NewSubtask(Subtask subtask)
{
    QSqlQuery query;
    query.exec(QString("insert into Subtask (taskid,nameoftranslator,nameofpersonincharge,briefintroduction,"
                       "deadlineoftask,dividedcontent,stateoftranslation,feedback)"
                       " values ('%1','%2','%3','%4','%5','%6','进行中','%7')")
               .arg(subtask.GetTaskId()).arg(subtask.GetTranslator().Getname())
               .arg(subtask.GetPersonInCharge().Getname()).arg(subtask.GetBriefIntroduction())
               .arg(subtask.GetDeadlineOfTask()).arg(subtask.GetDividedContent()).arg(subtask.GetFeedback()));
}

//GetSubtask用于读取子任务信息，并返回Subtask类型的子任务
Subtask DBMS::GetSubtask(int taskid,QString name)
{
    QSqlQuery query;
    query.exec(QString("select * from Subtask where taskid = '%1' and nameoftranslator = '%2'")
               .arg(taskid).arg(name));
    query.first();
    return Subtask(GetTask(taskid),GetUser(name),query.value(5).toString(),query.value(6).toString(),
                   query.value(7).toString(),query.value(8).toString());
}

//UpdateSubtask用于更新子任务信息
void DBMS::UpdateSubtask(Subtask subtask)
{
    QSqlQuery query;
    query.exec(QString("update Subtask set stateoftranslation = '%1',translationresult = '%2',feedback = '%3' "
                       "where taskid = '%4' and nameoftranslator = '%5'")
               .arg(subtask.GetStateOfTranslation()).arg(subtask.GetTranslationResult()).arg(subtask.GetFeedback())
               .arg(subtask.GetTaskId()).arg(subtask.GetTranslator().Getname()));
}

//IsMyReleasedTask用于判断任务是否是由该用户发布的，若是返回true，否则返回false
bool DBMS::IsMyReleasedTask(QString name, int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from Task where taskid = '%1'").arg(taskid));
    query.next();
    if (name == query.value(1).toString()){
        return true;
    }
    else {
        return false;
    }
}

//IsMyResponsibleTask用于判断任务是否是由该用户负责的，若是返回true，否则返回false
bool DBMS::IsMyResponsibleTask(QString name,int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from Task where taskid = '%1'").arg(taskid));
    query.next();
    if (name == query.value(9).toString()){
        return true;
    }
    else {
        return false;
    }
}

//IsMySubtask用于判断子任务是否是由该用户翻译的，若是返回true，否则返回false
bool DBMS::IsMySubtask(QString name, int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from Subtask where taskid = '%1'").arg(taskid));
    while(query.next()){
        if (name == query.value(1).toString()){
            return true;
        }
    }
    return false;
}

//HasResponsiblePerson用于判断任务是否有负责人，若有返回true，否则返回false
bool DBMS::HasResponsiblePerson(int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from Task where taskid = '%1'").arg(taskid));
    query.next();
    if (query.value(8).toString() == "进行中"){
        return false;
    }
    else {
        return true;
    }
}

//WantToResponse用于用户报名任务的负责工作
void DBMS::WantToResponse(int taskid,QString name)
{
    QSqlQuery query;
    query.exec(QString("insert into WantToResponse values('%1','%2')").arg(taskid).arg(name));
}

//DeleteWantToResponse用于删除任务负责人的报名信息
void DBMS::DeleteWantToResponse(int taskid)
{
    QSqlQuery query;
    query.exec(QString("delete from WantToResponse where taskid = '%1'").arg(taskid));
}

//HasPersonWantToResponse用于判断该任务是否有负责人报名，若有返回true，否则返回false
bool DBMS::HasPersonWantToResponse(int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from WantToResponse where taskid = '%1'").arg(taskid));
    if (query.next())
    {
        return true;
    }
    else {
        return false;
    }
}

//IHaveWantedToResponse用于判断用户是否已经报名该任务的负责工作，若已报名返回true，否则返回false
bool DBMS::IHaveWantedToResponse(QString name, int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from WantToResponse where taskid = '%1'").arg(taskid));
    while (query.next()){
        if (query.value(1).toString() == name){
            return true;
        }
    }
    return false;
}

//WantToTranslate用于用户报名任务的翻译工作
void DBMS::WantToTranslate(int taskid,QString name)
{
    QSqlQuery query;
    query.exec(QString("insert into WantToTranslate values('%1','%2')").arg(taskid).arg(name));
}

//DeleteWantToTranslate用于删除任务中译者的报名信息
void DBMS::DeleteWantToTranslate(int taskid)
{
    QSqlQuery query;
    query.exec(QString("delete from WantToTranslate where taskid = '%1'").arg(taskid));
}

//HasPersonWantToTranslate用于判断任务是否有译者报名，若有返回true，否则返回false
bool DBMS::HasPersonWantToTranslate(int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from WantToTranslate where taskid = '%1'").arg(taskid));
    if (query.next())
    {
        return true;
    }
    else {
        return false;
    }
}

//HasTranslator用于判断任务是否有译者，若有返回true，否则返回false
bool DBMS::HasTranslator(int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from Task where taskid = '%1'").arg(taskid));
    query.next();
    if (query.value(10).toString() == "进行中"){
        return false;
    }
    else {
        return true;
    }
}

//IHaveWantedToTranslate用于判断用户是否已经报名该任务的翻译工作，若已报名返回true，否则返回false
bool DBMS::IHaveWantedToTranslate(QString name,int taskid)
{
    QSqlQuery query;
    query.exec(QString("select * from WantToTranslate where taskid = '%1'").arg(taskid));
    while (query.next()){
        if (query.value(1).toString() == name){
            return true;
        }
    }
    return false;
}

//DivideContentToTranslator用于负责人给译者分配任务
void DBMS::DivideContentToTranslator(int taskid, QString name1, QString content1, QString name2, QString content2)
{
    QSqlQuery query;
    if (name2 != nullptr){
        query.exec(QString("update Task set stateofrecruitmenttranslator = '已结束',nameoftranslator1 = '%1',"
                           "nameoftranslator2 = '%2' where taskid = '%3'").arg(name1).arg(name2).arg(taskid));
        query.exec(QString("update Task set dividedcontent1 = '%1',dividedcontent2 = '%2' where taskid = '%3'")
                   .arg(content1).arg(content2).arg(taskid));
        NewSubtask(Subtask(GetTask(taskid),GetUser(name1),content1));
        NewSubtask(Subtask(GetTask(taskid),GetUser(name2),content2));
    }
    //若无译者2，则将全部的翻译任务交给译者1
    else {
        query.exec(QString("update Task set stateofrecruitmenttranslator = '已结束',nameoftranslator1 = '%1'"
                           " where taskid = '%2'").arg(name1).arg(taskid));
        query.exec(QString("update Task set dividedcontent1 = '%1' where taskid = '%2'")
                   .arg(GetTask(taskid).GetContent()).arg(taskid));
        NewSubtask(Subtask(GetTask(taskid),GetUser(name1),GetTask(taskid).GetContent()));
    }
}
