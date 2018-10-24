#include "recipesearchresultframe.h"

#include "QLayout"
#include "QHBoxLayout"
#include "QGridLayout"
#include "QLabel"
#include "QMouseEvent"
#include "QDebug"
#include "QEvent"
#include "QMetaEnum"
#include "QCoreApplication"
#include "QPicture"
#include "mainwindow.h"

#include "stareditor.h"
#include "ingredient.h"
#include "parameterbutton.h"
#include "clickablelabel.h"
#include "searchpage.h"


RecipeSearchResultFrame::RecipeSearchResultFrame(MainWindow* mw, Recipe* recipe, QHBoxLayout* starLayout, int index, QWidget* parent) : QWidget(parent), recipe(recipe), mw(mw){
    setMouseTracking(true);
    QCoreApplication::instance()->installEventFilter(this); //install filter application-wide

    horLayout = new QHBoxLayout();
    gridLayout = new QGridLayout();

    //setup gridlayout
    gridLayout->setMargin(0);
    gridLayout->setSpacing(5);
    gridLayout->addWidget(createIndex(index),0,0);
    gridLayout->addWidget(createInspectLabel(),1,0);
    gridLayout->addWidget(createTitle(),0,1);
    gridLayout->addWidget(createFavouriteLabel(),0,2);
    gridLayout->addWidget(createDate(),1,1);
    gridLayout->addWidget(createCategoryIngredientAmountLabel(),2,1);
    gridLayout->addWidget(createStarRating(starLayout),3,1);
    gridLayout->addWidget(createDeleteButton(),3,0);

    horLayout->addLayout(gridLayout);
    horLayout->addWidget(createImage());

    frame = new QFrame();
    frame->setFrameStyle(QFrame::Raised | QFrame::Box);
    frame->setLayout(horLayout);
}

bool RecipeSearchResultFrame::eventFilter(QObject *obj, QEvent *event) {
    if (!dynamic_cast<QMouseEvent*>( event )){
        return false;
    }

    if( event->type() == QEvent::MouseButtonPress && obj == frame){
        mousePressEvent(dynamic_cast<QMouseEvent*>(event));
        return true;
    }
    return false;
}

void RecipeSearchResultFrame::mousePressEvent(QMouseEvent* /*event*/){
    if (!recipe->getPixmapList().empty()){
        emit on_mousePressed(recipe);
    }
}

QFrame *RecipeSearchResultFrame::getFrame() const{
    return frame;
}

QLabel* RecipeSearchResultFrame::createIndex(int index){
    QLabel* label = new QLabel(QString::number(index));
    label->setMinimumSize(30, 20);
    label->setMaximumSize(30, 20);
    label->setStyleSheet("font: bold large; font-size: 12px");
    label->setMouseTracking(true);
    return label;
}

ClickableLabel *RecipeSearchResultFrame::createInspectLabel(){
    ClickableLabel* inspect = new ClickableLabel();
    QPixmap pm(":/img/magn_glass.png");
    inspect->setPixmap(pm);
    inspect->setMaximumSize(20, 20);
    inspect->setScaledContents(true);
    inspect->setMouseTracking(true);
    inspect->setStyleSheet("background: transparent");
    inspect->setRecipe(recipe);
    connect(inspect, &ClickableLabel::clicked, mw->getSp(), &SearchPage::openChangeDialog);
    return inspect;
}

QLabel *RecipeSearchResultFrame::createTitle() {
    QLabel* name = new QLabel(recipe->getName());
    name->setMinimumSize(200, 20);
    name->setMaximumSize(250, 20);
    name->setStyleSheet("font: bold large; font-size: 12px");
    name->setMouseTracking(true);
    return name;
}

QLabel *RecipeSearchResultFrame::createDate(){
    QLabel* date = new QLabel(recipe->getCreationDate());
    date->setMaximumSize(150, 20);
    date->setMouseTracking(true);
    return date;
}

QLabel* RecipeSearchResultFrame::createFavouriteLabel() {
    heart = new ClickableLabel();
    heart->setRecipe(recipe);
    if (recipe->getFavourite()){
        QPixmap pm(":/img/heart_on.png");
        heart->setPixmap(pm);
    } else {
        QPixmap pm(":/img/heart_off.png");
        heart->setPixmap(pm);
    }
    heart->setMaximumSize(20, 20);
    heart->setScaledContents(true);
    heart->setMouseTracking(true);
    connect(heart, &ClickableLabel::clicked, mw->getSp(), &SearchPage::setFavourite);

    return heart;
}

QLabel *RecipeSearchResultFrame::createCategoryIngredientAmountLabel(){
    QString suffix = " Zutaten";
    if (recipe->getNumberOfIngredients() == 1){
        suffix = " Zutat";
    }
    QLabel* label = new QLabel(recipe->getCategory() + " mit " + QString::number(recipe->getNumberOfIngredients()) + suffix);
    label->setMaximumSize(200, 20);
    label->setMouseTracking(true);
    return label;
}

QFrame *RecipeSearchResultFrame::createStarRating(QHBoxLayout* starLayout){
    QFrame* starFrame = new QFrame();
    starFrame->setMinimumSize(155, 20);
    starFrame->setMaximumSize(155, 20);
    starFrame->setLayout(starLayout);
    starFrame->setFrameStyle(QFrame::Raised | QFrame::Box);
    starFrame->setDisabled(true);
    starFrame->setMouseTracking(true);
    StarEditor* starEditor = starFrame->layout()->parent()->findChild<StarEditor*>();
    starEditor->setStarPosition(recipe->getRating());
    starEditor->setStarRatingPaintingScaleFactor(15);
    return starFrame;
}

QFrame *RecipeSearchResultFrame::createImage(){
    QLabel* image = new QLabel();
    image->setMaximumSize(110, 110);
    if (!recipe->getPixmapList().empty()){
        image->setPixmap(recipe->getPixmapList().at(0).getPixmap());
    }
    image->setScaledContents(true);
    image->setMouseTracking(true);
    QGridLayout* imageLayout = new QGridLayout();
    imageLayout->addWidget(image);
    imageLayout->setSpacing(0);
    imageLayout->setMargin(0);
    QFrame* imageFrame = new QFrame();
    imageFrame->setMinimumSize(110,110);
    imageFrame->setMaximumSize(110,110);
    imageFrame->setFrameStyle(QFrame::NoFrame | QFrame::Box);
    imageFrame->setLayout(imageLayout);
    imageFrame->setMouseTracking(true);
    return imageFrame;
}

ParameterButton* RecipeSearchResultFrame::createDeleteButton(){
    deleteButton = new ParameterButton(recipe);
    deleteButton->setMaximumSize(20,20);
    deleteButton->setMinimumSize(20,20);
    deleteButton->setText("X");
    deleteButton->setStyleSheet("font: 12px bold red; background-color: qradialgradient(cx:0, cy:0, radius: 1.6, fx:0.5, fy:0.5, \
                                    stop:0  rgb(255, 239, 229), stop:0.8 rgb(247, 188, 128), stop:1  rgb(247, 188, 128));}"
                                );
    return deleteButton;
}

QLabel *RecipeSearchResultFrame::getHeart() const{
    return heart;
}

ParameterButton *RecipeSearchResultFrame::getDeleteButton() const{
    return deleteButton;
}
