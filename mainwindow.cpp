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

#include "QTableWidget"
#include "QDate"
#include "QDesktopServices"
#include "QSettings"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("DaDarkSoftware");
    QCoreApplication::setApplicationName("MomsBakeryDb");

    loadSettings();

    cp = new CreatePage(this, ui->createNameTxtEdit, ui->createCategoryComboBox,
                        ui->createAddIngredientWeightTypeComboBox, ui->createAddedIngredientsScrollViewContents,
                        ui->createAddedKeywordsScrollViewContents, ui->createRatingStarFrame,
                        ui->createFavouriteCheckBox, ui->createRatingCheckBox, addedIngredientFrameList,
                        addedKeywordFrameList, ui->createNotesTxtEdit, ui->createImgInputLabel,
                        ui->createIngredientNameTxtEdit, ui->createIngredientAmountTxtEdit,
                        ui->createAddedKeywordsTxtEdit, ui->createIngredientIconLabel,
                        ui->createKeywordIconLabel);

    ClickableLabel* cl = new ClickableLabel(this);
    ui->searchTab->layout()->addWidget(cl);
    connect(cl, &ClickableLabel::clicked, this, &MainWindow::openFileWithStdProgramm);
    sp = new SearchPage(this, ui->searchAddedIngredientScrollAreaContents, ui->searchIngredientScrollAreaContents,
                        ui->searchCategoryComboBox, ui->searchFavouriteComboBox, ui->searchRecipenameTxtEdit,
                        ui->searchIngredientTextEdit, ui->searchKeywordScrollAreaContents, ui->searchAddedKeywordScrollAreaContents,
                        ui->searchKeywordTextEdit, ui->searchFoundRecipesScrollViewContents, ui->searchRatingStarFrame,
                        ui->searchIncludeRatingCheckBox, cl, ui->searchSortComboBox, ui->searchIngredientIconLabel,
                        ui->searchKeywordIconLabel);
    hp = new HomePage(this, ui->homeDirectoryLineEdit);

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

void MainWindow::on_searchIncludeRatingCheckBox_stateChanged(int arg1){
    sp->on_searchIncludeRatingCheckBox_stateChanged(arg1);
}

//create page

void MainWindow::setupCreatePage() {
    cp->setup();
}

void MainWindow::on_createSaveBtn_clicked(){
    QString saveResult = cp->on_createSaveBtn_clicked();
    statusBar()->showMessage(saveResult, 3000);
}

void MainWindow::on_createAddIngredientBtn_clicked(){
    QString saveResult = cp->on_createAddIngredientBtn_clicked();
    statusBar()->showMessage(saveResult,2000);
}

void MainWindow::on_createAddKeywordBtn_clicked() {
    QString saveResult = cp->on_createAddKeywordBtn_clicked();
    statusBar()->showMessage(saveResult,2000);
}

void MainWindow::on_addedFrameDeleteButton_clicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    cp->on_addedFrameDeleteButton_clicked(button);
}

void MainWindow::on_uploadImgBtn_clicked() {
    cp->on_uploadImgBtn_clicked();
}

void MainWindow::on_createRatingCheckBox_stateChanged(int arg1){
    cp->on_createRatingCheckBox_stateChanged(arg1);
}

void MainWindow::on_createResetBtn_clicked() {
    cp->on_createResetBtn_clicked();
}

//home page

void MainWindow::setupHomePage() {
    //"D:/Daniel/Dokumente/QtProjects/recipefolder"
    ui->homeDirectoryLineEdit->setText(rm->getIoManager()->getDirectoryPath());
}

void MainWindow::on_homeSetDirectoryLabel_clicked(){
    hp->on_homeSetDirectoryLabel_clicked();
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

void MainWindow::loadSettings(){
    QSettings settings;
    rm = new RecipeManager(settings.value("savePath").toString());
}

RecipeManager *MainWindow::getRm() const {
    return rm;
}

void MainWindow::setRm(RecipeManager *rm){
    this->rm = rm;
}

void MainWindow::on_searchSortComboBox_currentIndexChanged(int index){
    sp->on_searchSortComboBox_currentIndexChanged(index);
}
