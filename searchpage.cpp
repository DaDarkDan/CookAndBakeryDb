#include "searchpage.h"
#include "mainwindow.h"
#include "recipemanager.h"
#include "ingredient.h"
#include "stareditor.h"
#include "recipesearchresultframe.h"
#include "clickablelabel.h"
#include "parameterbutton.h"
#include "createpage.h"
#include "recipeframe.h"
#include "changedialog.h"

#include "QLayoutItem"
#include "QLayout"
#include "QPushButton"
#include "QComboBox"
#include "QFrame"
#include "QTextEdit"
#include "QLabel"
#include "QCheckBox"
#include "QMessageBox"
#include "QSignalMapper"

#include "QDebug"

SearchPage::SearchPage(MainWindow* mw, QWidget* searchAddedIngredientScrollAreaContents, QWidget* searchIngredientScrollAreaContents,
                       QComboBox* searchCategoryComboBox, QComboBox* searchFavouriteComboBox, QTextEdit* searchRecipenameTxtEdit,
                       QTextEdit* searchIngredientTextEdit, QWidget* searchKeywordScrollAreaContents, QWidget* searchAddedKeywordScrollAreaContents,
                       QTextEdit* searchKeywordTextEdit, QWidget* searchFoundRecipesScrollViewContents, QFrame* searchRatingStarFrame,
                       QCheckBox* searchIncludeRatingCheckBox, ClickableLabel* searchResultImgLabel, QComboBox* searchSortComboBox,
                       QLabel* searchIngredientIconLabel, QLabel* searchKeywordIconLabel, QFrame* searchShownImageFrame,
                       QLabel* searchImgTitleLabel){
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
    this->searchIncludeRatingCheckBox = searchIncludeRatingCheckBox;
    this->searchResultImgLabel = searchResultImgLabel;
    this->searchSortComboBox = searchSortComboBox;
    this->searchIngredientIconLabel = searchIngredientIconLabel;
    this->searchKeywordIconLabel = searchKeywordIconLabel;
    this->searchShownImageFrame = searchShownImageFrame;
    this->searchImgTitleLabel = searchImgTitleLabel;

    currentRecipePixmapIndex = 0;
}

void SearchPage::setup() {
    setupSearchIngredientScrollViews();
    setupSearchKeywordScrollView();

    //icons
    searchIngredientIconLabel->setPixmap(QPixmap(":/img/ingredient.png"));
    searchIngredientIconLabel->setScaledContents(true);
    searchIngredientIconLabel->setAlignment(Qt::AlignRight);
    searchKeywordIconLabel->setPixmap(QPixmap(":/img/idea.png"));
    searchKeywordIconLabel->setScaledContents(true);

    //combo boxes
    searchCategoryComboBox->addItem("egal");
    searchCategoryComboBox->addItems(Recipe::categoryList);

    searchFavouriteComboBox->addItem("egal");
    searchFavouriteComboBox->addItem("Ja");
    searchFavouriteComboBox->addItem("Nein");

    for (auto str : sortings){
        searchSortComboBox->addItem(str);
    }

    //star layout
    searchRatingStarFrame->setLayout(mw->createStarEditorFrameLayout(false));
    starEditor = searchRatingStarFrame->layout()->parent()->findChild<StarEditor*>();
    connect(starEditor, &StarEditor::editingFinished, this, &SearchPage::ratingEditingFinished);
    searchRatingStarFrame->setDisabled(true);

    //result image
    searchResultImgLabel->setScaledContents(true);
    searchResultImgLabel->setMinimumSize(400, 550);
    searchResultImgLabel->setMaximumSize(400, 550);
    updateFoundRecipes();
}

