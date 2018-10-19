#include "recipe.h"
#include "recipecompare.h"
#include "QMap"

#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

class QFrame;
class QVBoxLayout;
class QPushButton;
class QLayout;
class RecipeManager;
class MainWindow;
class QComboBox;
class QTextEdit;
class QCheckBox;
class QLabel;
class ClickableLabel;
class StarEditor;

class SearchPage : public QObject
{
    Q_OBJECT

public:
    SearchPage(MainWindow* mw, QWidget* searchAddedIngredientScrollAreaContents, QWidget* searchIngredientScrollAreaContents,
               QComboBox* searchCategoryComboBox, QComboBox* searchFavouriteComboBox, QTextEdit* searchRecipenameTxtEdit,
               QTextEdit* searchIngredientTextEdit, QWidget* searchKeywordScrollAreaContents, QWidget* searchAddedKeywordScrollAreaContents,
               QTextEdit* searchKeywordTextEdit, QWidget* searchFoundRecipesScrollViewContents, QFrame* searchRatingStarFrame,
               QCheckBox* searchIncludeRatingCheckBox, ClickableLabel* searchResultImgLabel, QComboBox* searchSortComboBox);

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

    void on_searchIncludeRatingCheckBox_stateChanged(int arg1);

    void updateFoundRecipes();

    void on_searchTabOpened();
    void on_searchSortComboBox_currentIndexChanged(int index);

private slots:
    void displaySearchResultImage(QPixmap pixmap, QString path);
    void ratingEditingFinished();

    void openDeleteMessageBox(Recipe* recipe);

private:
    MainWindow* mw;

    void setupSearchIngredientScrollViews();
    void setupSearchKeywordScrollView();
    void deleteLayoutAndWidgetsScrollView(QLayout* layout);
    QFrame* getRecipeAsFrame(Recipe* recipe, int index);

    void addButtonToScrollAreaContentsLayout(QVBoxLayout* layout, QPushButton* button);

    void on_searchIngredientKeyword_textChanged(QTextEdit* txtEdit, QLayout* layout);

    void deleteRecipe(Recipe* recipe);

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
    QCheckBox* searchIncludeRatingCheckBox;
    ClickableLabel* searchResultImgLabel;
    QComboBox* searchSortComboBox;

    StarEditor* starEditor = nullptr;

    QString sortings[9] = {"Name aufsteigend", "Name absteigend",
                          "Datum aufsteigend", "Datum absteigend",
                          "Kategorie aufsteigend", "Kategorie absteigend",
                          "Favorit",
                          "Bewertung aufsteigend",  "Bewertung absteigend"};
};

#endif // SEARCHPAGE_H
