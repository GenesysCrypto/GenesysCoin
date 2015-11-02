#ifndef ADDEDITSKYNODE_H
#define ADDEDITSKYNODE_H

#include <QDialog>

namespace Ui {
class AddEditSkyNode;
}


class AddEditSkyNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditSkyNode(QWidget *parent = 0);
    ~AddEditSkyNode();

protected:

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

signals:

private:
    Ui::AddEditSkyNode *ui;
};

#endif // ADDEDITSKYNODE_H
