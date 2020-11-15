#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLineEdit"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Create the Message
    messages = new Messages();

    //Attach it to the List View
    ui->messagesListView->setModel(messages);

    //Create the network layer
    network = new Network(this);

    //connect the sendButton and ReturnKey to validation/send method
    connect(this->ui->sendButton, &QPushButton::pressed, this, &MainWindow::doCheckAndSendMessages);
    connect(this->ui->messageEdit, &QLineEdit::returnPressed, this, &MainWindow::doCheckAndSendMessages);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doCheckAndSendMessages()
{
    //grab trimmed message from send box
    QString messageString = this->ui->messageEdit->text().trimmed();

    //check that the string isn't empty
    if(messageString.size() == 0)
    {
        return;
    }

    //clear the user input box
    this->ui->messageEdit->clear();

    //append to the model
    this->messages->append(messageString);
}

