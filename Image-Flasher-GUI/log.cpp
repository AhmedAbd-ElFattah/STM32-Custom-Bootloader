#include "log.h"


Log::Log(QString Arg_Message_QString)
{
    Message = Arg_Message_QString;
}

QString Log::GetInfoMsg()
{
    QString txt = "[ " + QDateTime::currentDateTime().toString("d MMMM yyyy || h:m:s ap")+" ] ";
    txt +="[ Info ] --> ";
    txt += Message;
    txt += "\n";
    return txt;
}

QString Log::GetWarningMsg()
{
    QString txt = "[ " + QDateTime::currentDateTime().toString("d MMMM yyyy || h:m:s ap")+" ] ";
    txt +="[ Warning ] --> ";
    txt += Message;
    txt += "\n";
    return txt;
}

QString Log::GetErrorMsg()
{
    QString txt = "[ " + QDateTime::currentDateTime().toString("d MMMM yyyy || h:m:s ap")+" ] ";
    txt +="[ Error ] --> ";
    txt += Message;
    txt += "\n";
    return txt;
}
