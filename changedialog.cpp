#include "changedialog.h"
#include "ui_changedialog.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "QDateTime"
#include "QFileDialog"
#include "QStandardPaths"
#include "QCompleter"

#include "recipe.h"
#include "stareditor.h"
#include "ingredient.h"
#include "recipemanager.h"
#include "clickablelabel.h"

ChangeDialog::ChangeDialog(MainWindow* mw, Recipe* recipe, QWidget *parent) : QDialog(parent), ui(new Ui::ChangeDialog), recipe(recipe), mw(mw){
    ui->setupUi(this);
    createImgInputLabel = nullptr;
    //disable everything except bottom buttons
    ui->createAddedIngredientsFrame->setDisabled(true);
    disableList.push_back(ui->createAddedIngredientsFrame);
    ui->createAddedKeywordsFrame->setDisabled(true);
    disableList.push_back(ui->createAddedKeywordsFrame);
    ui->createIngredientFrame->setDisabled(true);
    disableList.push_back(ui->createIngredientFrame);
    ui->createKeywordsFrame->setDisabled(true);
    disableList.push_back(ui->createKeywordsFrame);
    ui->createNameCategoryFrame->setDisabled(true);
    disableList.push_back(ui->createNameCategoryFrame);
    ui->createNotesFrame->setDisabled(true);
    disableList.push_back(ui->createNotesFrame);
    ui->createTimeInputFrame->setDisabled(true);
    disableList.push_back(ui->createTimeInputFrame);
    ui->createDeleteImg->setDisabled(true);
    disableList.push_back(ui->createDeleteImg);
    ui->createUploadImgBtn->setDisabled(true);
    disableList.push_back(ui->createUploadImgBtn);
    ui->discardChangesButton->setDisabled(true);
    disableList.push_back(ui->discardChangesButton);
    setup();
}

