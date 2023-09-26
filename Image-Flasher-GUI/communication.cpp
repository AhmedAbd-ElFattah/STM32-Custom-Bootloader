#include "communication.h"

Communication::Communication()
{
    ImageFlash_Serial_Port.setBaudRate(QSerialPort::BaudRate::Baud115200);
    ImageFlash_Serial_Port.setParity(QSerialPort::Parity::NoParity);
    ImageFlash_Serial_Port.setDataBits(QSerialPort::DataBits::Data8);
    ImageFlash_Serial_Port.setFlowControl(QSerialPort::FlowControl::NoFlowControl);
}

void Communication::Connect(QString Arg_PortName)
{
    QString ConnectionMessage;
    if (ImageFlash_Serial_Port.isOpen()){
        ImageFlash_Serial_Port.close();
    }
    ImageFlash_Serial_Port.setPortName(Arg_PortName);
    ImageFlash_Serial_Port.open(QIODevice::ReadWrite);

    if (IsConnected()){
        ConnectionMessage = Log("Connected successfully to "+Arg_PortName).GetInfoMsg();
    }
    else{
        DisConnect();
        ConnectionMessage = Log("Failed to Connect with "+Arg_PortName).GetInfoMsg();
    }
    if (nullptr != log){
        QMetaObject::invokeMethod(log,
                                  "appendPlainText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, ConnectionMessage));
    }

}

void Communication::DisConnect()
{
    if (ImageFlash_Serial_Port.isOpen()){
        ImageFlash_Serial_Port.close();
    }
}


void Communication::SetLogUIObject(QPlainTextEdit *Arg_Log_QPlainTextEdit)
{
    log = Arg_Log_QPlainTextEdit;
}

void Communication::SetHexParser(HexParser *Arg_hexParser)
{
    hexParser = Arg_hexParser;
}

void Communication::SetProgressBar(QProgressBar *Arg_TaskProgressBar)
{
    CurrentTaskProgressBar = Arg_TaskProgressBar;
}

void Communication::SetCurrentTask(QLabel *Arg_CurrentTask_Label)
{
    CurrentTask_Label = Arg_CurrentTask_Label;
}

void Communication::SetIdSpinBox(QSpinBox *Arg_IdSpinBox)
{
    IdSpinBox = Arg_IdSpinBox;
}

void Communication::SetCommunicationSelectionCombobox(QComboBox *Arg_CommunicationSelectionCombobox)
{
    ComSelection = Arg_CommunicationSelectionCombobox;
}

void Communication::run()
{
    quint32 DeviceID = 0;
    BootloaderCommunication CurrentCom = Communication_UART;
    if (nullptr != ComSelection){
        CurrentCom = (BootloaderCommunication)ComSelection->currentIndex();
    }
    if ((nullptr != IdSpinBox) && (IdSpinBox->isEnabled())){
        DeviceID = IdSpinBox->value();
        qDebug()<<"Current Device id is "<<DeviceID;
    }
    quint8 RetValue;
    BL_Exec_St Status;
    /*Reset progress bar*/
    if (nullptr != CurrentTaskProgressBar ){
        QMetaObject::invokeMethod(CurrentTaskProgressBar,
                                  "setValue",
                                  Qt::AutoConnection,
                                  Q_ARG(int, 0));
    }
    if (Communication_UART == CurrentCom){
        /*1. Connect to Application*/
        Status = SendCommand(HOST_CMD_ConnectToApp, DeviceID, 0, 0, &RetValue);

        if ((nullptr != log) && (Status == BL_CMD_EXEC_SUCCEED_STATUS)){
            QMetaObject::invokeMethod(log,
                                      "appendPlainText",
                                      Qt::AutoConnection,
                                      Q_ARG(QString, Log("Connected successfully to application.").GetInfoMsg()));
        }

        else if ((nullptr != log) && (Status == BL_CMD_EXEC_FAILED_STATUS)) {
            QMetaObject::invokeMethod(log,
                                      "appendPlainText",
                                      Qt::AutoConnection,
                                      Q_ARG(QString, Log("Failed to Connect to application.").GetInfoMsg()));
        }
        else if(Status == BL_CMD_EXEC_FAILED_STATUS){
            return ;
        }

        /*2. Set Flash flag in microcontroller.*/
        Status = SendCommand(HOST_CMD_SET_UPDATE_FLAG, DeviceID, 0, 0, &RetValue);

        if ((nullptr != log) && (Status == BL_CMD_EXEC_SUCCEED_STATUS)){
            QMetaObject::invokeMethod(log,
                                      "appendPlainText",
                                      Qt::AutoConnection,
                                      Q_ARG(QString, Log("Flash flag is successfully raised.").GetInfoMsg()));
        }
        else if ((nullptr != log) && (Status == BL_CMD_EXEC_FAILED_STATUS)) {
            QMetaObject::invokeMethod(log,
                                      "appendPlainText",
                                      Qt::AutoConnection,
                                      Q_ARG(QString, Log("Flash flag failed to be raised.").GetInfoMsg()));
        }
        else if(Status == BL_CMD_EXEC_FAILED_STATUS){
            return ;
        }

        QThread::msleep(1000);
        /*3. After microcontroller reset, Connect to bootloader.*/
        if (nullptr != CurrentTask_Label){
            QMetaObject::invokeMethod(CurrentTask_Label,
                                      "setText",
                                      Qt::AutoConnection,
                                      Q_ARG(QString, "Current Task : Connect To Bootloader"));
        }
        Status = SendCommand(HOST_CMD_ConnectToBL, DeviceID, 0, 0, &RetValue);

        if ((nullptr != log) && (Status == BL_CMD_EXEC_SUCCEED_STATUS)){
            QMetaObject::invokeMethod(log,
                                      "appendPlainText",
                                      Qt::AutoConnection,
                                      Q_ARG(QString, Log("Connected successfully to bootloader.").GetInfoMsg()));
        }
        else if ((nullptr != log) && (Status == BL_CMD_EXEC_FAILED_STATUS)) {
            QMetaObject::invokeMethod(log,
                                      "appendPlainText",
                                      Qt::AutoConnection,
                                      Q_ARG(QString, Log("Failed to Connect to bootloader.").GetInfoMsg()));
        }
        else if(Status == BL_CMD_EXEC_FAILED_STATUS){
            return ;
        }
        QThread::msleep(100);

    }

    /*4. Erase application.*/
    if (nullptr != CurrentTask_Label){
        QMetaObject::invokeMethod(CurrentTask_Label,
                                  "setText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, "Current Task : Erase Application"));
    }

    if (nullptr != log){
        QMetaObject::invokeMethod(log,
                                  "appendPlainText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, Log("Start erasing application.").GetInfoMsg()));
    }




    Status = SendCommand(HOST_CMD_ERASE_APP_IMAGE, DeviceID, 0, 0, &RetValue);

    if ((nullptr != log) && (Status == BL_CMD_EXEC_SUCCEED_STATUS)){
        QMetaObject::invokeMethod(log,
                                  "appendPlainText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, Log("Application erased successfully.").GetInfoMsg()));
    }
    else if ((nullptr != log) && (Status == BL_CMD_EXEC_FAILED_STATUS)) {
        QMetaObject::invokeMethod(log,
                                  "appendPlainText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, Log("Failed to erase application.").GetInfoMsg()));
    }
    else if(Status == BL_CMD_EXEC_FAILED_STATUS){
        return ;
    }


    /*5. Flash new image.*/
    if (nullptr != CurrentTask_Label){
        QMetaObject::invokeMethod(CurrentTask_Label,
                                  "setText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, "Current Task : Flash image"));
    }
    quint32 address, value;
    quint8 ProgressPercentage;
    for (quint32 i = 0; i < hexParser->GetMaxSize(); i++){
        if (i<10){
            QThread::msleep(1000);
        }
        ProgressPercentage = (i*100)/hexParser->GetMaxSize();

        if ((nullptr != CurrentTaskProgressBar && (CurrentTaskProgressBar->value() != ProgressPercentage)) ){
            QMetaObject::invokeMethod(CurrentTaskProgressBar,
                                      "setValue",
                                      Qt::AutoConnection,
                                      Q_ARG(int, ProgressPercentage));
        }

        address = (i*2+hexParser->GetBaseAddress());
        value = hexParser->GetData(i);

        do{
            Status = SendCommand(HOST_CMD_WRITE_16BIT_DATA_AT, DeviceID, address, value, &RetValue);
        } while((BL_CMD_EXEC_FAILED_STATUS == Status) || (255 != RetValue));


        if((nullptr != log) && (Status == BL_CMD_EXEC_FAILED_STATUS)){
            QString msg="Failed to write at address 0x";
            msg += QString::number(address, 16);
            msg += ".";
            QMetaObject::invokeMethod(log,
                                      "appendPlainText",
                                      Qt::AutoConnection,
                                      Q_ARG(QString, Log(msg).GetErrorMsg()));
            return ;
        }
    }
    /*6. Set Image validation flag.*/
    Status = SendCommand(HOST_CMD_SET_VALID_IMAGE, DeviceID, 0, 0, &RetValue);

    if((nullptr != log) && (Status == BL_CMD_EXEC_FAILED_STATUS)){
        QString msg="Failed to Set Image validation flag";
        QMetaObject::invokeMethod(log,
                                  "appendPlainText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, Log(msg).GetErrorMsg()));
        return ;
    }

    /*7. Jump to application.*/
    SendCommand(HOST_CMD_JumpToApp, DeviceID, 0, 0, &RetValue);

    if (nullptr != log){
        QMetaObject::invokeMethod(log,
                                  "appendPlainText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, Log("Jump to application.").GetInfoMsg()));
    }

    /*Progress Bar to 100%*/
    if (nullptr != CurrentTaskProgressBar ){
        QMetaObject::invokeMethod(CurrentTaskProgressBar,
                                  "setValue",
                                  Qt::AutoConnection,
                                  Q_ARG(int, 100));
    }
}

BL_Exec_St Communication::SendCommand(quint32 Command, quint32 Flags, quint32 Param_1, quint32 Param_2, quint8 *Arg_Retval)
{
    QByteArray data;
    quint32 L_ConnectCommand_qint32 = (quint32)Command;
    data.append((char *)&L_ConnectCommand_qint32, sizeof(L_ConnectCommand_qint32));
    data.append((char *)&Flags,    sizeof(Flags));
    data.append((char *)&Param_1,    sizeof(Param_1));
    data.append((char *)&Param_2,    sizeof(Param_2));

    ImageFlash_Serial_Port.write(data);
    ImageFlash_Serial_Port.waitForBytesWritten();

    /*Set Default return value*/
    *Arg_Retval = -1;
    if ((Command == HOST_CMD_ConnectToBL) ||
            (Command == HOST_CMD_ConnectToApp) ||
            (Command == HOST_CMD_JumpToApp)){

        return BL_CMD_EXEC_SUCCEED_STATUS;
    }

    char EchoValue = 0, Status=-1;

    if (ImageFlash_Serial_Port.isOpen()){
        while (ImageFlash_Serial_Port.waitForReadyRead(3600*1000)){
            ImageFlash_Serial_Port.read(&Status, 1);
            ImageFlash_Serial_Port.read(&EchoValue, 1);
            *Arg_Retval = (quint8) EchoValue;
            break;
        }

    }
    return (BL_Exec_St) Status;

}

bool Communication::IsConnected()
{
    return ImageFlash_Serial_Port.isOpen();
}



Communication::~Communication()
{
    if (ImageFlash_Serial_Port.isOpen()){
        ImageFlash_Serial_Port.close();
    }
}




