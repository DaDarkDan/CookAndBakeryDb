#include "recipesearchresultframe.h"

#include "QLayout"
#include "QHBoxLayout"
#include "QGridLayout"
#include "QLabel"
#include "QMouseEvent"

#include "stareditor.h"
#include "ingredient.h"

#include "QDebug"
#include "QEvent"
#include "QMetaEnum"
#include "QCoreApplication"

RecipeSearchResultFrame::RecipeSearchResultFrame(Recipe recipe, QHBoxLayout* starLayout, int index, QWidget* parent) : QWidget(parent), recipe(recipe){
    setMouseTracking(true);
    QCoreApplication::instance()->installEventFilter(this); //install filter application-wide

    horLayout = new QHBoxLayout();
    gridLayout = new QGridLayout();

    //setup gridlayout
    gridLayout->setMargin(5);
    gridLayout->setSpacing(5);
    gridLayout->addWidget(createIndex(index),0,0);
    gridLayout->addWidget(createTitle(),0,1);
    gridLayout->addWidget(createDate(),1,1);
    gridLayout->addWidget(createInAmount(),2,1);
    gridLayout->addWidget(createStarRating(starLayout),3,1);

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
    emit on_mousePressed(recipe.getPixmap());
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

QLabel *RecipeSearchResultFrame::createTitle() {
    QLabel* name = new QLabel(recipe.getName());
    name->setMinimumSize(200, 20);
    name->setMaximumSize(250, 20);
    name->setStyleSheet("font: bold large; font-size: 12px");
    name->setMouseTracking(true);
    return name;
}

QLabel *RecipeSearchResultFrame::createDate(){
    QLabel* date = new QLabel(recipe.getCreationDate());
    date->setMaximumSize(150, 20);
    date->setMouseTracking(true);
    return date;
}

QLabel *RecipeSearchResultFrame::createInAmount(){
    QLabel* ing = new QLabel(QString::number(recipe.getNumberOfIngredients()) + " Zutaten");
    ing->setMaximumSize(150, 20);
    ing->setMouseTracking(true);
    return ing;
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
    starEditor->setStarPosition(recipe.getRating());
    starEditor->setStarRatingPaintingScaleFactor(15);
    return starFrame;
}

QFrame *RecipeSearchResultFrame::createImage(){
    QLabel* image = new QLabel();
    image->setMaximumSize(100, 100);
    image->setPixmap(recipe.getPixmap());
    image->setScaledContents(true);
    image->setMouseTracking(true);
    QGridLayout* imageLayout = new QGridLayout();
    imageLayout->addWidget(image);
    imageLayout->setSpacing(0);
    imageLayout->setMargin(0);
    QFrame* imageFrame = new QFrame();
    imageFrame->setMinimumSize(100,100);
    imageFrame->setMaximumSize(100,100);
    imageFrame->setFrameStyle(QFrame::NoFrame | QFrame::Box);
    imageFrame->setLayout(imageLayout);
    imageFrame->setMouseTracking(true);
    return imageFrame;
}
