#include "iomanager.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Recipe;
class RecipeManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createSaveBtn_clicked();

    void on_pushButton_clicked();

    void on_createAddIngredientBtn_clicked();

    void onIngredientDeleteButton_clicked();

private:
    Ui::MainWindow *ui;
    vector<QLayout*> addedIngredientList;
    vector<QLayout*> addedKeywordList;
};

#endif // MAINWINDOW_H
