#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "messages.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Messages* messages;

private slots:
    void doCheckAndSendMessages();

};
#endif // MAINWINDOW_H