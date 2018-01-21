#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLocalSocket;

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
    void on_pushButtonConnect_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonSend_clicked();
    void on_pushButtonQuit_clicked();
    //
    void receiveMessage();

private:
    Ui::MainWindow *ui;
    QLocalSocket *mSocket;
};

#endif // MAINWINDOW_H
