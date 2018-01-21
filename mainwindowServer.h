#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QHash>

class QLocalServer;
class QLocalSocket;
class QBuffer;
class QProcess;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonQuit_clicked();
    void on_pushButtonOpen_clicked();
    void on_pushButtonSend_clicked();
    void on_pushButtonListen_clicked();
    void on_pushButtonClear_clicked();
    void sendMessage();
    //
    void handleConnect();
    void receiveMessage();

    void on_toolButtonAccess_clicked();

private:
    Ui::MainWindow *ui;
    QLocalServer *mServer;
    QLocalSocket *mSocket;
    QList<QLocalSocket*> connections;
    QHash<QLocalSocket*, QBuffer*> bufffers;
    QProcess *mProcess;
};

#endif // MAINWINDOW_H
