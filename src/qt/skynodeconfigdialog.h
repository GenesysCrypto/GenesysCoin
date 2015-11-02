#ifndef SKYNODECONFIGDIALOG_H
#define SKYNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class SkyNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class SkyNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SkyNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:9999", QString privkey="MASTERNODEPRIVKEY");
    ~SkyNodeConfigDialog();

private:
    Ui::SkyNodeConfigDialog *ui;
};

#endif // SKYNODECONFIGDIALOG_H
