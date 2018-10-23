#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeDialog;
}

class ChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDialog(QWidget *parent = nullptr);
    ~ChangeDialog();

private:
    Ui::ChangeDialog *ui;
};

#endif // CHANGEDIALOG_H
