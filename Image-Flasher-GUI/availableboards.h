#ifndef AVAILABLEBOARDS_H
#define AVAILABLEBOARDS_H
/*
 * File Name --> availableboards.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Searches for all available boards and added them to comboboc in gui
 *               Searching is based on Configured values of
 *               APP_CONFIG_Board_VendorId, APP_CONFIG_Board_ProductId,
 *               APP_CONFIG_Board_Manufacturer, and APP_CONFIG_Board_Description
 *               in "ApplicationConfigurations.h" file
 * */
#include "ApplicationConfigurations.h"
#include <QComboBox>
#include <QSerialPortInfo>
#include <QMessageBox>

class AvailableBoards
{
private:
    /*Combobox that shows available boards*/
    QComboBox * availableBoardComboBox = nullptr;
    QList<QSerialPortInfo> ports;
    QVector<QSerialPortInfo> Boards;
public:
    AvailableBoards();
    AvailableBoards(QComboBox *Arg_AvailableBoardComboBox);
    /*Assign combobox that shows available boards*/
    void AssignComboBox(QComboBox *Arg_AvailableBoardComboBox);
    /*Return the port name for the selected board in combobox.*/
    QString GetPortName();

    void Refresh();

    ~AvailableBoards();
};

#endif // AVAILABLEBOARDS_H
