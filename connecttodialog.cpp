#include "connecttodialog.h"
#include "ui_connecttodialog.h"

ConnectToDialog::ConnectToDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToDialog)
{
    ui->setupUi(this);

    //connect the "connect" button to fire off new
    //connectButtonPressed method
    //This is a standard button, so we connect to the
    //"accepted" method on the QDialogButtonBox
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ConnectToDialog::connectButtonPressed);
}

void ConnectToDialog::connectButtonPressed(){
    //grab valuesfrom dialog and cast
    //Note: Once again, there us notr erroe correction to save time

    QHostAddress address = QHostAddress(ui->ipAddressLineEdit->text().trimmed());
    quint64 port = (quint64)ui->portLineEdit->text().trimmed().toUInt();

    //Emit the signal
    emit userIntendsConnection(address, port);
}

ConnectToDialog::~ConnectToDialog()
{
    delete ui;
}
