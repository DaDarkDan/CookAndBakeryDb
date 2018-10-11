#include "createpage.h"
#include "recipe.h"
#include "recipemanager.h"
#include "ingredient.h"
#include "stareditor.h"
#include "mainwindow.h"

#include "QTextEdit"
#include "QDate"
#include "QComboBox"
#include "QFrame"
#include "QLabel"
#include "QCheckBox"
#include "QStatusBar"
#include "QLayout"
#include "QString"
#include "QPushButton"
#include "QCheckBox"

CreatePage::CreatePage(MainWindow* mw, QComboBox* createCategoryComboBox, QComboBox* createAddIngredientWeightTypeComboBox,
                           QWidget* createAddedIngredientsScrollViewContents, QWidget* createAddedKeywordsScrollViewContents,
                       QFrame* createRatingStarFrame, QCheckBox* createFavouriteCheckBox){
    this->mw = mw;
    this->createCategoryComboBox = createCategoryComboBox;
    this->createAddIngredientWeightTypeComboBox = createAddIngredientWeightTypeComboBox;
    this->createAddedIngredientsScrollViewContents = createAddedIngredientsScrollViewContents;
    this->createAddedKeywordsScrollViewContents = createAddedKeywordsScrollViewContents;
    this->createRatingStarFrame = createRatingStarFrame;
    this->createFavouriteCheckBox = createFavouriteCheckBox;
}

void CreatePage::setup(){
    //favourite checkbox
    createFavouriteCheckBox->setStyleSheet("margin-bottom: 20px");

    //combo boxes
    createCategoryComboBox->addItems(Recipe::categoryList);
    createAddIngredientWeightTypeComboBox->addItems(Ingredient::weightTypeList);

    //scroll views
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    createAddedIngredientsScrollViewContents->setLayout(layout);
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    createAddedKeywordsScrollViewContents->setLayout(layout);

    //star layout
    createRatingStarFrame->setLayout(mw->createStarEditorFrameLayout());
}

QString CreatePage::on_createSaveBtn_clicked(QTextEdit* createNameTxtEdit, vector<QWidget*> addedIngredientFrameList,
                                          vector<QWidget*> addedKeywordFrameList, QTextEdit* createNotesTxtEdit,
                                          QLabel* createImgInputLabel, QCheckBox* createFavouriteCheckBox) {
    if (createNameTxtEdit->toPlainText() == ""){
        return "Bitte gib einen Rezeptnamen an!";
    }

    Recipe* recipe = new Recipe();
    //name
    recipe->setName(createNameTxtEdit->toPlainText());
    createNameTxtEdit->clear();
    //date
    recipe->setCreationDate(QDate::currentDate().toString());
    //category
    recipe->setCategory(createCategoryComboBox->currentText());
    //ingredients
    vector<Ingredient> addedIngredientList;
    for (auto frame : addedIngredientFrameList){
        auto children = frame->children();
        if (children.size() == 5) {
            Ingredient ing;
            ing.setName(qobject_cast<QTextEdit*>(children.at(0))->toPlainText());
            ing.setAmount(qobject_cast<QTextEdit*>(children.at(1))->toPlainText().toFloat());
            ing.setWeightType(qobject_cast<QComboBox*>(children.at(2))->currentText());
            addedIngredientList.push_back(ing);
        }
    }
    recipe->setIngredients(addedIngredientList);
    for (auto i : addedIngredientFrameList){
        while(QWidget* w = i->findChild<QWidget*>()){
            delete w;
        }
        delete i;
    }
    addedIngredientFrameList.clear();
    //keywords
    for (auto frame : addedKeywordFrameList){
        auto children = frame->children();
        if (children.size() == 3) {
            recipe->addKeyword(qobject_cast<QTextEdit*>(children.at(0))->toPlainText());
        }
    }
    for (auto i : addedKeywordFrameList){
        while(QWidget* w = i->findChild<QWidget*>()){
            delete w;
        }
        delete i;
    }
    addedKeywordFrameList.clear();
    //rating
    StarEditor* starEditor = createRatingStarFrame->layout()->parent()->findChild<StarEditor*>();
    recipe->setRating(starEditor->starRating().getMyStarCount());
    //notes
    recipe->setNotes(createNotesTxtEdit->toPlainText());
    createNotesTxtEdit->clear();
    //image
    if (createImgInputLabel->pixmap()){
        recipe->setPixmap(*createImgInputLabel->pixmap());
        createImgInputLabel->clear();
    }
    //favourite
    recipe->setFavourite(createFavouriteCheckBox->isChecked());
    createFavouriteCheckBox->setCheckState(Qt::Unchecked);

    if (mw->getRm()->saveRecipe(*recipe)){
        return "Rezept '" + recipe->getName() + " wurde erfolgreich gespeichert!";
    }
    return "Rezept konnte nicht gespeichert werden. Gibt es dieses schon?";
}

