#include "iomanager.h"
#include "QVBoxLayout"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QFrame;
class QTextEdit;
class QPushButton;
class RecipeManager;
class CreatePage;
class SearchPage;
class HomePage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QHBoxLayout* createStarEditorFrameLayout();
    static QTextEdit* createCustomTextEdit(const QString &value, int minH, int maxH, int minW, int maxW);
    static QFrame* createCustomFrame();

    QPushButton* createCustomDeleteButton();

private slots:

    void on_pushButton_clicked(); //TODO remove

    //create
    void on_createSaveBtn_clicked();
    void on_createAddIngredientBtn_clicked();
    void on_addedFrameDeleteButton_clicked();
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

    void on_searchCategoryComboBox_currentIndexChanged(int index);

    void on_searchFavouriteComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    CreatePage* cp;
    SearchPage* sp;
    HomePage* hp;

    RecipeManager* rm;
    vector<QWidget*> addedIngredientFrameList;
    vector<QWidget*> addedKeywordFrameList;

    void setupSearchPage();
    void setupCreatePage();
    void setupHomePage();

    //search
    QFrame* getRecipeAsFrame(const Recipe& recipe);

    void addButtonToScrollAreaContentsLayout(QVBoxLayout* layout, QPushButton* button);

    void on_searchIngredientKeyword_textChanged(QObject* sender, QLayout* layout);
};

#endif // MAINWINDOW_H
