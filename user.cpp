#include "User.h"

//构造函数
User::User(QString name,QString password,QString phonenumber,
           QString mailbox,QString prove,int points,int balance)
{
    m_qsName = name;
    m_qsPassword = password;
    m_qsPhoneNumber = phonenumber;
    m_qsMailbox = mailbox;
    m_qsProve = prove;
    m_iAccumulatePoints = points;
    m_iBalance = balance;
}

//拷贝构造函数
User::User(const User& user)
{
    m_qsName = user.m_qsName;
    m_qsPassword = user.m_qsPassword;
    m_qsPhoneNumber = user.m_qsPhoneNumber;
    m_qsMailbox = user.m_qsMailbox;
    m_qsProve = user.m_qsProve;
    m_iAccumulatePoints = user.m_iAccumulatePoints;
    m_iBalance = user.m_iBalance;
}

//析构函数
User::~User(){}

//赋值重载函数
User User::operator=(const User& user)
{
    m_qsName = user.m_qsName;
    m_qsPassword = user.m_qsPassword;
    m_qsPhoneNumber = user.m_qsPhoneNumber;
    m_qsMailbox = user.m_qsMailbox;
    m_qsProve = user.m_qsProve;
    m_iAccumulatePoints = user.m_iAccumulatePoints;
    m_iBalance = user.m_iBalance;
    return *this;
}

/**********************************以下均为对User的Get操作****************************************/
QString User::Getname()
{
    return m_qsName;
}

QString User::GetPassword()
{
    return m_qsPassword;
}

QString User::GetPhoneNumber()
{
    return m_qsPhoneNumber;
}

QString User::GetMailbox()
{
    return m_qsMailbox;
}

QString User::GetProve()
{
    return m_qsProve;
}

int User::GetPoints()
{
    return m_iAccumulatePoints;
}

int User::GetBalance()
{
    return m_iBalance;
}

/**********************************以下均为对User的Set类操作***************************************/
void User::NewName(QString newname)
{
    m_qsName = newname;
}

void User::NewPassword(QString newpassword)
{
    m_qsPassword = newpassword;
}

void User::NewPhonenumber(QString newphonenumber)
{
    m_qsPhoneNumber = newphonenumber;
}

void User::NewMailbox(QString newmailbox)
{
    m_qsMailbox = newmailbox;
}

void User::NewProve(QString newprove)
{
    m_qsProve = newprove;
}

void User::InitAccumulatePoints(int points)
{
    m_iAccumulatePoints = points;
}

void User::PointsAddOne()
{
    m_iAccumulatePoints+=1;
}

void User::Recharge(int charge)
{
    m_iBalance+=charge;
}

void User::Pay(int pay)
{
    m_iBalance-=pay;
}

/**********************************以下函数用于判断用户的积分是否足够报名负责人*************************/
//若累积积分大于等于30，则用户可以报名负责人，返回true，否则返回false
bool User::CanBeResponsibleForTask()
{
    if (m_iAccumulatePoints >= 30){
        return true;
    }
    else {
        return false;
    }
}
