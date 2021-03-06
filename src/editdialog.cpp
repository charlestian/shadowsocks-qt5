#include "editdialog.h"
#include "ui_editdialog.h"
#include "ssvalidator.h"
#include "ip4validator.h"
#include "portvalidator.h"

EditDialog::EditDialog(Connection *_connection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog),
    connection(_connection)
{
    ui->setupUi(this);

    /* initialisation and validator setup */
    ui->encryptComboBox->addItems(SSValidator::supportedMethod);
    IP4Validator *addrValidator = new IP4Validator(this);
    PortValidator *portValidator = new PortValidator(this);
    ui->serverPortEdit->setValidator(portValidator);
    ui->localPortEdit->setValidator(portValidator);
    //Maybe we shouldn't validate local address using IPv4 format?
    ui->localAddrEdit->setValidator(addrValidator);

    ui->nameEdit->setText(connection->profile.name);
    ui->serverAddrEdit->setText(connection->profile.serverAddress);
    ui->serverPortEdit->setText(QString::number(connection->profile.serverPort));
    ui->localAddrEdit->setText(connection->profile.localAddress);
    ui->localPortEdit->setText(QString::number(connection->profile.localPort));
    ui->pwdEdit->setText(connection->profile.password);
    ui->encryptComboBox->setCurrentText(connection->profile.method.toUpper());
    ui->timeoutSpinBox->setValue(connection->profile.timeout);
    ui->debugCheckBox->setChecked(connection->profile.debug);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditDialog::save);
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::save()
{
    connection->profile.name = ui->nameEdit->text();
    connection->profile.serverAddress = ui->serverAddrEdit->text();
    connection->profile.serverPort = ui->serverPortEdit->text().toUShort();
    connection->profile.localAddress = ui->localAddrEdit->text();
    connection->profile.localPort = ui->localPortEdit->text().toUShort();
    connection->profile.password = ui->pwdEdit->text();
    connection->profile.method = ui->encryptComboBox->currentText();
    connection->profile.timeout = ui->timeoutSpinBox->value();
    connection->profile.debug = ui->debugCheckBox->isChecked();
    this->accept();
}
