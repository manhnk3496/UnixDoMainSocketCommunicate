#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLocalSocket>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSocket = new QLocalSocket(this);
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//connect to server
void MainWindow::on_pushButtonConnect_clicked()
{
    mSocket->connectToServer("ma");
    ui->labelNotification->setText("Start...");
}

//clear content chat
void MainWindow::on_pushButtonClear_clicked()
{
    ui->textBrowserContent->clear();
}

//send message to server
void MainWindow::on_pushButtonSend_clicked()
{
    if(mSocket){
        QTextStream T(mSocket);
        T << ui->lineEditChat->text();
        mSocket->flush();
    }
    ui->textBrowserContent->append("Me: "+ ui->lineEditChat->text());
    ui->lineEditChat->clear();
}

//close program
void MainWindow::on_pushButtonQuit_clicked()
{
    close();
}

/*.................................................
    Functions are written by manually
 ..................................................*/

void MainWindow::receiveMessage()
{
//    QTextStream T(mSocket);
//    ui->textBrowserContent->append(T.readAll());
    ui->textBrowserContent->append("Server: "+mSocket->readAll());
}