void SearchPage::on_searchAddIngredient_clicked(QPushButton* button) {
    button->disconnect();
    searchIngredientScrollAreaContents->layout()->removeWidget(button);

    connect(button, SIGNAL(clicked()), mw, SLOT(on_searchDeleteIngredient_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(searchAddedIngredientScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    //update search results
    updateFoundRecipes();
}

void SearchPage::on_searchDeleteIngredient_clicked(QPushButton* button) {
    button->disconnect();
    searchAddedIngredientScrollAreaContents->layout()->removeWidget(button);

    connect(button, SIGNAL(clicked()), mw, SLOT(on_searchAddIngredient_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(searchIngredientScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    on_searchIngredientKeyword_textChanged(searchIngredientTextEdit, searchIngredientScrollAreaContents->layout());
    //update search results
    updateFoundRecipes();
}

void SearchPage::on_searchAddKeyword_clicked(QPushButton* button) {
    button->disconnect();
    searchKeywordScrollAreaContents->layout()->removeWidget(button);

    connect(button, SIGNAL(clicked()), mw, SLOT(on_searchDeleteKeyword_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(searchAddedKeywordScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    //update search results
    updateFoundRecipes();
}

void SearchPage::on_searchDeleteKeyword_clicked(QPushButton* button) {
    button->disconnect();
    searchAddedKeywordScrollAreaContents->layout()->removeWidget(button);

    connect(button, SIGNAL(clicked()), mw, SLOT(on_searchAddKeyword_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(searchKeywordScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    on_searchIngredientKeyword_textChanged(searchKeywordTextEdit, searchKeywordScrollAreaContents->layout());
    //update search results
    updateFoundRecipes();
}

void SearchPage::on_searchRecipenameTxtEdit_textChanged() {
    //update search results
    updateFoundRecipes();
}

void SearchPage::on_searchIngredientTextEdit_textChanged(QTextEdit* txtEdit, QLayout* layout) {
    on_searchIngredientKeyword_textChanged(txtEdit, layout);
}

void SearchPage::on_searchKeywordTextEdit_textChanged(QTextEdit* txtEdit, QLayout* layout) {
    on_searchIngredientKeyword_textChanged(txtEdit, layout);
}

void SearchPage::on_searchCategoryComboBox_currentIndexChanged(int /*index*/){
    //update search results
    updateFoundRecipes();
}

void SearchPage::on_searchFavouriteComboBox_currentIndexChanged(int /*index*/){
    //update search results
    updateFoundRecipes();
}

void SearchPage::on_searchResetButton_clicked() {
    searchRecipenameTxtEdit->clear();
    searchCategoryComboBox->setCurrentIndex(0);
    searchFavouriteComboBox->setCurrentIndex(0);
    searchSortComboBox->setCurrentIndex(0);
    searchIngredientTextEdit->clear();
    searchKeywordTextEdit->clear();
    searchIncludeRatingCheckBox->setCheckState(Qt::CheckState::Unchecked);
    searchResultImgLabel->clear();
    setupSearchIngredientScrollViews();
    setupSearchKeywordScrollView();

    //update search results
    updateFoundRecipes();
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
        connect(button, SIGNAL(clicked()), mw, SLOT(on_searchAddIngredient_clicked()));
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
        connect(button, SIGNAL(clicked()), mw, SLOT(on_searchAddKeyword_clicked()));
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

void SearchPage::updateFoundRecipes() {
    //clean up old search results
    if (searchFoundRecipesScrollViewContents->layout() != nullptr){
        deleteLayoutAndWidgetsScrollView(searchFoundRecipesScrollViewContents->layout());
    }
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    searchFoundRecipesScrollViewContents->setLayout(layout);

    //apply search parameters
    QList<QString> ingList, keywList;
    for (int i = 0; i < searchAddedIngredientScrollAreaContents->layout()->count(); i++){
        ingList.push_back(qobject_cast<QPushButton*>(searchAddedIngredientScrollAreaContents->layout()->itemAt(i)->widget())->text());
    }
    for (int i = 0; i < searchAddedKeywordScrollAreaContents->layout()->count(); i++){
        keywList.push_back(qobject_cast<QPushButton*>(searchAddedKeywordScrollAreaContents->layout()->itemAt(i)->widget())->text());
    }
    QList<Recipe*> foundRecipes;
    if (searchIncludeRatingCheckBox->isChecked() && starEditor){
        foundRecipes = mw->getRm()->findRecipes(searchRecipenameTxtEdit->toPlainText(), searchCategoryComboBox->currentText(),
                                                      searchFavouriteComboBox->currentText(), ingList, keywList, starEditor->starRating().getMyStarCount());
    } else {
        foundRecipes = mw->getRm()->findRecipes(searchRecipenameTxtEdit->toPlainText(), searchCategoryComboBox->currentText(),
                                                      searchFavouriteComboBox->currentText(), ingList, keywList);
    }

    //fill with search results
    for (unsigned int i = 0; i < foundRecipes.size(); i++){
        searchFoundRecipesScrollViewContents->layout()->addWidget(getRecipeAsFrame(foundRecipes.at(i), i+1));
    }
}

void SearchPage::on_searchSortComboBox_currentIndexChanged(int index){
    mw->getRm()->setCurrentSorting(index);
    updateFoundRecipes();
}

QFrame *SearchPage::getRecipeAsFrame(Recipe* recipe, int index) {
    RecipeSearchResultFrame* rsrFrame = new RecipeSearchResultFrame(mw, recipe, mw->createStarEditorFrameLayout(true), index, mw);
    connect(rsrFrame, &RecipeSearchResultFrame::on_mousePressed, this, &SearchPage::displaySearchResultImage);
    connect(rsrFrame->getDeleteButton(), &ParameterButton::clicked, this, &SearchPage::openDeleteMessageBox);
    return rsrFrame->getFrame();
}

void SearchPage::openDeleteMessageBox(Recipe* recipe){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Wollen Sie das Rezept '" + recipe->getName() + "' wirklich löschen?");
    QPushButton* applyBtn = msgBox.addButton(QMessageBox::Apply);
    applyBtn->setText("Löschen");
    applyBtn->setStyleSheet("color: red");
    QPushButton* discardBtn = msgBox.addButton(QMessageBox::Discard);
    discardBtn->setText("Abbrechen");
    msgBox.setDefaultButton(discardBtn);
    msgBox.exec();

    if (msgBox.clickedButton() == applyBtn){
        deleteRecipe(recipe);
        updateFoundRecipes();
    } else if(msgBox.clickedButton() == discardBtn){
        msgBox.close();
    }
}


void SearchPage::deleteRecipe(Recipe *recipe){
    mw->getRm()->deleteRecipe(recipe);
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

void SearchPage::on_searchIncludeRatingCheckBox_stateChanged(int arg1){
    if (arg1 == 0){
        starEditor->setEditable(false);
        searchRatingStarFrame->setEnabled(false);
    } else if (arg1 == 2){
        starEditor->setEditable(true);
        searchRatingStarFrame->setEnabled(true);
    }
    //update search results
    updateFoundRecipes();
}

void SearchPage::displaySearchResultImage(Recipe* recipe){
    if (recipe){
        searchImgTitleLabel->setText("Bild " + QString::number(currentRecipePixmapIndex+1) + " von " + QString::number(recipe->getPixmapList().size()));
        currentActiveRecipe = recipe;
        searchResultImgLabel->setFullPath(recipe->getPixmapList().at(0).getPath());
        searchResultImgLabel->setPixmap(recipe->getPixmapList().at(0).getPixmap());
    } else {
        searchResultImgLabel->setFullPath(currentActiveRecipe->getPixmapList().at(0).getPath());
        searchResultImgLabel->setPixmap(currentActiveRecipe->getPixmapList().at(0).getPixmap());
    }
}

void SearchPage::ratingEditingFinished(){
    updateFoundRecipes();
}

void SearchPage::on_searchTabOpened(){
    setupSearchIngredientScrollViews();
    setupSearchKeywordScrollView();
    updateFoundRecipes();
}

void SearchPage::on_searchImageLeft_clicked(){
    if (!currentActiveRecipe) return;
    if (currentRecipePixmapIndex == 0){
        currentRecipePixmapIndex = currentActiveRecipe->getPixmapList().size()-1;
    } else {
        currentRecipePixmapIndex--;
    }
    searchResultImgLabel->setPixmap(currentActiveRecipe->getPixmapList().at(currentRecipePixmapIndex).getPixmap());
    searchImgTitleLabel->setText("Bild " + QString::number(currentRecipePixmapIndex+1) + " von " + QString::number(currentActiveRecipe->getPixmapList().size()));
}

void SearchPage::on_searchImageRight_clicked(){
    if (!currentActiveRecipe) return;
    if (currentRecipePixmapIndex == currentActiveRecipe->getPixmapList().size()-1){
        currentRecipePixmapIndex = 0;
    } else {
        currentRecipePixmapIndex++;
    }
    searchResultImgLabel->setPixmap(currentActiveRecipe->getPixmapList().at(currentRecipePixmapIndex).getPixmap());
    searchImgTitleLabel->setText("Bild " + QString::number(currentRecipePixmapIndex+1) + " von " + QString::number(currentActiveRecipe->getPixmapList().size()));
}

void SearchPage::setFavourite(QString /*string*/, Recipe* recipe){
    ClickableLabel* heart = qobject_cast<ClickableLabel*>(sender());
    if (recipe){
        if (recipe->getFavourite()){
            recipe->setFavourite(false);
            QPixmap pm(":/img/heart_off.png");
            heart->setPixmap(pm);
        } else {
            recipe->setFavourite(true);
            QPixmap pm(":/img/heart_on.png");
            heart->setPixmap(pm);
        }
        mw->getRm()->saveRecipe(recipe, true);
    }
}

void SearchPage::openChangeDialog(QString /*string*/, Recipe *recipe){
    mw->setDisabled(true);
    ChangeDialog dialog(mw, recipe);
    dialog.setWindowTitle(recipe->getName() + " (ID " + recipe->getId() + ")");
    dialog.exec();
    mw->setEnabled(true);
    updateFoundRecipes();
}
