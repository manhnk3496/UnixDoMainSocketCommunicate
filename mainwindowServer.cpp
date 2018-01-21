#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLocalServer>
#include <QTextStream>
#include <QLocalSocket>
#include <QProcess>
#include <QFileDialog>
#include <QBuffer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditAccess->setEnabled(false);
    //
    mSocket = new QLocalSocket();
    mServer = new QLocalServer(this);
    mProcess = new QProcess(this);
    //
    connect(mServer,SIGNAL(newConnection()),this,SLOT(handleConnect()));
    connect(ui->pushButtonSend, SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(ui->lineEditChat, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//close program.
void MainWindow::on_pushButtonQuit_clicked()
{
    close();
}

//Open client program by server program.
void MainWindow::on_pushButtonOpen_clicked()
{
    if(!mProcess->isOpen()){
        auto program = ui->lineEditAccess->text();
        QStringList args;
        mProcess->setProgram(program);
        mProcess->setArguments(args);
        mProcess->start();
        ui->pushButtonOpen->setText("Close Client");
        if(mProcess->isOpen()){
            ui->labelNotification->setText("Process is running!!");
        }
        else
        {
            ui->labelNotification->setText(mProcess->errorString());
        }
    }
    else{
        mProcess->close();
        ui->pushButtonOpen->setText("Open");
        if(!mProcess->open()){
            ui->labelNotification->setText("Program is close!");
        }
    }
}


// Send message to Client.
void MainWindow::on_pushButtonSend_clicked()
{
}

// Listenning from client.
//complete.
void MainWindow::on_pushButtonListen_clicked()
{
    if(mServer->listen("ma")){
        ui->labelNotification->setText("Start...");
    }
    else
    {
        ui->labelNotification->setText(mServer->errorString());
    }
}

//clear content chat.
//complete.
void MainWindow::on_pushButtonClear_clicked()
{
    ui->textBrowserContent->clear();
}

/*.........................................
 * Functions are written by manually.
 *
 *
 ..........................................*/

//handle function when have a new connect.
void MainWindow::handleConnect()
{
    mSocket = mServer->nextPendingConnection();
    connect(mSocket,SIGNAL(readyRead()), this, SLOT(receiveMessage()));



//    connections.append(mSocket);
//    QBuffer *buffer = new QBuffer(this);
//    buffer->open(QIODevice::ReadWrite);
//    bufffers.insert(mSocket, buffer);
}

//Handle fuction when receive message.
void MainWindow::receiveMessage()
{
//    mSocket = static_cast<QLocalSocket*>(sender());


    ui->labelNotification->setText("New message!!!");
    QTextStream T(mSocket);
    ui->textBrowserContent->append("Client: " + T.readAll());
}


//send message
//complete
void MainWindow::sendMessage()
{
    if(mSocket){
        QTextStream T(mSocket);
        T << ui->lineEditChat->text();
        mSocket->flush();
    }
    ui->textBrowserContent->append("Me: " + ui->lineEditChat->text());
    ui->lineEditChat->clear();
}


//Set access
//complete
void MainWindow::on_toolButtonAccess_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this, tr(""), "/", "");
    if(filename.isEmpty()){
        return;
    }
    ui->lineEditAccess->setText(filename);
}
