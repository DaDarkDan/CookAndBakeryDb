#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"
#include "QStandardPaths"
#include "QTableWidget"
#include "QDate"

#include "recipe.h"
#include "recipemanager.h"
#include "ingredient.h"
#include "stareditor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rm = new RecipeManager();

    setupSearchPage();
    setupCreatePage();
    setupHomePage();
}

void MainWindow::setupSearchPage() {
    setupSearchIngredientScrollViews();
    setupSearchKeywordScrollView();
    //combo boxes
    ui->searchCategoryComboBox->addItem("egal");
    ui->searchCategoryComboBox->addItems(Recipe::categoryList);

    ui->searchFavouriteComboBox->addItem("egal");
    ui->searchFavouriteComboBox->addItem("Ja");
    ui->searchFavouriteComboBox->addItem("Nein");

    fillFoundRecipesScrollViewContents();

    //star layout
    ui->createRatingStarFrame->setLayout(createStarEditorFrameLayout());
}


void MainWindow::setupCreatePage() {
    //combo boxes
    ui->createCategoryComboBox->addItems(Recipe::categoryList);
    ui->createAddIngredientWeightTypeComboBox->addItems(Ingredient::weightTypeList);

    //scroll views
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    ui->createAddedIngredientsScrollViewContents->setLayout(layout);
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    ui->createAddedKeywordsScrollViewContents->setLayout(layout);

    //star layout
    ui->searchRatingStarFrame->setLayout(createStarEditorFrameLayout());
}

QHBoxLayout* MainWindow::createStarEditorFrameLayout() const{
    StarEditor* starEditor = new StarEditor();
    QHBoxLayout* frameLayout = new QHBoxLayout();
    frameLayout->addWidget(starEditor);
    frameLayout->setContentsMargins(0,0,0,0);
    return frameLayout;
}

void MainWindow::setupHomePage() {

}

void MainWindow::fillFoundRecipesScrollViewContents(){
    //clean up old search results
    if (ui->searchFoundRecipesScrollViewContents->layout() != nullptr){
        deleteLayoutAndWidgetsScrollView(ui->searchFoundRecipesScrollViewContents->layout());
    }
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    ui->searchFoundRecipesScrollViewContents->setLayout(layout);

    //apply search parameters
    vector<QString> ingList, keywList;
    for (int i = 0; i < ui->searchAddedIngredientScrollAreaContents->layout()->count(); i++){
        ingList.push_back(qobject_cast<QPushButton*>(ui->searchAddedIngredientScrollAreaContents->layout()->itemAt(i)->widget())->text());
    }
    for (int i = 0; i < ui->searchAddedKeywordScrollAreaContents->layout()->count(); i++){
        keywList.push_back(qobject_cast<QPushButton*>(ui->searchAddedKeywordScrollAreaContents->layout()->itemAt(i)->widget())->text());
    }
    vector<Recipe> foundRecipes = rm->findRecipes(ui->searchRecipenameTxtEdit->toPlainText(), ui->searchCategoryComboBox->currentText(),
                                                  ui->searchFavouriteComboBox->currentText(), ingList, keywList); //TODO add rating

    //fill with search results
    for (auto r : foundRecipes){
        ui->searchFoundRecipesScrollViewContents->layout()->addWidget(getRecipeAsFrame(r));
    }
}

