#include "createpage.h"
#include "recipe.h"
#include "recipemanager.h"
#include "ingredient.h"
#include "stareditor.h"
#include "mainwindow.h"

#include "QTextEdit"
#include "QDateTime"
#include "QComboBox"
#include "QFrame"
#include "QLabel"
#include "QCheckBox"
#include "QStatusBar"
#include "QLayout"
#include "QString"
#include "QPushButton"
#include "QCheckBox"
#include "QFileDialog"
#include "QStandardPaths"
#include "QMessageBox"
#include "QLineEdit"
#include "QCompleter"

CreatePage::CreatePage(MainWindow* mw, QTextEdit* createNameTxtEdit, QComboBox* createCategoryComboBox,
                       QComboBox* createAddIngredientWeightTypeComboBox, QWidget* createAddedIngredientsScrollViewContents,
                       QWidget* createAddedKeywordsScrollViewContents, QFrame* createRatingStarFrame,
                       QCheckBox* createFavouriteCheckBox, QCheckBox* createRatingCheckBox,
                       QList<QWidget*> addedIngredientFrameList, QList<QWidget*> addedKeywordFrameList,
                       QTextEdit* createNotesTxtEdit, QLabel* createImgInputLabel,
                       QLineEdit* createIngredientNameLineEdit, QTextEdit* createIngredientAmountTxtEdit,
                       QTextEdit* createAddedKeywordsTxtEdit, QLabel* createIngredientIconLabel,
                       QLabel* createKeywordIconLabel, QLabel* createImgTitleLabel){
    this->mw = mw;
    this->createNameTxtEdit = createNameTxtEdit;
    this->createCategoryComboBox = createCategoryComboBox;
    this->createAddIngredientWeightTypeComboBox = createAddIngredientWeightTypeComboBox;
    this->createAddedIngredientsScrollViewContents = createAddedIngredientsScrollViewContents;
    this->createAddedKeywordsScrollViewContents = createAddedKeywordsScrollViewContents;
    this->createRatingStarFrame = createRatingStarFrame;
    this->createFavouriteCheckBox = createFavouriteCheckBox;
    this->createRatingCheckBox = createRatingCheckBox;
    this->addedIngredientFrameList = addedIngredientFrameList;
    this->addedKeywordFrameList = addedKeywordFrameList;
    this->createNotesTxtEdit = createNotesTxtEdit;
    this->createImgInputLabel = createImgInputLabel;
    this->createIngredientNameLineEdit = createIngredientNameLineEdit;
    this->createIngredientAmountTxtEdit = createIngredientAmountTxtEdit;
    this->createAddedKeywordsTxtEdit = createAddedKeywordsTxtEdit;
    this-> createIngredientIconLabel = createIngredientIconLabel;
    this->createKeywordIconLabel = createKeywordIconLabel;
    this->createImgTitleLabel = createImgTitleLabel;

    currentPixmapIndex = 0;
}

void CreatePage::setup(){
    //icons
    createIngredientIconLabel->setPixmap(QPixmap(":/img/ingredient.png"));
    createIngredientIconLabel->setScaledContents(true);
    createIngredientIconLabel->setAlignment(Qt::AlignRight);
    createKeywordIconLabel->setPixmap(QPixmap(":/img/idea.png"));
    createKeywordIconLabel->setScaledContents(true);
    //textEdits
    createNameTxtEdit->setTabChangesFocus(true);
    if (mw->getRm()->getIoManager()->getDirectoryPath() == ""){
        createNameTxtEdit->setText("Sie benötigen einen Speicherpfad!");
        createNameTxtEdit->setStyleSheet("background: rgb(202, 205, 209)");
        createNameTxtEdit->setDisabled(true);
    }
    QCompleter* completer = new QCompleter(mw->getRm()->getIngredientList());
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    createIngredientNameLineEdit->setCompleter(completer);

    createIngredientAmountTxtEdit->setTabChangesFocus(true);
    createAddedKeywordsTxtEdit->setTabChangesFocus(true);
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
    starEditor = createRatingStarFrame->layout()->parent()->findChild<StarEditor*>();
    createRatingStarFrame->setDisabled(true);
}

