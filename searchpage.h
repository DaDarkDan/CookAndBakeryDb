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
    SearchPage(RecipeManager* rm) : rm(rm){}
    void setup(MainWindow* mainWindow, QWidget* searchAddedIngredientScrollAreaContents, QWidget* searchIngredientScrollAreaContents,
               QComboBox* searchCategoryComboBox, QComboBox* searchFavouriteComboBox, QFrame* createRatingStarFrame,
               QWidget* searchAddedKeywordScrollAreaContents, QWidget* searchKeywordScrollAreaContents,
               QWidget* searchFoundRecipesScrollViewContents, QTextEdit* searchRecipenameTxtEdit);

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
    RecipeManager* rm;

    void setupSearchIngredientScrollViews(MainWindow* mainWindow, QWidget* searchAddedIngredientScrollAreaContents, QWidget* searchIngredientScrollAreaContents);
    void setupSearchKeywordScrollView(MainWindow* mainWindow, QWidget* searchAddedKeywordScrollAreaContents, QWidget* searchKeywordScrollAreaContents);
    void deleteLayoutAndWidgetsScrollView(QLayout* layout);
    void fillFoundRecipesScrollViewContents(QWidget* searchFoundRecipesScrollViewContents, QWidget* searchAddedIngredientScrollAreaContents,
                                            QWidget* searchAddedKeywordScrollAreaContents, QTextEdit* searchRecipenameTxtEdit,
                                            QComboBox* searchCategoryComboBox, QComboBox* searchFavouriteComboBox);
    QFrame* getRecipeAsFrame(const Recipe& recipe);

    void addButtonToScrollAreaContentsLayout(QVBoxLayout* layout, QPushButton* button);

    void on_searchIngredientKeyword_textChanged(QObject* sender, QLayout* layout);

};

#endif // SEARCHPAGE_H