QFrame* MainWindow::getRecipeAsFrame(const Recipe& recipe) {
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
    starFrame->setLayout(createStarEditorFrameLayout());

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

void MainWindow::setupSearchIngredientScrollViews(){
    //reset scroll views if set
    deleteLayoutAndWidgetsScrollView(ui->searchAddedIngredientScrollAreaContents->layout());
    deleteLayoutAndWidgetsScrollView(ui->searchIngredientScrollAreaContents->layout());

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    for (auto i : rm->getIngredientList()){
        QPushButton* button = new QPushButton(i);
        button->setMinimumHeight(20);
        connect(button, SIGNAL(clicked()), this, SLOT(on_searchAddIngredient_clicked()));
        layout->addWidget(button);
    }
    ui->searchIngredientScrollAreaContents->setLayout(layout);

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    ui->searchAddedIngredientScrollAreaContents->setLayout(layout);
}

void MainWindow::setupSearchKeywordScrollView(){
    //reset scroll views if set
    deleteLayoutAndWidgetsScrollView(ui->searchAddedKeywordScrollAreaContents->layout());
    deleteLayoutAndWidgetsScrollView(ui->searchKeywordScrollAreaContents->layout());

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    for (auto i : rm->getKeywordList()){
        QPushButton* button = new QPushButton(i);
        button->setMinimumHeight(20);
        connect(button, SIGNAL(clicked()), this, SLOT(on_searchAddKeyword_clicked()));
        layout->addWidget(button);
    }
    ui->searchKeywordScrollAreaContents->setLayout(layout);

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    ui->searchAddedKeywordScrollAreaContents->setLayout(layout);
}

void MainWindow::on_searchAddIngredient_clicked(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->disconnect();
    ui->searchIngredientScrollAreaContents->layout()->removeWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(on_searchDeleteIngredient_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->searchAddedIngredientScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    //update search results
    fillFoundRecipesScrollViewContents();
}

void MainWindow::on_searchDeleteIngredient_clicked(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->disconnect();
    ui->searchAddedIngredientScrollAreaContents->layout()->removeWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(on_searchAddIngredient_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->searchIngredientScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    on_searchIngredientKeyword_textChanged(ui->searchIngredientTextEdit, ui->searchIngredientScrollAreaContents->layout());
    //update search results
    fillFoundRecipesScrollViewContents();
}

void MainWindow::on_searchAddKeyword_clicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->disconnect();
    ui->searchKeywordScrollAreaContents->layout()->removeWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(on_searchDeleteKeyword_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->searchAddedKeywordScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    //update search results
    fillFoundRecipesScrollViewContents();
}

void MainWindow::on_searchDeleteKeyword_clicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->disconnect();
    ui->searchAddedKeywordScrollAreaContents->layout()->removeWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(on_searchAddKeyword_clicked()));
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->searchKeywordScrollAreaContents->layout());
    addButtonToScrollAreaContentsLayout(layout, button);
    on_searchIngredientKeyword_textChanged(ui->searchKeywordTextEdit, ui->searchKeywordScrollAreaContents->layout());
    //update search results
    fillFoundRecipesScrollViewContents();
}

