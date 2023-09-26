#include "hexparser.h"

QString HexParser::convertString(const QString &Arg_Record_QString)
{
    QString modifiedString = Arg_Record_QString;
    for (int i = 0; i < modifiedString.length(); i += 4) {
        QChar temp1 = modifiedString[i];
        QChar temp2 = modifiedString[i + 1];
        modifiedString[i] = modifiedString[i + 2];
        modifiedString[i + 1] = modifiedString[i + 3];
        modifiedString[i + 2] = temp1;
        modifiedString[i + 3] = temp2;
    }

    return modifiedString;
}

quint32 HexParser::GetData(quint32 Arg_RelativeAddress_quint32){
    return Data_Array[Arg_RelativeAddress_quint32];
}

quint32 HexParser::GetBaseAddress()
{
    return L_BL_File_HexProps.StartAddress;
}

quint32 HexParser::GetMaxSize()
{
    return L_BL_File_HexProps.Size;
}

void HexParser::DeleteOldData()
{
    FileLoaded=false;
    if (nullptr != Data_Array){
        delete []Data_Array;
        Data_Array = nullptr;
    }
    if (nullptr != HexTable_pQTableWidget){
        while(HexTable_pQTableWidget->rowCount()){
            HexTable_pQTableWidget->removeRow(0);
        }
    }
}

void HexParser::SetHexFilePath(QString FilePath)
{
    FileLoaded = false;
    L_FilePath_QString = FilePath;
    DeleteOldData();
    /*To update Hex File properties*/
    L_BL_File_HexProps = GetHexFileProps();
}

void HexParser::SetProgressBar(QProgressBar *Arg_TaskProgressBar)
{
    CurrentTaskProgressBar = Arg_TaskProgressBar;
}

void HexParser::SetHexFileTable(QTableWidget *Arg_HexTable_pQTableWidget)
{
    HexTable_pQTableWidget = Arg_HexTable_pQTableWidget;
}

void HexParser::SetLoadedHexFile(QLabel *Arg_LoadedHexFile_Label)
{
    LoadedHexFile_Label = Arg_LoadedHexFile_Label;
}

void HexParser::SetCurrentTask(QLabel *Arg_CurrentTask_Label)
{
    CurrentTask_Label = Arg_CurrentTask_Label;
}

void HexParser::SetLogUIObject(QPlainTextEdit *Arg_log)
{
    log = Arg_log;
}

bool HexParser::IsFileLoaded()
{
    return FileLoaded==true;
}


HexProps HexParser::GetHexFileProps()
{
    QString CurrentLine;

    quint8 L_BytesCount_qint8, L_RecordType_qint8;
    quint32 L_Address_quint32;
    quint16 L_LowAddress_quint16=0, L_HighAddress_quint16=0;

    bool ok;


    L_BL_File_HexProps.StartAddress = 0xFFFFFFFF;
    L_BL_File_HexProps.EndAddress   = 0x00000000;
    L_BL_File_HexProps.LinesCount = 0;

    QFile file(L_FilePath_QString);
    if (file.open(QIODevice::ReadOnly)){
        QTextStream Lines(&file);
        while(!Lines.atEnd()){
            L_BL_File_HexProps.LinesCount += 1;
            CurrentLine = Lines.readLine();
            L_BytesCount_qint8  = CurrentLine.mid(1, 2).toUInt(&ok, 16);
            L_LowAddress_quint16   = CurrentLine.mid(3, 4).toUInt(&ok, 16);
            L_RecordType_qint8  = CurrentLine.mid(7, 2).toUInt(&ok, 16);

            switch (L_RecordType_qint8) {
            /*Record Type --> 0 (Data record)*/
            case HexFile_DataRecord:
                L_Address_quint32 = 0;
                L_Address_quint32 |= L_LowAddress_quint16;
                L_Address_quint32 |= (L_HighAddress_quint16 << 16);
                L_BL_File_HexProps.StartAddress = std::min(L_BL_File_HexProps.StartAddress, L_Address_quint32);
                L_BL_File_HexProps.EndAddress   = std::max(L_BL_File_HexProps.EndAddress, L_Address_quint32 + 4*L_BytesCount_qint8);
                break;

                /*Record Type --> 4 (High address)*/
            case HexFile_HighAddress:
                L_HighAddress_quint16 = CurrentLine.mid(9, 4).toUInt(&ok, 16);
                break;
            }


        }
    }
    if ( 0!=  (L_BL_File_HexProps.EndAddress %4)){
        L_BL_File_HexProps.EndAddress += 2;
    }
    L_BL_File_HexProps.Size = (L_BL_File_HexProps.EndAddress - L_BL_File_HexProps.StartAddress)/2;
    file.close();
    return L_BL_File_HexProps;
}


