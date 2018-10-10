 #include "mainwindow.h"
#include "ui_mainwindow.h"

#include "createpage.h"
#include "searchpage.h"
#include "homepage.h"

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
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    rm = new RecipeManager();

    cp = new CreatePage(rm);
    sp = new SearchPage(rm);
    hp = new HomePage();

    setupSearchPage();
    setupCreatePage();
    setupHomePage();
}

MainWindow::~MainWindow(){
    delete ui;
}

//search page

void MainWindow::setupSearchPage() {
    sp->setup(this, ui->searchAddedIngredientScrollAreaContents, ui->searchIngredientScrollAreaContents,
              ui->searchCategoryComboBox, ui->searchFavouriteComboBox, ui->createRatingStarFrame,
              ui->searchAddedKeywordScrollAreaContents, ui->searchKeywordScrollAreaContents,
              ui->searchFoundRecipesScrollViewContents, ui->searchRecipenameTxtEdit);
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

void MainWindow::on_searchCategoryComboBox_currentIndexChanged(int index) {
    //update search results
    fillFoundRecipesScrollViewContents();
}

void MainWindow::on_searchFavouriteComboBox_currentIndexChanged(int index) {


    //update search results
    fillFoundRecipesScrollViewContents();
}

//create page

void MainWindow::setupCreatePage() {
    cp->setup(ui->createCategoryComboBox, ui->createAddIngredientWeightTypeComboBox, ui->createAddedIngredientsScrollViewContents,
              ui->createAddedKeywordsScrollViewContents, ui->searchRatingStarFrame);
}

void MainWindow::on_createSaveBtn_clicked(){
    QString saveResult = cp->on_createSaveBtn_clicked(ui->createNameTxtEdit, ui->createCategoryComboBox, addedIngredientFrameList, addedKeywordFrameList, ui->createRatingStarFrame,
                                 ui->createNotesTxtEdit, ui->createImgInputLabel, ui->createFavouriteCheckBox);
    statusBar()->showMessage(saveResult);
}

void MainWindow::on_createAddIngredientBtn_clicked(){
    QString saveResult = cp->on_createAddIngredientBtn_clicked(ui->createIngredientNameTxtEdit, ui->createIngredientAmountTxtEdit, ui->createAddIngredientWeightTypeComboBox,
                                                               ui->createAddedIngredientsScrollViewContents, addedIngredientFrameList);
    statusBar()->showMessage(saveResult);
}

void MainWindow::on_createAddKeywordBtn_clicked() {
    QString saveResult = cp->on_createAddKeywordBtn_clicked(ui->createAddedKeywordsTxtEdit, ui->createAddedKeywordsScrollViewContents, addedKeywordFrameList);
    statusBar()->showMessage(saveResult);
}

void MainWindow::on_addedFrameDeleteButton_clicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    cp->on_addedFrameDeleteButton_clicked(button, addedIngredientFrameList, addedKeywordFrameList);
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


//home page

void MainWindow::setupHomePage() {

}

void MainWindow::on_pushButton_clicked() {
    rm->getIoManager()->setDirectoryPath(QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}


//helper functions

QPushButton* MainWindow::createCustomDeleteButton() {
    QPushButton* deleteButton = new QPushButton("X");
    deleteButton->setStyleSheet("font: bold;color: red");
    deleteButton->setMaximumHeight(15);
    deleteButton->setMinimumHeight(15);
    deleteButton->setMaximumWidth(30);
    deleteButton->setMinimumWidth(30);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(on_addedFrameDeleteButton_clicked()));
    return deleteButton;
}

QFrame* MainWindow::createCustomFrame(){
    QFrame* frame = new QFrame();
    frame->setMaximumHeight(40);
    QSizePolicy* sp = new QSizePolicy();
    sp->setVerticalPolicy(QSizePolicy::Maximum);
    frame->setSizePolicy(*sp);
    frame->setStyleSheet(" .QFrame {background-color : red}");
    return frame;
}

QTextEdit* MainWindow::createCustomTextEdit(const QString &value, int minH, int maxH, int minW, int maxW){
    QTextEdit* textEdit = new QTextEdit(value);
    textEdit->setMinimumHeight(minH);
    textEdit->setMaximumHeight(maxH);
    textEdit->setMinimumWidth(minW);
    textEdit->setMaximumWidth(maxW);
    return textEdit;
}

QHBoxLayout* MainWindow::createStarEditorFrameLayout() {
    StarEditor* starEditor = new StarEditor();
    QHBoxLayout* frameLayout = new QHBoxLayout();
    frameLayout->addWidget(starEditor);
    frameLayout->setContentsMargins(0,0,0,0);
    return frameLayout;
}
