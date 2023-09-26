#ifndef LOG_H
#define LOG_H

/*
 * File Name --> log.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Get log messages in suitable format.
 * */

#include <QString>
#include <QDateTime>

class Log
{
private:
    QString Message;
public:
    Log(QString Arg_Message_QString);

    QString GetInfoMsg();
    QString GetWarningMsg();
    QString GetErrorMsg();
};

#endif // LOG_H
