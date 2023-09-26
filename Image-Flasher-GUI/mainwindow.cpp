#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<QTextCursor>("QTextCursor");
    ui->setupUi(this);
    BoardSelector.AssignComboBox(ui->AvailableBoards_comboBox);

    Hexparser_obj.SetProgressBar(ui->CurrentTask_progressBar);
    Hexparser_obj.SetHexFileTable(ui->HexTable_tableWidget);
    Hexparser_obj.SetLoadedHexFile(ui->LoadedHexFile_label);
    Hexparser_obj.SetCurrentTask(ui->CurrentTask_label);
    Hexparser_obj.SetLogUIObject(ui->log_plainTextEdit);

    CommuncationWithBoard.SetLogUIObject(ui->log_plainTextEdit);
    CommuncationWithBoard.SetProgressBar(ui->CurrentTask_progressBar);
    CommuncationWithBoard.SetCurrentTask(ui->CurrentTask_label);
    CommuncationWithBoard.SetIdSpinBox(ui->deviceId_spinBox);
    CommuncationWithBoard.SetCommunicationSelectionCombobox(ui->communication_comboBox);

    /*Assign Threads*/
    ParsingFileThread.setObjectName("Parsing File Thread");
    CommunicationThread.setObjectName("Communication Thread");
    Hexparser_obj.moveToThread(&ParsingFileThread);
    CommuncationWithBoard.moveToThread(&CommunicationThread);

}

MainWindow::~MainWindow()
{
    /*Wait for thread to finish processing*/
    ParsingFileThread.wait(60*1000);
    CommunicationThread.wait(60*1000);

    delete ui;
}


void MainWindow::on_BrowseHexFile_pushButton_clicked()
{

    QString L_FileName_QString;

    if (Hexparser_obj.isRunning()){
        QMessageBox::critical(nullptr, "File parsing.",
                              "Please wait till current file is parsed.");
        return ;
    }

    L_FileName_QString = QFileDialog::getOpenFileName(this,
                                                      tr("Open Hex File"),
                                                      "",
                                                      tr("Supported Files (*.hex)"));
    Hexparser_obj.SetHexFilePath(L_FileName_QString);
    if (!Hexparser_obj.isRunning()){
        Hexparser_obj.start();
    }

}


void MainWindow::on_Flash_pushButton_clicked()
{
    if (!Hexparser_obj.IsFileLoaded()){
        QMessageBox::critical(nullptr, "File not loaded.",
                              "Please load file and wait till file is parsed.");
        return;
    }


    CommuncationWithBoard.SetHexParser(&Hexparser_obj);

    if (CommuncationWithBoard.IsConnected()){
        CommuncationWithBoard.start();
    }
    else{
    }
}


void MainWindow::on_RefreshAvailableBoards_pushButton_clicked()
{
    BoardSelector.Refresh();
}


void MainWindow::on_connect_pushButton_clicked()
{
    if (!CommuncationWithBoard.IsConnected()){
        QString PortName = BoardSelector.GetPortName();
        if ("" == PortName){
            return;
        }


        /*Send All Filters*/

        CommuncationWithBoard.Connect(PortName);
        if (!CommuncationWithBoard.IsConnected()){
            QMessageBox::critical(nullptr, "Connection failed !",
                                  "Connection failed !, please try to refresh and connection again");
            on_RefreshAvailableBoards_pushButton_clicked();
            return ;
        }

        ui->connect_pushButton->setText("Dis-Connect");

    }
    else{

        CommuncationWithBoard.DisConnect();
        ui->connect_pushButton->setText("Connect");


    }
}


void MainWindow::on_communication_comboBox_currentIndexChanged(int index)
{
    BootloaderCommunication CurrentIndex = (BootloaderCommunication)index;
    switch(CurrentIndex){
    case Communication_UART:
        ui->deviceId_spinBox->setDisabled(true);
        break;
    case Communication_CAN:
        ui->deviceId_spinBox->setDisabled(false);
        ui->deviceId_spinBox->setValue(0);
        break;
    }
}

