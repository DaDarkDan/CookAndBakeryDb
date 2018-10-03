#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"
#include "QStandardPaths"
#include "QTableWidget"

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
    //combo boxes
    ui->searchCategoryComboBox->addItem("egal");
    ui->searchCategoryComboBox->addItems(Recipe::categoryList);

    ui->searchFavouriteComboBox->addItem("egal");
    ui->searchFavouriteComboBox->addItem("Ja");
    ui->searchFavouriteComboBox->addItem("Nein");

    //scroll views
    setupSearchIngredientScrollView();
    setupSearchKeywordScrollView();
}

void MainWindow::setupSearchIngredientScrollView(){
    QVBoxLayout* layout = new QVBoxLayout();
    for (auto i : rm->getIngredientList()){
        layout->addWidget(new QPushButton(i.getName()));
    }
    ui->searchIngredientScrollArea->setLayout(layout);
}

void MainWindow::setupSearchKeywordScrollView(){
    QVBoxLayout* layout = new QVBoxLayout();
    for (auto i : rm->getKeywordList()){
        layout->addWidget(new QPushButton(i));
    }
    ui->searchIngredientScrollArea->setLayout(layout);
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
    StarEditor* starEditor = new StarEditor();
    QHBoxLayout* frameLayout = new QHBoxLayout();
    frameLayout->addWidget(starEditor);
    frameLayout->setContentsMargins(0,0,0,0);
    ui->createRatingStarFrame->setLayout(frameLayout);
}

void MainWindow::setupHomePage() {

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
