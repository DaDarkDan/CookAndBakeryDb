#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recipe.h"
#include "recipemanager.h"
#include "ingredient.h"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setup create page
    QComboBox* categoryComboBox = findChild<QComboBox*>("createCategoryComboBox");
    categoryComboBox->addItems(Recipe::categoryList);

    QComboBox* weightTypeComboBox = findChild<QComboBox*>("createAddIngredientWeightTypeComboBox");
    weightTypeComboBox->addItems(Ingredient::weightTypeList);

    //set up scroll boxes
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    ui->createAddedIngredientsScrollViewContents->setLayout(layout);
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    ui->createAddedKeywordsScrollBoxContents->setLayout(layout);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_createSaveBtn_clicked(){
    Recipe* recipe = new Recipe();
    //name
    QTextEdit* nameTxtEdit = findChild<QTextEdit*>("createNameTxtEdit");
    recipe->setName(nameTxtEdit->toPlainText());
    //category
    QComboBox* categoryComboBox = findChild<QComboBox*>("createCategoryComboBox");
    recipe->setCategory(categoryComboBox->currentText());
    //ingredients

    //keywords

    //rating

    //notes


    if (nameTxtEdit->toPlainText() == "" || RecipeManager::isNewRecipe(*recipe)){
        RecipeManager::getIoManager()->saveRecipe(*recipe);
    } else {
        //TODO show error message
    }
}

void MainWindow::on_pushButton_clicked() {
    RecipeManager::getIoManager()->setDirectoryPath(QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_createAddIngredientBtn_clicked(){
    QTextEdit* nameTxtEdit = ui->createIngredientNameTxtEdit;
    QTextEdit* amountTxtEdit = ui->createIngredientAmountTxtEdit;
    QComboBox* weightTypeComboBox = ui->createAddIngredientWeightTypeComboBox;

    if (nameTxtEdit->toPlainText() != "" && amountTxtEdit->toPlainText() != ""){
        //copy values to new widgets
        QTextEdit* name = new QTextEdit(nameTxtEdit->toPlainText());
        name->setMaximumHeight(25);
        name->setMinimumHeight(25);
        name->setMaximumWidth(150);
        name->setMinimumWidth(100);
        nameTxtEdit->clear();
        QTextEdit* amount = new QTextEdit(amountTxtEdit->toPlainText());
        amount->setMaximumHeight(25);
        amount->setMinimumHeight(25);
        amount->setMaximumWidth(100);
        amount->setMinimumWidth(50);
        amountTxtEdit->clear();
        QComboBox* weightType = new QComboBox();
        weightType->addItems(Ingredient::weightTypeList);
        weightType->setCurrentText(weightTypeComboBox->currentText());
        weightType->setMaximumHeight(25);
        weightType->setMinimumHeight(25);
        weightType->setMaximumWidth(70);
        weightType->setMinimumWidth(70);

        QPushButton* deleteButton = new QPushButton("Entfernen");
        deleteButton->setMaximumHeight(25);
        deleteButton->setMinimumHeight(25);
        deleteButton->setMaximumWidth(80);
        deleteButton->setMinimumWidth(80);
        connect(deleteButton, SIGNAL(clicked()), this, SLOT(onIngredientDeleteButton_clicked()));
        //Set up frame
        QFrame* frame = new QFrame();
        frame->setMaximumHeight(40);
        QSizePolicy* sp = new QSizePolicy();
        sp->setVerticalPolicy(QSizePolicy::Maximum);
        frame->setSizePolicy(*sp);
        frame->setStyleSheet(" .QFrame {background-color : red}");

        QHBoxLayout* frameLayout = new QHBoxLayout(frame);
        frameLayout->addWidget(name);
        frameLayout->addWidget(amount);
        frameLayout->addWidget(weightType);
        frameLayout->addWidget(deleteButton);

        ui->createAddedIngredientsScrollViewContents->layout()->addWidget(frame);
        addedIngredientList.push_back(frameLayout);
    }
}

void MainWindow::onIngredientDeleteButton_clicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    QFrame* parentFrame = qobject_cast<QFrame*>(button->parent());

    for (auto child : parentFrame->children()){
        delete child;
    }
    delete parentFrame;
}