void MainWindow::addButtonToScrollAreaContentsLayout(QVBoxLayout* layout, QPushButton* button){
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

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_createSaveBtn_clicked(){
    if (ui->createNameTxtEdit->toPlainText() == ""){
        //TODO show error
        return;
    }

    Recipe* recipe = new Recipe();
    //name
    recipe->setName(ui->createNameTxtEdit->toPlainText());
    ui->createNameTxtEdit->clear();
    //date
    recipe->setCreationDate(QDate::currentDate().toString());
    //category
    recipe->setCategory(ui->createCategoryComboBox->currentText());
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
    StarEditor* starEditor = ui->createRatingStarFrame->layout()->parent()->findChild<StarEditor*>();
    recipe->setRating(starEditor->starRating().getMyStarCount());
    //notes
    recipe->setNotes(ui->createNotesTxtEdit->toPlainText());
    ui->createNotesTxtEdit->clear();
    //image
    if (ui->createImgInputLabel->pixmap()){
        recipe->setPixmap(*ui->createImgInputLabel->pixmap());
        ui->createImgInputLabel->clear();
    }
    //favourite
    recipe->setFavourite(ui->createFavouriteCheckBox->isChecked());
    ui->createFavouriteCheckBox->setCheckState(Qt::Unchecked);

    if (rm->saveRecipe(*recipe)){
        statusBar()->showMessage("Rezept <" + recipe->getName() + "> wurde erfolgreich gespeichert");
    } else {
        //TODO show error message
    }
}

void MainWindow::on_pushButton_clicked() {
    rm->getIoManager()->setDirectoryPath(QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_createAddIngredientBtn_clicked(){
    QTextEdit* nameTxtEdit = ui->createIngredientNameTxtEdit;
    QTextEdit* amountTxtEdit = ui->createIngredientAmountTxtEdit;
    QComboBox* weightTypeComboBox = ui->createAddIngredientWeightTypeComboBox;

    //check if amount is decimal number
    bool isFloat;
    amountTxtEdit->toPlainText().toFloat(&isFloat);

    if (!isFloat){
        //TODO show error
        return;
    }

    if (nameTxtEdit->toPlainText() != "" && amountTxtEdit->toPlainText() != ""){
        //create contents
        QTextEdit* name = createTextEdit(nameTxtEdit->toPlainText(), 25, 25, 100, 150);
        nameTxtEdit->clear();
        QTextEdit* amount = createTextEdit(amountTxtEdit->toPlainText(), 25, 25, 50, 100);
        amountTxtEdit->clear();
        QComboBox* weightType = new QComboBox();
        weightType->addItems(Ingredient::weightTypeList);
        weightType->setCurrentText(weightTypeComboBox->currentText());
        weightType->setMaximumHeight(25);
        weightType->setMinimumHeight(25);
        weightType->setMaximumWidth(70);
        weightType->setMinimumWidth(70);
        QPushButton* deleteButton = createDeleteButton();
        QFrame* frame = createFrame();
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

void MainWindow::on_createAddKeywordBtn_clicked() {
    QTextEdit* keywordTxtEdit = ui->createAddedKeywordsTxtEdit;

    if (keywordTxtEdit->toPlainText() != ""){
        //create contents
        QTextEdit* txtEdit = createTextEdit(keywordTxtEdit->toPlainText(), 25, 25, 100, 100);
        keywordTxtEdit->clear();
        QPushButton* deleteButton = createDeleteButton();
        QFrame* frame = createFrame();
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
}

void MainWindow::onAddedFrameDeleteButton_clicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());

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

QFrame* MainWindow::createFrame() const{
    QFrame* frame = new QFrame();
    frame->setMaximumHeight(40);
    QSizePolicy* sp = new QSizePolicy();
    sp->setVerticalPolicy(QSizePolicy::Maximum);
    frame->setSizePolicy(*sp);
    frame->setStyleSheet(" .QFrame {background-color : red}");
    return frame;
}

QTextEdit* MainWindow::createTextEdit(const QString &value, int minH, int maxH, int minW, int maxW) const{
    QTextEdit* textEdit = new QTextEdit(value);
    textEdit->setMinimumHeight(minH);
    textEdit->setMaximumHeight(maxH);
    textEdit->setMinimumWidth(minW);
    textEdit->setMaximumWidth(maxW);
    return textEdit;
}

QPushButton* MainWindow::createDeleteButton() const{
    QPushButton* deleteButton = new QPushButton("X");
    deleteButton->setStyleSheet("font: bold;color: red");
    deleteButton->setMaximumHeight(15);
    deleteButton->setMinimumHeight(15);
    deleteButton->setMaximumWidth(30);
    deleteButton->setMinimumWidth(30);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(onAddedFrameDeleteButton_clicked()));
    return deleteButton;
}


void MainWindow::on_uploadImgBtn_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), tr("Formate(*.png *.jpg *.bmp *.pdf)"));
    QImage image(fileName);

    ui->createImgInputLabel->setScaledContents(true);

    if (fileName.endsWith(".pdf") || fileName.endsWith(".PDF")){

    } else {
        ui->createImgInputLabel->setPixmap(QPixmap::fromImage(image));
    }
}

void MainWindow::on_searchRecipenameTxtEdit_textChanged() {
    //update search results
    fillFoundRecipesScrollViewContents();
}

void MainWindow::on_searchIngredientTextEdit_textChanged() {
    on_searchIngredientKeyword_textChanged(sender(), ui->searchIngredientScrollAreaContents->layout());
}

void MainWindow::on_searchKeywordTextEdit_textChanged() {
    on_searchIngredientKeyword_textChanged(sender(), ui->searchKeywordScrollAreaContents->layout());
}

void MainWindow::on_searchIngredientKeyword_textChanged(QObject* sender, QLayout* layout) {
    QTextEdit* txtEdit = qobject_cast<QTextEdit*>(sender);
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

void MainWindow::on_searchResetButton_clicked() {
    ui->searchRecipenameTxtEdit->setText("");
    ui->searchCategoryComboBox->setCurrentIndex(0);
    ui->searchFavouriteComboBox->setCurrentIndex(0);
    ui->searchIngredientTextEdit->setText("");
    ui->searchKeywordTextEdit->setText("");
    setupSearchIngredientScrollViews();
    setupSearchKeywordScrollView();

    //update search results
    fillFoundRecipesScrollViewContents();
}

void MainWindow::deleteLayoutAndWidgetsScrollView(QLayout* layout) {
    if (layout != nullptr){
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr){
            delete item->widget();
            delete item;
        }
        delete layout;
    }
}

void MainWindow::on_searchCategoryComboBox_currentIndexChanged(int index) {
    //update search results
    fillFoundRecipesScrollViewContents();
}

void MainWindow::on_searchFavouriteComboBox_currentIndexChanged(int index) {
    //update search results
    fillFoundRecipesScrollViewContents();
}