QString CreatePage::on_createAddIngredientBtn_clicked(QTextEdit* createIngredientNameTxtEdit, QTextEdit* createIngredientAmountTxtEdit, vector<QWidget*> addedIngredientFrameList) {
    //check if amount is decimal number
    bool isFloat;
    createIngredientAmountTxtEdit->toPlainText().toFloat(&isFloat);

    if (!isFloat){
        return "Die eingegebene Menge muss eine Zahl sein!";
    }

    if (createIngredientNameTxtEdit->toPlainText() != "" && createIngredientAmountTxtEdit->toPlainText() != ""){
        //create contents
        QTextEdit* name = mw->createCustomTextEdit(createIngredientNameTxtEdit->toPlainText(), 25, 25, 100, 150);
        createIngredientNameTxtEdit->clear();
        QTextEdit* amount = mw->createCustomTextEdit(createIngredientAmountTxtEdit->toPlainText(), 25, 25, 50, 100);
        createIngredientAmountTxtEdit->clear();
        QComboBox* weightType = new QComboBox();
        weightType->addItems(Ingredient::weightTypeList);
        weightType->setCurrentText(createAddIngredientWeightTypeComboBox->currentText());
        weightType->setMaximumHeight(25);
        weightType->setMinimumHeight(25);
        weightType->setMaximumWidth(70);
        weightType->setMinimumWidth(70);
        QPushButton* deleteButton = mw->createCustomDeleteButton();
        QFrame* frame = mw->createCustomFrame();
        name->setParent(frame);
        amount->setParent(frame);
        weightType->setParent(frame);
        deleteButton->setParent(frame);

        //set up layout
        QHBoxLayout* frameLayout = new QHBoxLayout(frame);
        frameLayout->setMargin(2);
        frameLayout->addWidget(name);
        frameLayout->addWidget(amount);
        frameLayout->addWidget(weightType);
        frameLayout->addWidget(deleteButton);

        createAddedIngredientsScrollViewContents->layout()->addWidget(frame);
        addedIngredientFrameList.push_back(frame);

        return "Zutat '" + name->toPlainText() + " wurde hinzugefügt!";
    }
    return "Zutat konnte aufgrund eines Fehlers nicht hinzugefügt werden!";
}

QString CreatePage::on_createAddKeywordBtn_clicked(QTextEdit* createAddedKeywordsTxtEdit, vector<QWidget*> addedKeywordFrameList) {

    if (createAddedKeywordsTxtEdit->toPlainText() != ""){
        //create contents
        QTextEdit* txtEdit = mw->createCustomTextEdit(createAddedKeywordsTxtEdit->toPlainText(), 25, 25, 100, 100);
        createAddedKeywordsTxtEdit->clear();
        QPushButton* deleteButton = mw->createCustomDeleteButton();
        QFrame* frame = mw->createCustomFrame();
        txtEdit->setParent(frame);
        deleteButton->setParent(frame);

        //set up layout
        QHBoxLayout* frameLayout = new QHBoxLayout(frame);
        frameLayout->setMargin(2);
        frameLayout->addWidget(txtEdit);
        frameLayout->addWidget(deleteButton);

        createAddedKeywordsScrollViewContents->layout()->addWidget(frame);
        addedKeywordFrameList.push_back(frame);

        return "Schlagwort '" + txtEdit->toPlainText() + " wurde hinzugefügt!";
    }
    return "Schlagwort konnte aufgrund eines Fehlers nicht hinzugefügt werden!";

}

void CreatePage::on_addedFrameDeleteButton_clicked(QPushButton* button, vector<QWidget*> addedIngredientFrameList, vector<QWidget*> addedKeywordFrameList) {
    QFrame* parentFrame = qobject_cast<QFrame*>(button->parent());

    for (unsigned int i = 0; i < addedIngredientFrameList.size();i++){
        if (addedIngredientFrameList.at(i) == parentFrame){
            addedIngredientFrameList.erase(addedIngredientFrameList.begin()+i);
            break;
        }
    }
    for (unsigned int i = 0; i < addedKeywordFrameList.size();i++){
        if (addedKeywordFrameList.at(i) == parentFrame){
            addedKeywordFrameList.erase(addedKeywordFrameList.begin()+i);
            break;
        }
    }
    for (auto child : parentFrame->children()){
        delete child;
    }
    delete parentFrame;
}

void CreatePage::on_uploadImgBtn_clicked() {

}
