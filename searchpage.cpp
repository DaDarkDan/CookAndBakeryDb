#include "searchpage.h"
#include "mainwindow.h"
#include "recipemanager.h"
#include "ingredient.h"

#include "QLayoutItem"
#include "QLayout"
#include "QWidget"
#include "QPushButton"
#include "QComboBox"
#include "QFrame"
#include "QTextEdit"
#include "QLabel"

SearchPage::SearchPage(MainWindow* mw, QWidget* searchAddedIngredientScrollAreaContents, QWidget* searchIngredientScrollAreaContents,
                       QComboBox* searchCategoryComboBox, QComboBox* searchFavouriteComboBox, QTextEdit* searchRecipenameTxtEdit,
                       QTextEdit* searchIngredientTextEdit, QWidget* searchKeywordScrollAreaContents, QWidget* searchAddedKeywordScrollAreaContents,
                       QTextEdit* searchKeywordTextEdit, QWidget* searchFoundRecipesScrollViewContents, QFrame* searchRatingStarFrame){
    this->mw = mw;
    this->searchAddedIngredientScrollAreaContents = searchAddedIngredientScrollAreaContents;
    this->searchIngredientScrollAreaContents = searchIngredientScrollAreaContents;
    this->searchCategoryComboBox = searchCategoryComboBox;
    this->searchFavouriteComboBox = searchFavouriteComboBox;
    this->searchRecipenameTxtEdit = searchRecipenameTxtEdit;
    this->searchIngredientTextEdit = searchIngredientTextEdit;
    this->searchKeywordScrollAreaContents = searchKeywordScrollAreaContents;
    this->searchAddedKeywordScrollAreaContents = searchAddedKeywordScrollAreaContents;
    this->searchKeywordTextEdit = searchKeywordTextEdit;
    this->searchRatingStarFrame = searchRatingStarFrame;
    this->searchFoundRecipesScrollViewContents = searchFoundRecipesScrollViewContents;
}

void SearchPage::setup() {
    setupSearchIngredientScrollViews();
    setupSearchKeywordScrollView();


    //combo boxes
    searchCategoryComboBox->addItem("egal");
    searchCategoryComboBox->addItems(Recipe::categoryList);

    searchFavouriteComboBox->addItem("egal");
    searchFavouriteComboBox->addItem("Ja");
    searchFavouriteComboBox->addItem("Nein");

    fillFoundRecipesScrollViewContents();

    //star layout
    searchRatingStarFrame->setLayout(mw->createStarEditorFrameLayout());
}

