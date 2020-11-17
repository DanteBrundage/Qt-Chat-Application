#include "connecttodialog.h"
#include "ui_connecttodialog.h"

ConnectToDialog::ConnectToDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToDialog)
{
    ui->setupUi(this);
}

ConnectToDialog::~ConnectToDialog()
{
    delete ui;
}
