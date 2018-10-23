#include "changedialog.h"
#include "ui_changedialog.h"

ChangeDialog::ChangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDialog)
{
    ui->setupUi(this);
}

ChangeDialog::~ChangeDialog()
{
    delete ui;
}
