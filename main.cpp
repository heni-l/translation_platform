#include "login.h"
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

bool opendatabase();
int main(int argc, char *argv[])
{
    opendatabase();
    QApplication a(argc, argv);
    Login w;
    w.show();

    return a.exec();
}

bool opendatabase()
{
    //创建数据库
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else{
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        //mydb.setDatabaseName("my_db.db");
        mydb.setDatabaseName("C:\\Qt\\my_db.db");
    }

    if(mydb.open())
    {
        qDebug()<<"open success";
        /*
        QSqlQuery query;
        //创建User表，用于储存用户信息
        query.exec("create table User(name QString primary key, password QString, phonenumber QString,"
                   "mailbox QString, prove QString, accumulatepoints int, balance int)");
        //创建Task表，用于存储任务信息
        query.exec("create table Task(taskid int primary key,nameofreleasedpreason QString,"
                   "briefintroduction QString,content QString,deadlineoftask QString,"
                   "deadlineofrecruitmentpersonincharge QString,totalpay int,type QString,"
                   "stateofrecruitmentpersonincharge QString,nameofpersonincharge QString,"
                   "stateofrecruitmenttranslator QString,nameoftranslator1 QString,nameoftranslator2 QString,"
                   "dividedcontent1 QString,dividedcontent2 QString,finaltranslationresult QString,"
                   "stateoftask QString)");
        //创建Subtask表，用于存储子任务信息
        query.exec("create table Subtask(taskid int,nameoftranslator QString,nameofpersonincharge QString,"
                   "briefintroduction QString,deadlineoftask QString,dividedcontent QString,"
                   "stateoftranslation QString,translationresult QString,feedback QString)");
        //创建WantToResponse表，用于存储用户报名负责人的信息
        query.exec("create table WantToResponse(taskid int,name QString)");
        //创建WantToTranslate表，用于储存用户报名译者的信息
        query.exec("create table WantToTranslate(taskid int,name QString)");
        */
        return true;
    }
    else
    {
        qDebug()<<"open failed";
        return false;
    }
}