QString CreatePage::on_createSaveBtn_clicked() {
    Recipe temp;
    temp.setName(createNameTxtEdit->toPlainText());
    if (createNameTxtEdit->toPlainText() == ""){
        createNameTxtEdit->setStyleSheet("background: red");
        return "Bitte gib einen Rezeptnamen an!";
    } else if (!mw->getRm()->isNewRecipe(temp)){
        createNameTxtEdit->setStyleSheet("background: red");
        return "Dieser Rezeptname ist schon vergeben!";
    } else if (createNameTxtEdit->toPlainText() == "Sie benötigen einen Speicherpfad!"){
        return "Bitte geben Sie einen Speicherpfad unter 'Meine Datenbank' an!";
    }

    Recipe* recipe = new Recipe();
    //name
    recipe->setName(createNameTxtEdit->toPlainText());
    createNameTxtEdit->clear();
    //date
    recipe->setCreationDate(QDateTime::currentDateTime().toString("dd/MM/yyyy H:mm'Uhr'"));
    //category
    recipe->setCategory(createCategoryComboBox->currentText());
    createCategoryComboBox->setCurrentIndex(0);
    //favourite
    recipe->setFavourite(createFavouriteCheckBox->isChecked());
    createFavouriteCheckBox->setCheckState(Qt::Unchecked);
    //ingredients
    vector<Ingredient> addedIngredientList;
    for (auto frame : addedIngredientFrameList){
        auto children = frame->children();
        if (children.size() == 5) {
            Ingredient ing;
            ing.setName(qobject_cast<QTextEdit*>(children.at(0))->toPlainText());
            ing.setAmount(qobject_cast<QTextEdit*>(children.at(1))->toPlainText().replace(",", ".").toFloat());
            ing.setWeightType(qobject_cast<QComboBox*>(children.at(2))->currentText());
            addedIngredientList.push_back(ing);
        }
    }
    recipe->setIngredients(addedIngredientList);
    addedIngredientFrameList.clear();
    auto layout = createAddedIngredientsScrollViewContents->layout();
    QLayoutItem* item;
    while((item = layout->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }
    //keywords
    for (auto frame : addedKeywordFrameList){
        auto children = frame->children();
        if (children.size() == 3) {
            recipe->addKeyword(qobject_cast<QTextEdit*>(children.at(0))->toPlainText());
        }
    }
    addedKeywordFrameList.clear();
    layout = createAddedKeywordsScrollViewContents->layout();
    while((item = layout->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }
    //rating
    if (createRatingCheckBox->isChecked()){
        recipe->setRating(starEditor->starRating().getMyStarCount());
    } else {
        recipe->setRating(0);
    }
    createRatingCheckBox->setCheckState(Qt::CheckState::Unchecked);
    //notes
    recipe->setNotes(createNotesTxtEdit->toPlainText());
    createNotesTxtEdit->clear();
    //images
    if (createImgInputLabel->pixmap()){
        QList<PathPixmap> saveList;
        for (int i = 0; i < currentPixmapList.size(); i++){
            PathPixmap ppm(mw->getRm()->getIoManager()->getDirectoryPath() + "/" + recipe->getId() + "_image" + QString::number(i) + ".png", currentPixmapList.at(i));
            saveList.push_back(ppm);
        }
        recipe->setPixmapList(saveList);
        createImgInputLabel->clear();
    }

    QMessageBox box;
    box.setText("Rezept '" + recipe->getName() + "' wurde erfolgreich gespeichert!");
    box.exec();
    if (mw->getRm()->saveRecipe(recipe)){
        return "Rezept '" + recipe->getName() + "' wurde erfolgreich gespeichert!";
    }
    return "Rezept konnte nicht gespeichert werden.";
}

QString CreatePage::on_createAddIngredientBtn_clicked() {
    //check if amount is decimal number
    bool isFloat;
    QString germanInput = createIngredientAmountTxtEdit->toPlainText().replace(",", ".");
    germanInput.toFloat(&isFloat);

    if (!isFloat){
        return "Die eingegebene Menge muss eine Zahl sein!";
    }

    if (createIngredientNameLineEdit->text() != ""){
        //create contents
        QTextEdit* name = mw->createCustomTextEdit(createIngredientNameLineEdit->text(), 25, 25, 100, 150);
        createIngredientNameLineEdit->clear();
        QTextEdit* amount = mw->createCustomTextEdit(createIngredientAmountTxtEdit->toPlainText(), 25, 25, 50, 100);
        createIngredientAmountTxtEdit->clear();
        QComboBox* weightType = new QComboBox();
        weightType->addItems(Ingredient::weightTypeList);
        for (int i = 0; i < Ingredient::weightTypeList.size(); i++){
            if (createAddIngredientWeightTypeComboBox->currentText() == Ingredient::weightTypeList.at(i)){
                weightType->setCurrentIndex(i);
                break;
            }
        }
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

        return "Zutat '" + name->toPlainText() + "' wurde hinzugefügt!";
    }
    return "Zutat konnte aufgrund eines Fehlers nicht hinzugefügt werden!";
}

QString CreatePage::on_createAddKeywordBtn_clicked() {

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

void CreatePage::on_addedFrameDeleteButton_clicked(QPushButton* button) {
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
    QString fileName = QFileDialog::getOpenFileName(mw, QObject::tr("Open Image"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), QObject::tr("Formate(*.png *.jpg *.bmp)"));
    QImage image(fileName);

    createImgInputLabel->setScaledContents(true);
    createImgInputLabel->setPixmap(QPixmap::fromImage(image));
    currentPixmapList.push_back(QPixmap::fromImage(image));
    if (currentPixmapList.size() > 1){
        currentPixmapIndex = currentPixmapList.size()-1;
        createImgInputLabel->setPixmap(currentPixmapList.at(currentPixmapIndex));
    }
    createImgTitleLabel->setText("Bild " + QString::number(currentPixmapIndex+1) + " von " + QString::number(currentPixmapList.size()));
}

void CreatePage::on_createRatingCheckBox_stateChanged(int arg1){
    if (arg1 == 0){
        createRatingStarFrame->setEnabled(false);
        starEditor->setEditable(false);
    } else if (arg1 == 2){
        createRatingStarFrame->setEnabled(true);
        starEditor->setEditable(true);
    }
}

void CreatePage::on_createResetBtn_clicked() {
    createNameTxtEdit->clear();
    createCategoryComboBox->setCurrentIndex(0);
    createFavouriteCheckBox->setCheckState(Qt::Unchecked);
    createRatingCheckBox->setCheckState(Qt::CheckState::Unchecked);

    createNotesTxtEdit->clear();

    addedIngredientFrameList.clear();
    auto layout = createAddedIngredientsScrollViewContents->layout();
    QLayoutItem* item;
    while((item = layout->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }

    addedKeywordFrameList.clear();
    layout = createAddedKeywordsScrollViewContents->layout();
    while((item = layout->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }

    createImgInputLabel->clear();
}

void CreatePage::on_createNameTxtEdit_textChanged() {
    createNameTxtEdit->setStyleSheet("background: white");
}

QTextEdit *CreatePage::getCreateNameTxtEdit() const{
    return createNameTxtEdit;
}

void CreatePage::on_createDeleteImg_clicked(){
    if (currentPixmapList.empty()) return;

    currentPixmapList.removeAt(currentPixmapIndex);
    createImgInputLabel->clear();
    if (!currentPixmapList.empty() && currentPixmapIndex > 0){
        currentPixmapIndex--;
        createImgInputLabel->setPixmap(currentPixmapList.at(currentPixmapIndex));
    } else if (!currentPixmapList.empty() && currentPixmapIndex == 0){
        createImgInputLabel->setPixmap(currentPixmapList.at(currentPixmapIndex));
    }
    if (currentPixmapList.size() != 0){
        createImgTitleLabel->setText("Bild " + QString::number(currentPixmapIndex+1) + " von " + QString::number(currentPixmapList.size()));
    } else {
        createImgTitleLabel->setText("Bild: ");
    }
}

void CreatePage::on_createImageLeft_clicked(){
    if (currentPixmapList.size() <= 1) return;
    if (currentPixmapIndex == 0){
        currentPixmapIndex = currentPixmapList.size()-1;
    } else {
        currentPixmapIndex--;
    }
    createImgInputLabel->setPixmap(currentPixmapList.at(currentPixmapIndex));
    createImgTitleLabel->setText("Bild " + QString::number(currentPixmapIndex+1) + " von " + QString::number(currentPixmapList.size()));
}

void CreatePage::on_createImgRight_clicked(){
    if (currentPixmapList.size() <= 1) return;
    if (currentPixmapIndex == currentPixmapList.size()-1){
        currentPixmapIndex = 0;
    } else {
        currentPixmapIndex++;
    }
    createImgInputLabel->setPixmap(currentPixmapList.at(currentPixmapIndex));
    createImgTitleLabel->setText("Bild " + QString::number(currentPixmapIndex+1) + " von " + QString::number(currentPixmapList.size()));
}
