#include "searchpage.h"
#include "mainwindow.h"
#include "recipemanager.h"

#include "QLayoutItem"
#include "QLayout"
#include "QWidget"
#include "QPushButton"
#include "QComboBox"
#include "QFrame"
#include "QTextEdit"

void SearchPage::setup(MainWindow* mainWindow, QWidget* searchAddedIngredientScrollAreaContents, QWidget* searchIngredientScrollAreaContents,
                       QComboBox* searchCategoryComboBox, QComboBox* searchFavouriteComboBox, QFrame* createRatingStarFrame,
                       QWidget* searchAddedKeywordScrollAreaContents, QWidget* searchKeywordScrollAreaContents,
                       QWidget* searchFoundRecipesScrollViewContents, QTextEdit* searchRecipenameTxtEdit) {
    setupSearchIngredientScrollViews(mainWindow, searchAddedIngredientScrollAreaContents, searchIngredientScrollAreaContents);
    setupSearchKeywordScrollView(mainWindow, searchAddedKeywordScrollAreaContents, searchKeywordScrollAreaContents);

    //combo boxes
    searchCategoryComboBox->addItem("egal");
    searchCategoryComboBox->addItems(Recipe::categoryList);

    searchFavouriteComboBox->addItem("egal");
    searchFavouriteComboBox->addItem("Ja");
    searchFavouriteComboBox->addItem("Nein");

    fillFoundRecipesScrollViewContents(searchFoundRecipesScrollViewContents, searchAddedIngredientScrollAreaContents,
                                       searchAddedKeywordScrollAreaContents, searchRecipenameTxtEdit,
                                       searchCategoryComboBox, searchFavouriteComboBox);

    //star layout
    createRatingStarFrame->setLayout(MainWindow::createStarEditorFrameLayout());
}

void SearchPage::setupSearchIngredientScrollViews(MainWindow* mainWindow, QWidget* searchAddedIngredientScrollAreaContents, QWidget* searchIngredientScrollAreaContents){
    //reset scroll views if set
    deleteLayoutAndWidgetsScrollView(searchAddedIngredientScrollAreaContents->layout());
    deleteLayoutAndWidgetsScrollView(searchIngredientScrollAreaContents->layout());

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    for (auto i : rm->getIngredientList()){
        QPushButton* button = new QPushButton(i);
        button->setMinimumHeight(20);
        QObject::connect(button, SIGNAL(clicked()), mainWindow, SLOT(on_searchAddIngredient_clicked()));
        layout->addWidget(button);
    }
    searchIngredientScrollAreaContents->setLayout(layout);

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    searchAddedIngredientScrollAreaContents->setLayout(layout);
}

void SearchPage::setupSearchKeywordScrollView(MainWindow* mainWindow, QWidget* searchAddedKeywordScrollAreaContents, QWidget* searchKeywordScrollAreaContents){
    //reset scroll views if set
    deleteLayoutAndWidgetsScrollView(searchAddedKeywordScrollAreaContents->layout());
    deleteLayoutAndWidgetsScrollView(searchKeywordScrollAreaContents->layout());

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    for (auto i : rm->getKeywordList()){
        QPushButton* button = new QPushButton(i);
        button->setMinimumHeight(20);
        QObject::connect(button, SIGNAL(clicked()), mainWindow, SLOT(on_searchAddKeyword_clicked()));
        layout->addWidget(button);
    }
    searchKeywordScrollAreaContents->setLayout(layout);

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    searchAddedKeywordScrollAreaContents->setLayout(layout);
}

void SearchPage::deleteLayoutAndWidgetsScrollView(QLayout *layout){
    if (layout != nullptr){
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr){
            delete item->widget();
            delete item;
        }
        delete layout;
    }
}

void SearchPage::fillFoundRecipesScrollViewContents(QWidget* searchFoundRecipesScrollViewContents, QWidget* searchAddedIngredientScrollAreaContents,
                                                    QWidget* searchAddedKeywordScrollAreaContents, QTextEdit* searchRecipenameTxtEdit,
                                                    QComboBox* searchCategoryComboBox, QComboBox* searchFavouriteComboBox) {
    //clean up old search results
    if (searchFoundRecipesScrollViewContents->layout() != nullptr){
        deleteLayoutAndWidgetsScrollView(searchFoundRecipesScrollViewContents->layout());
    }
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    searchFoundRecipesScrollViewContents->setLayout(layout);

    //apply search parameters
    vector<QString> ingList, keywList;
    for (int i = 0; i < searchAddedIngredientScrollAreaContents->layout()->count(); i++){
        ingList.push_back(qobject_cast<QPushButton*>(searchAddedIngredientScrollAreaContents->layout()->itemAt(i)->widget())->text());
    }
    for (int i = 0; i < searchAddedKeywordScrollAreaContents->layout()->count(); i++){
        keywList.push_back(qobject_cast<QPushButton*>(searchAddedKeywordScrollAreaContents->layout()->itemAt(i)->widget())->text());
    }
    vector<Recipe> foundRecipes = rm->findRecipes(searchRecipenameTxtEdit->toPlainText(), searchCategoryComboBox->currentText(),
                                                  searchFavouriteComboBox->currentText(), ingList, keywList); //TODO add rating

    //fill with search results
    for (auto r : foundRecipes){
        searchFoundRecipesScrollViewContents->layout()->addWidget(getRecipeAsFrame(r));
    }
}
