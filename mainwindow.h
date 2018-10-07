#include "iomanager.h"
#include "QVBoxLayout"

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

    void on_pushButton_clicked(); //TODO remove

    //create
    void on_createSaveBtn_clicked();
    void on_createAddIngredientBtn_clicked();
    void onAddedFrameDeleteButton_clicked();
    void on_createAddKeywordBtn_clicked();
    void on_uploadImgBtn_clicked();

    //search
    void on_searchAddIngredient_clicked();
    void on_searchDeleteIngredient_clicked();
    void on_searchRecipenameTxtEdit_textChanged();

    void on_searchAddKeyword_clicked();
    void on_searchDeleteKeyword_clicked();

    void on_searchIngredientTextEdit_textChanged();

    void on_searchKeywordTextEdit_textChanged();

    void on_searchResetButton_clicked();

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

    //search
    void setupSearchIngredientScrollViews();
    void setupSearchKeywordScrollView();
    void searchFoundRecipesScrollViewContents();
    void fillFoundRecipeScrollView();
    QFrame* getRecipeAsFrame(const Recipe& recipe);

    void addButtonToScrollAreaContentsLayout(QVBoxLayout* layout, QPushButton* button);

    void on_searchIngredientKeyword_textChanged(QObject* sender, QLayout* layout);

    QHBoxLayout* createStarEditorFrameLayout() const;

};

#endif // MAINWINDOW_H