void SearchPage::on_searchAddIngredient_clicked(QPushButton* button) {
    button->disconnect();
    searchIngredientScrollAreaContents->layout()->removeWidget(button);

    QObject::connect(button, SIGNAL(clicked()), mw, SLOT(on_searchDeleteIngredient_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(searchAddedIngredientScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    //update search results
    fillFoundRecipesScrollViewContents();
}

void SearchPage::on_searchDeleteIngredient_clicked(QPushButton* button) {
    button->disconnect();
    searchAddedIngredientScrollAreaContents->layout()->removeWidget(button);

    QObject::connect(button, SIGNAL(clicked()), mw, SLOT(on_searchAddIngredient_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(searchIngredientScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    on_searchIngredientKeyword_textChanged(searchIngredientTextEdit, searchIngredientScrollAreaContents->layout());
    //update search results
    fillFoundRecipesScrollViewContents();
}

void SearchPage::on_searchAddKeyword_clicked(QPushButton* button) {
    button->disconnect();
    searchKeywordScrollAreaContents->layout()->removeWidget(button);

    QObject::connect(button, SIGNAL(clicked()), mw, SLOT(on_searchDeleteKeyword_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(searchAddedKeywordScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    //update search results
    fillFoundRecipesScrollViewContents();
}

void SearchPage::on_searchDeleteKeyword_clicked(QPushButton* button) {
    button->disconnect();
    searchAddedKeywordScrollAreaContents->layout()->removeWidget(button);

    QObject::connect(button, SIGNAL(clicked()), mw, SLOT(on_searchAddKeyword_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(searchKeywordScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    on_searchIngredientKeyword_textChanged(searchKeywordTextEdit, searchKeywordScrollAreaContents->layout());
    //update search results
    fillFoundRecipesScrollViewContents();
}

void SearchPage::on_searchRecipenameTxtEdit_textChanged() {
    //update search results
    fillFoundRecipesScrollViewContents();
}

void SearchPage::on_searchIngredientTextEdit_textChanged(QTextEdit* txtEdit, QLayout* layout) {
    on_searchIngredientKeyword_textChanged(txtEdit, layout);
}

void SearchPage::on_searchKeywordTextEdit_textChanged(QTextEdit* txtEdit, QLayout* layout) {
    on_searchIngredientKeyword_textChanged(txtEdit, layout);
}

void SearchPage::on_searchCategoryComboBox_currentIndexChanged(int index){
    //update search results
    fillFoundRecipesScrollViewContents();
}

void SearchPage::on_searchFavouriteComboBox_currentIndexChanged(int index){
    //update search results
    fillFoundRecipesScrollViewContents();
}

void SearchPage::on_searchResetButton_clicked() {
    searchRecipenameTxtEdit->setText("");
    searchCategoryComboBox->setCurrentIndex(0);
    searchFavouriteComboBox->setCurrentIndex(0);
    searchIngredientTextEdit->setText("");
    searchKeywordTextEdit->setText("");
    setupSearchIngredientScrollViews();
    setupSearchKeywordScrollView();

    //update search results
    fillFoundRecipesScrollViewContents();
}

void SearchPage::setupSearchIngredientScrollViews(){
    //reset scroll views if set
    deleteLayoutAndWidgetsScrollView(searchAddedIngredientScrollAreaContents->layout());
    deleteLayoutAndWidgetsScrollView(searchIngredientScrollAreaContents->layout());

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    for (auto i : mw->getRm()->getIngredientList()){
        QPushButton* button = new QPushButton(i);
        button->setMinimumHeight(20);
        QObject::connect(button, SIGNAL(clicked()), mw, SLOT(on_searchAddIngredient_clicked()));
        layout->addWidget(button);
    }
    searchIngredientScrollAreaContents->setLayout(layout);

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    searchAddedIngredientScrollAreaContents->setLayout(layout);
}

void SearchPage::setupSearchKeywordScrollView(){
    //reset scroll views if set
    deleteLayoutAndWidgetsScrollView(searchAddedKeywordScrollAreaContents->layout());
    deleteLayoutAndWidgetsScrollView(searchKeywordScrollAreaContents->layout());

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    for (auto i : mw->getRm()->getKeywordList()){
        QPushButton* button = new QPushButton(i);
        button->setMinimumHeight(20);
        QObject::connect(button, SIGNAL(clicked()), mw, SLOT(on_searchAddKeyword_clicked()));
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

void SearchPage::fillFoundRecipesScrollViewContents() {
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
    vector<Recipe> foundRecipes = mw->getRm()->findRecipes(searchRecipenameTxtEdit->toPlainText(), searchCategoryComboBox->currentText(),
                                                  searchFavouriteComboBox->currentText(), ingList, keywList); //TODO add rating

    //fill with search results
    for (auto r : foundRecipes){
        searchFoundRecipesScrollViewContents->layout()->addWidget(getRecipeAsFrame(r));
    }
}

QFrame *SearchPage::getRecipeAsFrame(const Recipe &recipe) {
    QHBoxLayout* horLayout = new QHBoxLayout();
    QGridLayout* gridLayout = new QGridLayout();
    //TODO setup layout

    QLabel* name = new QLabel(recipe.getName());
    name->setMaximumSize(200, 20);
    QLabel* date = new QLabel(recipe.getCreationDate());
    date->setMaximumSize(150, 20);
    QLabel* ing = new QLabel(QString::number(recipe.getNumberOfIngredients()) + " Zutaten");
    ing->setMaximumSize(150, 20);
    QFrame* starFrame = new QFrame();
    starFrame->setMaximumSize(205, 25);
    QLabel* image = new QLabel();
    image->setMaximumSize(100, 100);
    image->setPixmap(recipe.getPixmap());
    image->setScaledContents(true);
    starFrame->setLayout(mw->createStarEditorFrameLayout());

    //zeile spalte
    gridLayout->addWidget(name,0,0);
    gridLayout->addWidget(date,1,0);
    gridLayout->addWidget(ing,2,0);
    gridLayout->addWidget(starFrame,3,0);

    horLayout->addLayout(gridLayout);
    horLayout->addWidget(image);

    QFrame* frame = new QFrame();
    frame->setFrameStyle(QFrame::Raised | QFrame::Box);
    frame->setLayout(horLayout);

    return frame;
}

void SearchPage::addButtonToScrollAreaContentsLayout(QVBoxLayout *layout, QPushButton *button) {
    if (layout->count() == 0){
        layout->addWidget(button);
        return;
    }
    for (int i = 0; i < layout->count(); i ++){
        auto currentBtn = qobject_cast<QPushButton*>(layout->itemAt(i)->widget())->text();
        if (button->text() < currentBtn){
            layout->insertWidget(i, button);
            break;
        } else if (button->text() > currentBtn && i == layout->count()-1) {
            layout->insertWidget(i+1, button);
        }
    }
}

void SearchPage::on_searchIngredientKeyword_textChanged(QTextEdit* txtEdit, QLayout *layout){
    for (int i = 0; i < layout->count(); i++){
        QPushButton* currentBtn = qobject_cast<QPushButton*>(layout->itemAt(i)->widget());
        if (currentBtn->text().toUpper().contains(txtEdit->toPlainText().toUpper())){
            currentBtn->setEnabled(true);
            currentBtn->setVisible(true);
        } else {
            currentBtn->setEnabled(false);
            currentBtn->setVisible(false);
        }
    }
}
