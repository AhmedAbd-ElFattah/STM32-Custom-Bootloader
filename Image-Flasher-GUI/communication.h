#ifndef COMMUNICATION_H
#define COMMUNICATION_H
/*
 * File Name --> communication.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Communication with board.
 * */
#include <QObject>
#include <QThread>
#include <QSerialPort>
#include "common.h"
#include <QDebug>
#include <QPlainTextEdit>
#include "log.h"
#include "hexparser.h"
#include <QTextCursor>
#include <QThread>
#include <QSpinBox>
#include <QComboBox>

class Communication : public QThread
{
    Q_OBJECT
private:
    QSpinBox *IdSpinBox = nullptr;
    QComboBox *ComSelection = nullptr;
    HexParser *hexParser=nullptr;
    /*Used to send logs to GUI*/
    QPlainTextEdit *log=nullptr;
    /*To inform user with current task*/
    QLabel *CurrentTask_Label = nullptr;
    /*Progress Bar of current task.*/
    QProgressBar *CurrentTaskProgressBar = nullptr;
    QSerialPort ImageFlash_Serial_Port;
    BL_Exec_St SendCommand(quint32 Command, quint32 Flags, quint32 Param_1, quint32 Param_2, quint8 *Arg_Retval);

public:
    bool IsConnected(void);
    Communication();
    void Connect(QString Arg_PortName);
    void DisConnect();
    void SetLogUIObject(QPlainTextEdit *Arg_Log_QPlainTextEdit);
    void SetHexParser(HexParser *Arg_hexParser);
    void SetProgressBar(QProgressBar *Arg_TaskProgressBar);
    void SetCurrentTask(QLabel *Arg_CurrentTask_Label);
    void SetIdSpinBox(QSpinBox *Arg_IdSpinBox);
    void SetCommunicationSelectionCombobox(QComboBox *Arg_CommunicationSelectionCombobox);
    void run() override;
    ~Communication();
signals:


};

#endif // COMMUNICATION_H

