/*
 * File Name --> infosystem.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Responsible for system information.
 * */


#ifndef INFOSYSTEM_H
#define INFOSYSTEM_H

#include <QPlainTextEdit>
#include <QString>


class InfoSystem
{
private:
    QPlainTextEdit *log=nullptr;

public:
    InfoSystem();

    void SetLogUI(QPlainTextEdit *Arg_log);
    void AddLog(const QString& Arg_LogData);


};
extern InfoSystem ImageFlash_InfoSystem;

#endif // INFOSYSTEM_H