void ChangeDialog::setup() {
    //setup recipe data
    ui->createNameTxtEdit->setText(recipe->getName());
    if (recipe->getFavourite()){
        ui->createFavouriteCheckBox->setCheckState(Qt::CheckState::Checked);
    } else {
        ui->createFavouriteCheckBox->setCheckState(Qt::CheckState::Unchecked);
    }

    ui->createCategoryComboBox->clear();
    ui->createAddIngredientWeightTypeComboBox->clear();
    ui->createCategoryComboBox->addItems(Recipe::categoryList);
    ui->createAddIngredientWeightTypeComboBox->addItems(Ingredient::weightTypeList);
    for (int i = 0; i < Recipe::categoryList.size(); i++){
        if (recipe->getCategory() == Recipe::categoryList.at(i)){
            ui->createCategoryComboBox->setCurrentIndex(i);
        }
    }
    ui->createAddIngredientWeightTypeComboBox->setCurrentIndex(0);
    //clear line/text edits
    ui->createIngredientNameLineEdit->clear();
    ui->createIngredientAmountTxtEdit->clear();
    ui->createKeywordsLineEdit->clear();
    //lineEdits
    QCompleter* completer1 = new QCompleter(mw->getRm()->getIngredientList());
    completer1->setCaseSensitivity(Qt::CaseInsensitive);
    ui->createIngredientNameLineEdit->setCompleter(completer1);

    QCompleter* completer2 = new QCompleter(mw->getRm()->getKeywordList());
    completer2->setCaseSensitivity(Qt::CaseInsensitive);
    ui->createKeywordsLineEdit->setCompleter(completer2);
    //rating
    if (ui->createRatingStarFrame->layout()){
        delete ui->createRatingStarFrame->layout()->parent()->findChild<StarEditor*>();
        delete ui->createRatingStarFrame->layout();
    }
    ui->createRatingStarFrame->setLayout(mw->createStarEditorFrameLayout());
    StarEditor* starEditor = ui->createRatingStarFrame->layout()->parent()->findChild<StarEditor*>();
    starEditor->starRating().setStarCount(-1);
    ui->createRatingStarFrame->setDisabled(true);

    //scroll views
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    auto l = ui->createAddedIngredientsScrollViewContents->layout();
    if (l != nullptr){
        QLayoutItem* item;
        while ((item = l->takeAt(0)) != nullptr){
            delete item->widget();
            delete item;
        }
        delete l;
    }
    ui->createAddedIngredientsScrollViewContents->setLayout(layout);
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    l = ui->createAddedKeywordsScrollViewContents->layout();
    if (l != nullptr){
        QLayoutItem* item;
        while ((item = l->takeAt(0)) != nullptr){
            delete item->widget();
            delete item;
        }
        delete l;
    }
    ui->createAddedKeywordsScrollViewContents->setLayout(layout);
    //ingredients
    for(auto ing : recipe->getIngredients()){
        //create contents
        QTextEdit* name = mw->createCustomTextEdit(ing.getName(), 25, 25, 100, 150);
        QTextEdit* amount = mw->createCustomTextEdit(QString::number(ing.getAmount()), 25, 25, 50, 100);
        QComboBox* weightType = new QComboBox();
        weightType->addItems(Ingredient::weightTypeList);
        for (int i = 0; i < Ingredient::weightTypeList.size(); i++){
            if (ing.getWeightType() == Ingredient::weightTypeList.at(i)){
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

        ui->createAddedIngredientsScrollViewContents->layout()->addWidget(frame);
        addedIngredientFrameList.push_back(frame);
    }
    //keywords
    for (auto keyword : recipe->getKeywords()){
        QTextEdit* txtEdit = mw->createCustomTextEdit(keyword, 25, 25, 100, 100);
        QPushButton* deleteButton = mw->createCustomDeleteButton();
        QFrame* frame = mw->createCustomFrame();
        txtEdit->setParent(frame);
        deleteButton->setParent(frame);

        //set up layout
        QHBoxLayout* frameLayout = new QHBoxLayout(frame);
        frameLayout->setMargin(2);
        frameLayout->addWidget(txtEdit);
        frameLayout->addWidget(deleteButton);

        ui->createAddedKeywordsScrollViewContents->layout()->addWidget(frame);
        addedKeywordFrameList.push_back(frame);
    }
    //time
    ui->createTimeInputTextEdit->setAlignment(Qt::AlignRight);
    if (recipe->getProcessTime() > 0.01f){
        ui->createTimeInputTextEdit->setText(QString::number(recipe->getProcessTime()));
    }
    //notes
    ui->createNotesTxtEdit->setText(recipe->getNotes());
    //images
    currentPixmapList.clear();
    ui->createImgInputFrame->layout()->setAlignment(Qt::AlignHCenter);
    if (!createImgInputLabel){
        createImgInputLabel = new ClickableLabel(ui->createImgInputFrame);
        createImgInputLabel->setScaledContents(true);
        createImgInputLabel->setMinimumSize(400, 550);
        createImgInputLabel->setMaximumSize(400, 550);
        qobject_cast<QVBoxLayout*>(ui->createImgInputFrame->layout())->insertWidget(1,createImgInputLabel);
    }
    createImgInputLabel->clear();
    if (recipe->getPixmapList().size() > 0){
        createImgInputLabel->setPixmap(recipe->getPixmapList().at(0).getPixmap());
        createImgInputLabel->setFullPath(recipe->getPixmapList().at(0).getPath());
        ui->createImgTitleLabel->setText("Bild 1 von " + QString::number(recipe->getPixmapList().size()));

        for (auto pm : recipe->getPixmapList()){
            currentPixmapList.push_back(pm);
        }
    } else {
        ui->createImgTitleLabel->setText("Bild: ");
    }
    currentRecipePixmapIndex = 0;
}

ChangeDialog::~ChangeDialog(){
    delete ui;
}

void ChangeDialog::on_createChangeBtn_clicked(){
    if (ui->createChangeBtn->text() == "Rezept ändern"){
        for (auto widget : disableList){
            widget->setEnabled(true);
        }
        ui->createChangeBtn->setText("Änderungen speichern");
    } else {
        for (auto widget : disableList){
            widget->setDisabled(true);
        }
        ui->createChangeBtn->setText("Rezept ändern");
        saveChanges();
        setup();
    }
}

void ChangeDialog::on_createImageLeft_clicked(){
    if (currentPixmapList.size() <= 1) return;
    if (currentRecipePixmapIndex == 0){
        currentRecipePixmapIndex = currentPixmapList.size()-1;
    } else {
        currentRecipePixmapIndex--;
    }
    PathPixmap ppm = currentPixmapList.at(currentRecipePixmapIndex);
    createImgInputLabel->setPixmap(ppm.getPixmap());
    createImgInputLabel->setFullPath(ppm.getPath());
    ui->createImgTitleLabel->setText("Bild " + QString::number(currentRecipePixmapIndex+1) + " von " + QString::number(currentPixmapList.size()));
}

void ChangeDialog::on_createImgRight_clicked(){
    if (currentPixmapList.size() <= 1) return;
    if (currentRecipePixmapIndex == currentPixmapList.size()-1){
        currentRecipePixmapIndex = 0;
    } else {
        currentRecipePixmapIndex++;
    }
    PathPixmap ppm = currentPixmapList.at(currentRecipePixmapIndex);
    createImgInputLabel->setPixmap(ppm.getPixmap());
    createImgInputLabel->setFullPath(ppm.getPath());    ui->createImgTitleLabel->setText("Bild " + QString::number(currentRecipePixmapIndex+1) + " von " + QString::number(currentPixmapList.size()));
}

void ChangeDialog::on_createRatingCheckBox_stateChanged(int arg1){
    StarEditor* starEditor = ui->createRatingStarFrame->layout()->parent()->findChild<StarEditor*>();
    if (arg1 == 0){
        ui->createRatingStarFrame->setEnabled(false);
        starEditor->setEditable(false);
    } else if (arg1 == 2){
        ui->createRatingStarFrame->setEnabled(true);
        starEditor->setEditable(true);
    }
}

void ChangeDialog::on_createAddIngredientBtn_clicked(){
    //check if amount is decimal number
    bool isFloat;
    QString germanInput = ui->createIngredientAmountTxtEdit->toPlainText().replace(",", ".");
    germanInput.toFloat(&isFloat);

    if (!isFloat){
        return;
    }

    if (ui->createIngredientNameLineEdit->text() != ""){
        //create contents
        QTextEdit* name = mw->createCustomTextEdit(ui->createIngredientNameLineEdit->text(), 25, 25, 100, 150);
        ui->createIngredientNameLineEdit->clear();
        QTextEdit* amount = mw->createCustomTextEdit(ui->createIngredientAmountTxtEdit->toPlainText(), 25, 25, 50, 100);
        ui->createIngredientAmountTxtEdit->clear();
        QComboBox* weightType = new QComboBox();
        weightType->addItems(Ingredient::weightTypeList);
        for (int i = 0; i < Ingredient::weightTypeList.size(); i++){
            if (ui->createAddIngredientWeightTypeComboBox->currentText() == Ingredient::weightTypeList.at(i)){
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

        ui->createAddedIngredientsScrollViewContents->layout()->addWidget(frame);
        addedIngredientFrameList.push_back(frame);
    }
}

void ChangeDialog::on_createAddKeywordBtn_clicked(){

}

void ChangeDialog::on_discardChangesButton_clicked(){
    setup();
}

void ChangeDialog::saveChanges(){
    Recipe temp;
    temp.setName(ui->createNameTxtEdit->toPlainText());
    if (ui->createNameTxtEdit->toPlainText() == ""){
        ui->createNameTxtEdit->setStyleSheet("background: red");
        return;
    }

    Recipe* rec = new Recipe();
    //id
    rec->setId(recipe->getId());
    //name
    rec->setName(ui->createNameTxtEdit->toPlainText());
    //date
    rec->setCreationDate(QDateTime::currentDateTime().toString("dd/MM/yyyy H:mm'Uhr'"));
    //category
    rec->setCategory(ui->createCategoryComboBox->currentText());
    ui->createCategoryComboBox->setCurrentIndex(0);
    //favourite
    rec->setFavourite(ui->createFavouriteCheckBox->isChecked());
    ui->createFavouriteCheckBox->setCheckState(Qt::Unchecked);
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
    rec->setIngredients(addedIngredientList);
    //keywords
    for (auto frame : addedKeywordFrameList){
        auto children = frame->children();
        if (children.size() == 3) {
            rec->addKeyword(qobject_cast<QTextEdit*>(children.at(0))->toPlainText());
        }
    }
    //rating
    if (ui->createRatingCheckBox->isChecked()){
        rec->setRating(ui->createRatingStarFrame->layout()->parent()->findChild<StarEditor*>()->starRating().getMyStarCount());
    } else {
        rec->setRating(0);
    }
    ui->createRatingCheckBox->setCheckState(Qt::CheckState::Unchecked);
    //notes
    rec->setNotes(ui->createNotesTxtEdit->toPlainText());
    //images
    if (createImgInputLabel->pixmap()){
        QList<PathPixmap> saveList;
        for (int i = 0; i < currentPixmapList.size(); i++){
            PathPixmap ppm(mw->getRm()->getIoManager()->getDirectoryPath() + "/" + rec->getId() + "_image" + QString::number(i) + ".png", currentPixmapList.at(i).getPath());
            saveList.push_back(ppm);
        }
        rec->setPixmapList(saveList);
    }
    for (auto img : recipe->getImgFileDeleteList()){
        rec->addToBeDeletedImgPath(img);
    }
    recipe = rec;
    mw->getRm()->saveRecipe(recipe, true);
}

void ChangeDialog::on_createUploadImgBtn_clicked(){
    QString fileName = QFileDialog::getOpenFileName(mw, QObject::tr("Open Image"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), QObject::tr("Formate(*.png *.jpg *.bmp)"));
    if (fileName == "") return;
    QImage image(fileName);

    createImgInputLabel->setScaledContents(true);
    createImgInputLabel->setPixmap(QPixmap::fromImage(image));
    PathPixmap ppm(fileName, QPixmap::fromImage(image));
    currentPixmapList.push_back(ppm);
    if (currentPixmapList.size() > 1){
        currentRecipePixmapIndex = currentPixmapList.size()-1;
        createImgInputLabel->setPixmap(currentPixmapList.at(currentRecipePixmapIndex).getPixmap());
        createImgInputLabel->setFullPath(currentPixmapList.at(currentRecipePixmapIndex).getPath());
    }
    ui->createImgTitleLabel->setText("Bild " + QString::number(currentRecipePixmapIndex+1) + " von " + QString::number(currentPixmapList.size()));
}

void ChangeDialog::on_createDeleteImg_clicked(){
    if (currentPixmapList.empty()) return;

    QString test = createImgInputLabel->getFullPath();
    recipe->addToBeDeletedImgPath(createImgInputLabel->getFullPath());

    currentPixmapList.removeAt(currentRecipePixmapIndex);
    createImgInputLabel->clear();
    if (!currentPixmapList.empty() && currentRecipePixmapIndex > 0){
        currentRecipePixmapIndex--;
        createImgInputLabel->setPixmap(currentPixmapList.at(currentRecipePixmapIndex).getPixmap());
        createImgInputLabel->setFullPath(currentPixmapList.at(currentRecipePixmapIndex).getPath());
    } else if (!currentPixmapList.empty() && currentRecipePixmapIndex == 0){
        createImgInputLabel->setPixmap(currentPixmapList.at(currentRecipePixmapIndex).getPixmap());
        createImgInputLabel->setFullPath(currentPixmapList.at(currentRecipePixmapIndex).getPath());
    }
    if (currentPixmapList.size() != 0){
        ui->createImgTitleLabel->setText("Bild " + QString::number(currentRecipePixmapIndex+1) + " von " + QString::number(currentPixmapList.size()));
    } else {
        ui->createImgTitleLabel->setText("Bild: ");
    }
}
