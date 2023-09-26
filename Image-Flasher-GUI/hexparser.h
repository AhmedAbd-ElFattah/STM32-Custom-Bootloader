/*
 * File Name --> hexparser.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Parse hex file.
 * */

#ifndef HEXPARSER_H
#define HEXPARSER_H
#include "log.h"
#include <QString>
#include <QFile>
#include <QStringRef>
#include <QTextStream>

#include <QDebug>
#include <QtCore>
#include <QThread>
#include <QTableWidget>
#include <QProgressBar>
#include <QPlainTextEdit>

#include "common.h"
#include <algorithm>
#include <QLabel>
#include "infosystem.h"
#include <QSharedPointer>

struct Data{
    quint32  address;
    quint32  value;
};


struct HexProps{
    quint32  StartAddress;
    quint32  EndAddress;
    quint32  Size;
    qint16   LinesCount;
};

enum HexRecordTypes{
    HexFile_DataRecord=0,
    HexFile_HighAddress=4,
};

class HexParser :  public QThread
{
private:
    /*UI objects*/
    /*Table that shows HEX data*/
    QTableWidget *HexTable_pQTableWidget = nullptr;
    /*Progress bar that shows the progress of hex parsing*/
    QProgressBar *CurrentTaskProgressBar = nullptr;
    /*Label that prints path of file*/
    QLabel *LoadedHexFile_Label = nullptr;
    /*Label that shows current processing task*/
    QLabel *CurrentTask_Label = nullptr;

    QPlainTextEdit *log=nullptr;
    /*File path of Hex file*/
    QString L_FilePath_QString;
    /*Hex File properties*/
    HexProps L_BL_File_HexProps;
    /*Dynamic array of Hex files data values*/
    quint32* Data_Array = nullptr;
    QString convertString(const QString& Arg_Record_QString);

    bool FileLoaded=false;


public:
    /*Get data with relative address*/
    quint32 GetData(quint32 Arg_RelativeAddress_quint32);
    /*Get base address*/
    quint32 GetBaseAddress();
    quint32 GetMaxSize();
    /*Delete and deallocate previoud parsed data*/
    void DeleteOldData();

    void SetHexFilePath(QString FilePath);
    void SetProgressBar(QProgressBar *Arg_TaskProgressBar);
    void SetHexFileTable(QTableWidget *Arg_HexTable_pQTableWidget);
    void SetLoadedHexFile(QLabel *Arg_LoadedHexFile_Label);
    void SetCurrentTask(QLabel *Arg_CurrentTask_Label);
    void SetLogUIObject(QPlainTextEdit *Arg_log);

    bool IsFileLoaded();
    HexProps GetHexFileProps();

    void run() override;
    ~HexParser();

};

#endif // HEXPARSER_H
