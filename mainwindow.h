#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Recipe;

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

private:
    Ui::MainWindow *ui;

    Recipe* recipe;
};

#endif // MAINWINDOW_H
