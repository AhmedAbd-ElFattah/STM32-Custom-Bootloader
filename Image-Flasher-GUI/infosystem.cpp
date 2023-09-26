#include "infosystem.h"


InfoSystem::InfoSystem()
{

}

void InfoSystem::SetLogUI(QPlainTextEdit *Arg_log)
{
    log = Arg_log;
}

void InfoSystem::AddLog(const QString& Arg_LogData)
{
    if (nullptr != log){
        log->appendPlainText(Arg_LogData);
    }
}


InfoSystem ImageFlash_InfoSystem;