void HexParser::run()
{
    if (nullptr != log){
        QMetaObject::invokeMethod(log,
                                  "appendPlainText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, Log("Start Parsing File").GetInfoMsg()));
    }

    /*Current Task*/
    if(nullptr != CurrentTask_Label){
        QMetaObject::invokeMethod(CurrentTask_Label,
                                  "setText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, "Current Task : Parse HEX File."));
    }

    /*If there is previously allocated array, delete it*/
    if (nullptr != Data_Array){
        delete [] Data_Array;
        Data_Array = nullptr;
    }

    /*Allocate new array*/
    Data_Array = new quint32[L_BL_File_HexProps.Size];
    /*Fill Array with 0*/
    std::fill(Data_Array, Data_Array+L_BL_File_HexProps.Size, 0);

    QString CurrentLine, L_DataBytes_QString;

    quint8 L_BytesCount_qint8, L_RecordType_qint8;
    quint32 L_Address_quint32;
    quint16 L_LowAddress_quint16=0, L_HighAddress_quint16=0;

    bool ok;
    quint16 L_CurrentLine=0  ;
    quint8 ProgressPercentage;

    QFile file(L_FilePath_QString);

    if (!file.open(QIODevice::ReadOnly)){
        return;
    }

    QTextStream Lines(&file);
    while(!Lines.atEnd()){
        L_CurrentLine += 1;
        CurrentLine = Lines.readLine();
        L_BytesCount_qint8  = CurrentLine.mid(1, 2).toUInt(&ok, 16);
        L_LowAddress_quint16   = CurrentLine.mid(3, 4).toUInt(&ok, 16);
        L_RecordType_qint8  = CurrentLine.mid(7, 2).toUInt(&ok, 16);

        switch (L_RecordType_qint8) {

        case HexFile_DataRecord:
            L_Address_quint32 = 0;
            L_Address_quint32 |= L_LowAddress_quint16;
            L_Address_quint32 |= (L_HighAddress_quint16 << 16);
            quint32 L_RelativeAddress_quint32;
            L_DataBytes_QString = convertString(CurrentLine.mid(9, CurrentLine.length()-11));
            for (quint32 L_i_quint32=0; L_i_quint32 <(L_BytesCount_qint8*2) ;L_i_quint32 += 4){
                L_RelativeAddress_quint32 = (L_Address_quint32+ (L_i_quint32/2) - L_BL_File_HexProps.StartAddress)/2;
                if (L_RelativeAddress_quint32 < L_BL_File_HexProps.Size){
                    Data_Array[L_RelativeAddress_quint32] = L_DataBytes_QString.mid(L_i_quint32, 4).toUInt(&ok, 16);
                }

                if (L_BL_File_HexProps.LinesCount){
                    ProgressPercentage = ((L_CurrentLine*100)/L_BL_File_HexProps.LinesCount);



                    if ((nullptr != CurrentTaskProgressBar && (CurrentTaskProgressBar->value() != ProgressPercentage)) ){
                        QThread::msleep(1);
                        QMetaObject::invokeMethod(CurrentTaskProgressBar,
                                                  "setValue",
                                                  Qt::AutoConnection,
                                                  Q_ARG(int, ProgressPercentage));
                    }
                }

            }

            break;

        case HexFile_HighAddress:
            L_HighAddress_quint16 = CurrentLine.mid(9, 4).toUInt(&ok, 16);
            break;
        }
    }


    file.close();
    /*Loaded Hex File*/
    if(nullptr != LoadedHexFile_Label){
        QMetaObject::invokeMethod(LoadedHexFile_Label,
                                  "setText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, QString("Loaded Hex File : %1").arg(L_FilePath_QString)));
    }
    /*Finish Parsing File*/
    if ((nullptr != CurrentTaskProgressBar) ){
        QThread::msleep(2);
        //        CurrentTaskProgressBar->setValue(100);
        QMetaObject::invokeMethod(CurrentTaskProgressBar,
                                  "setValue",
                                  Qt::AutoConnection,
                                  Q_ARG(int, 100));
    }

    FileLoaded = true;

    if (nullptr != log){
        //        log->appendPlainText(Log("Finished Parsing File").GetInfoMsg());
        QMetaObject::invokeMethod(log,
                                  "appendPlainText",
                                  Qt::AutoConnection,
                                  Q_ARG(QString, Log("Finished Parsing File").GetInfoMsg()));
    }
    if (nullptr != HexTable_pQTableWidget){
        /*Clear table*/

        while (HexTable_pQTableWidget->rowCount()) {
            HexTable_pQTableWidget->removeRow(0);
        }

        /*Fill with new HexFile values*/
        int CurrentRowCount;
        for (quint32 i = 0; i < GetMaxSize(); i++){
            QThread::msleep(1);
            CurrentRowCount = HexTable_pQTableWidget->rowCount();
            QMetaObject::invokeMethod(HexTable_pQTableWidget,
                                      "insertRow",
                                      Qt::AutoConnection,
                                      Q_ARG(int, CurrentRowCount));
            QThread::msleep(1);

            HexTable_pQTableWidget->setItem(CurrentRowCount-1,
                                            0,
                                            new QTableWidgetItem("0x"+QString::number((i*2+GetBaseAddress()), 16)));
            HexTable_pQTableWidget->setItem(CurrentRowCount-1,
                                            1,
                                            new QTableWidgetItem("0x"+QString::number(GetData(i), 16)));

        }
    }
}

HexParser::~HexParser()
{
    if (nullptr != Data_Array){
        delete [] Data_Array;
        Data_Array = nullptr;
    }
}
