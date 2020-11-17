#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLineEdit"
#include "QInputDialog"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Before starting the application, prompt the user for their desired port
    bool ok = false;
    while(!ok){
        int portChoice = QInputDialog::getInt(this, "Select hosting port",
                                              "What port do you want to host your chat on? (Cancel to quit)",
                                              0, 0, 65535, 1, &ok);
        if(ok){
            network = new Network(portChoice, this);
        }else{
            exit(0);
        }

    }

    //Create the Message
    messages = new Messages();

    //Attach it to the List View
    ui->messagesListView->setModel(messages);

    //connect the sendButton and ReturnKey to validation/send method
    connect(this->ui->sendButton, &QPushButton::pressed, this, &MainWindow::doCheckAndSendMessages);
    connect(this->ui->messageEdit, &QLineEdit::returnPressed, this, &MainWindow::doCheckAndSendMessages);

    //connect the connectButton to show connect UI
    connect(this->ui->connectButton, &QPushButton::pressed, this, &MainWindow::openConnectToDialog);
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

void MainWindow::openConnectToDialog(){

    ConnectToDialog* connectToDialog =  new ConnectToDialog();
    connect(connectToDialog, &ConnectToDialog::userIntendsConnection, network, &Network::connectToClient);
    connectToDialog->show();
}

