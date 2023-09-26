#include "availableboards.h"



AvailableBoards::AvailableBoards()
{

}

void AvailableBoards::AssignComboBox(QComboBox *Arg_AvailableBoardComboBox)
{
    availableBoardComboBox = Arg_AvailableBoardComboBox;
    Refresh();
}

AvailableBoards::AvailableBoards(QComboBox *Arg_AvailableBoardComboBox):availableBoardComboBox(Arg_AvailableBoardComboBox)
{
    Refresh();
}

QString AvailableBoards::GetPortName()
{
    if (nullptr == availableBoardComboBox){
        return "";
    }
    /*Check if No available board.*/
    if (Boards.isEmpty()){
        QMessageBox::critical(nullptr, "No available board.",
                              "There isn't any selected board "
                              "Please connect board and refresh the list");
        Refresh();
        return "";
    }
    QSerialPortInfo SelectedPort = Boards.at(availableBoardComboBox->currentIndex());
    /*Check if selected board is empty.*/
    if (SelectedPort.isBusy()){
        QMessageBox::critical(nullptr, "Busy board.",
                              "Selected board is busy.");
        return "";
    }

    if (SelectedPort.isNull()){
        QMessageBox::critical(nullptr, "Null= board.",
                              "Selected board is Null.");
        return "";
    }

    if (!SelectedPort.isValid()){
        QMessageBox::critical(nullptr, "Not-valid board.",
                              "Selected board is not-valid or may disconnected.");
        return "";
    }

    return SelectedPort.systemLocation();
}

void AvailableBoards::Refresh()
{
    if (nullptr == availableBoardComboBox){
        return ;
    }
    /*Clear old data*/
    availableBoardComboBox->clear();
    Boards.clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    /*Search for board that match configured ones*/
    for (const QSerialPortInfo &port : ports) {

        if (
                (!port.hasProductIdentifier()) ||
                (APP_CONFIG_Board_VendorId != port.vendorIdentifier()) ||
                (!port.hasVendorIdentifier()) ||
                (APP_CONFIG_Board_ProductId != port.productIdentifier()) ||
                (!port.hasProductIdentifier()) ||
                (APP_CONFIG_Board_Manufacturer != port.manufacturer()) ||
                (APP_CONFIG_Board_Description != port.description())
                ){

            continue;
        }
        /*Add board to combobox in gui*/
        availableBoardComboBox->addItem(port.portName());
        /*Add port info to QVector to use this data
         * when GetPortName function is called by clicking on connect button.*/
        Boards.push_back(port);
    }

}

AvailableBoards::~AvailableBoards()
{
    if (nullptr != availableBoardComboBox){
        delete availableBoardComboBox;
        availableBoardComboBox = nullptr;
    }
}
