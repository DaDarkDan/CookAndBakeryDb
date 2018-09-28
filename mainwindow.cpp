#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recipe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    recipe = new Recipe();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createSaveBtn_clicked()
{
    QTextEdit* nameTxtEdit = findChild<QTextEdit*>("createNameTxtEdit");

    if (nameTxtEdit){
        recipe->setName(nameTxtEdit->toPlainText().toStdString());
    }

    QTextEdit* createNotesTxtEdit = findChild<QTextEdit*>("createNotesTxtEdit");

    if (createNotesTxtEdit){
        createNotesTxtEdit->setText(QString::fromStdString(recipe->getName()));
    }
}
