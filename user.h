#ifndef USER_H
#define USER_H

#include <QString>

/*********************************************************************************************
【类名】            User
【功能】            用于存放用户信息
【接口说明】         接口用于对用户信息进行操作
【开发者及日期】      何鉴芳 2019/8/1
【更改记录】         无
*********************************************************************************************/

class User
{
public :
    //积分和余额默认初始值为0
    User(QString name = nullptr,QString password = nullptr,QString phonenumber = nullptr,
         QString mailbox = nullptr,QString prove = nullptr,int points = 0,int balance = 0);
    User(const User& user);
    virtual ~User();
    User operator=(const User& user);
    /**********************************以下均为对User的Get操作****************************************/
    QString Getname();
    QString GetPassword();
    QString GetPhoneNumber();
    QString GetMailbox();
    QString GetProve();
    int GetPoints();
    int GetBalance();
    /**********************************以下均为对User的Set类操作***************************************/
    void NewName(QString newname);
    void NewPassword(QString newpassword);
    void NewPhonenumber(QString newphonenumber);
    void NewMailbox(QString newmailbox);
    void NewProve(QString newprove);
    void InitAccumulatePoints(int points);
    void PointsAddOne();
    void Recharge(int charge);
    void Pay(int pay);
    /**********************************以下函数用于判断用户的积分是否足够报名负责人*************************/
    bool CanBeResponsibleForTask();
private :
    QString m_qsName;//用户名
    QString m_qsPassword;//密码
    QString m_qsPhoneNumber;//手机号
    QString m_qsMailbox;//邮箱
    QString m_qsProve;//语言资质证明
    int m_iAccumulatePoints;//累积积分
    int m_iBalance;//账户余额
};

#endif // USER_H
