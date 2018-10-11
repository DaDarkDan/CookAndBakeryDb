#include "recipe.h"

#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

class QFrame;
class QVBoxLayout;
class QPushButton;
class QObject;
class QLayout;
class RecipeManager;
class MainWindow;
class QComboBox;
class QTextEdit;

class SearchPage
{
public:
    SearchPage(MainWindow* mw, QWidget* searchAddedIngredientScrollAreaContents, QWidget* searchIngredientScrollAreaContents,
               QComboBox* searchCategoryComboBox, QComboBox* searchFavouriteComboBox, QTextEdit* searchRecipenameTxtEdit,
               QTextEdit* searchIngredientTextEdit, QWidget* searchKeywordScrollAreaContents, QWidget* searchAddedKeywordScrollAreaContents,
               QTextEdit* searchKeywordTextEdit, QWidget* searchFoundRecipesScrollViewContents, QFrame* searchRatingStarFrame);

    void setup();

    void on_searchAddIngredient_clicked(QPushButton* button);
    void on_searchDeleteIngredient_clicked(QPushButton* button);
    void on_searchAddKeyword_clicked(QPushButton* button);
    void on_searchDeleteKeyword_clicked(QPushButton* button);

    void on_searchRecipenameTxtEdit_textChanged();
    void on_searchIngredientTextEdit_textChanged(QTextEdit* txtEdit, QLayout* layout);
    void on_searchKeywordTextEdit_textChanged(QTextEdit* txtEdit, QLayout* layout);

    void on_searchCategoryComboBox_currentIndexChanged(int index);
    void on_searchFavouriteComboBox_currentIndexChanged(int index);

    void on_searchResetButton_clicked();

private:
    MainWindow* mw;

    void setupSearchIngredientScrollViews();
    void setupSearchKeywordScrollView();
    void deleteLayoutAndWidgetsScrollView(QLayout* layout);
    void fillFoundRecipesScrollViewContents();
    QFrame* getRecipeAsFrame(const Recipe& recipe);

    void addButtonToScrollAreaContentsLayout(QVBoxLayout* layout, QPushButton* button);

    void on_searchIngredientKeyword_textChanged(QTextEdit* txtEdit, QLayout* layout);

    QWidget* searchAddedIngredientScrollAreaContents;
    QWidget* searchIngredientScrollAreaContents;
    QComboBox* searchCategoryComboBox;
    QComboBox* searchFavouriteComboBox;
    QTextEdit* searchRecipenameTxtEdit;
    QTextEdit* searchIngredientTextEdit;
    QWidget* searchKeywordScrollAreaContents;
    QWidget* searchAddedKeywordScrollAreaContents;
    QTextEdit* searchKeywordTextEdit;
    QWidget* searchFoundRecipesScrollViewContents;
    QFrame* searchRatingStarFrame;
};

#endif // SEARCHPAGE_H
