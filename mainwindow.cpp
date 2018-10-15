 #include "mainwindow.h"
#include "ui_mainwindow.h"

#include "createpage.h"
#include "searchpage.h"
#include "homepage.h"
#include "recipe.h"
#include "recipemanager.h"
#include "ingredient.h"
#include "stareditor.h"
#include "clickablelabel.h"

#include "QFileDialog"
#include "QStandardPaths"
#include "QTableWidget"
#include "QDate"
#include "QDesktopServices"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    rm = new RecipeManager();

    cp = new CreatePage(this, ui->createNameTxtEdit, ui->createCategoryComboBox,
                        ui->createAddIngredientWeightTypeComboBox, ui->createAddedIngredientsScrollViewContents,
                        ui->createAddedKeywordsScrollViewContents, ui->createRatingStarFrame,
                        ui->createFavouriteCheckBox, ui->createRatingCheckBox, addedIngredientFrameList,
                        addedKeywordFrameList, ui->createNotesTxtEdit, ui->createImgInputLabel);

    ClickableLabel* cl = new ClickableLabel("", this);
    ui->searchTab->layout()->addWidget(cl);
    connect(cl, &ClickableLabel::clicked, this, &MainWindow::openFileWithStdProgramm);
    sp = new SearchPage(this, ui->searchAddedIngredientScrollAreaContents, ui->searchIngredientScrollAreaContents,
                        ui->searchCategoryComboBox, ui->searchFavouriteComboBox, ui->searchRecipenameTxtEdit,
                        ui->searchIngredientTextEdit, ui->searchKeywordScrollAreaContents, ui->searchAddedKeywordScrollAreaContents,
                        ui->searchKeywordTextEdit, ui->searchFoundRecipesScrollViewContents, ui->searchRatingStarFrame,
                        ui->searchIncludeRatingCheckBox, cl);
    hp = new HomePage(this);

    setupSearchPage();
    setupCreatePage();
    setupHomePage();
}

MainWindow::~MainWindow(){
    delete ui;
}

//search page

void MainWindow::setupSearchPage() {
    sp->setup();
}

void MainWindow::on_searchAddIngredient_clicked(){
    sp->on_searchAddIngredient_clicked(qobject_cast<QPushButton*>(sender()));
}

void MainWindow::on_searchDeleteIngredient_clicked(){
    sp->on_searchDeleteIngredient_clicked(qobject_cast<QPushButton*>(sender()));
}

void MainWindow::on_searchAddKeyword_clicked() {
    sp->on_searchAddKeyword_clicked(qobject_cast<QPushButton*>(sender()));
}

void MainWindow::on_searchDeleteKeyword_clicked() {
    sp->on_searchDeleteKeyword_clicked(qobject_cast<QPushButton*>(sender()));
}

void MainWindow::on_searchRecipenameTxtEdit_textChanged() {
    sp->on_searchRecipenameTxtEdit_textChanged();
}

void MainWindow::on_searchIngredientTextEdit_textChanged() {
    sp->on_searchIngredientTextEdit_textChanged(qobject_cast<QTextEdit*>(sender()), ui->searchIngredientScrollAreaContents->layout());
}

void MainWindow::on_searchKeywordTextEdit_textChanged() {
    sp->on_searchKeywordTextEdit_textChanged(qobject_cast<QTextEdit*>(sender()), ui->searchKeywordScrollAreaContents->layout());
}

void MainWindow::on_searchResetButton_clicked() {
    sp->on_searchResetButton_clicked();
}

void MainWindow::on_searchCategoryComboBox_currentIndexChanged(int index) {
    sp->on_searchCategoryComboBox_currentIndexChanged(index);
}

void MainWindow::on_searchFavouriteComboBox_currentIndexChanged(int index) {
    sp->on_searchFavouriteComboBox_currentIndexChanged(index);
}

RecipeManager *MainWindow::getRm() const {
    return rm;
}

//create page

void MainWindow::setupCreatePage() {
    cp->setup();
}

void MainWindow::on_createSaveBtn_clicked(){
    QString saveResult = cp->on_createSaveBtn_clicked();
    statusBar()->showMessage(saveResult);
}

void MainWindow::on_createAddIngredientBtn_clicked(){
    QString saveResult = cp->on_createAddIngredientBtn_clicked(ui->createIngredientNameTxtEdit, ui->createIngredientAmountTxtEdit, addedIngredientFrameList);
    statusBar()->showMessage(saveResult);
}

void MainWindow::on_createAddKeywordBtn_clicked() {
    QString saveResult = cp->on_createAddKeywordBtn_clicked(ui->createAddedKeywordsTxtEdit, addedKeywordFrameList);
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

void MainWindow::on_searchIncludeRatingCheckBox_stateChanged(int arg1){
    sp->on_searchIncludeRatingCheckBox_stateChanged(arg1);
}

void MainWindow::openFileWithStdProgramm(QString path){
    if (path != ""){
        QDesktopServices::openUrl(path);
    }
}

void MainWindow::on_tabWidget_currentChanged(int index){
    if (index == 0){
        sp->on_searchTabOpened();
    }
}

void MainWindow::on_createRatingCheckBox_stateChanged(int arg1){
    cp->on_createRatingCheckBox_stateChanged(arg1);
}

void MainWindow::on_createResetBtn_clicked() {
    cp->on_createResetBtn_clicked();
}
