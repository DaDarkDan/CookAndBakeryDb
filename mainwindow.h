#include "iomanager.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QFrame;
class QTextEdit;
class QPushButton;
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
    void onAddedFrameDeleteButton_clicked();

    void on_createAddKeywordBtn_clicked();

    void on_uploadImgBtn_clicked();

private:
    Ui::MainWindow *ui;
    RecipeManager* rm;
    vector<QWidget*> addedIngredientFrameList;
    vector<QWidget*> addedKeywordFrameList;

    QFrame* createFrame() const;
    QTextEdit* createTextEdit(const QString &value, int minH, int maxH, int minW, int maxW) const;
    QPushButton* createDeleteButton() const;

    void setupSearchPage();
    void setupCreatePage();
    void setupHomePage();

    void setupSearchIngredientScrollView();
    void setupSearchKeywordScrollView();
};

#endif // MAINWINDOW_H
