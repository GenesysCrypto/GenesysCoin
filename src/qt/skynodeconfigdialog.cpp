#include "skynodeconfigdialog.h"
#include "ui_skynodeconfigdialog.h"

#include <QModelIndex>

SkyNodeConfigDialog::SkyNodeConfigDialog(QWidget *parent, QString nodeAddress, QString privkey) :
    QDialog(parent),
    ui(new Ui::SkyNodeConfigDialog)
{
    ui->setupUi(this);
    QString desc = "rpcallowip=127.0.0.1<br>rpcuser=REPLACEME<br>rpcpassword=REPLACEME<br>server=1<br>listen=1<br>port=REPLACEMEWITHYOURPORT<br>staking=0<br>enableaccounts=1<br>masternode=1<br>masternodeaddr=" + nodeAddress + "<br>masternodeprivkey=" + privkey + "<br>";
    ui->detailText->setHtml(desc);
}

SkyNodeConfigDialog::~SkyNodeConfigDialog()
{
    delete ui;
}
