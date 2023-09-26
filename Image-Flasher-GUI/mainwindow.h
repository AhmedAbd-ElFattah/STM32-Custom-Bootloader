#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QSerialPort>
#include <QMessageBox>
#include <QThread>
#include "hexparser.h"
#include "log.h"
#include "common.h"

#include "communication.h"
#include "availableboards.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define MAX_READ_BYTES (2*4)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BrowseHexFile_pushButton_clicked();
    void on_Flash_pushButton_clicked();
    void on_RefreshAvailableBoards_pushButton_clicked();
    void on_connect_pushButton_clicked();
    void on_communication_comboBox_currentIndexChanged(int index);

private:

    QThread ParsingFileThread;
    QThread CommunicationThread;
    AvailableBoards BoardSelector;

    HexParser Hexparser_obj;
    Communication CommuncationWithBoard;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
