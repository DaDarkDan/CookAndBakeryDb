#include "recipeframe.h"

#include "ingredient.h"

#include "QGridLayout"
#include "QFormLayout"

RecipeFrame::RecipeFrame(Recipe recipe) :recipe(recipe){

    QGridLayout* gridL = new QGridLayout();
    gridL->addWidget(createTitleFrame(),0,0);



    this->setLayout(gridL);
}

QFrame *RecipeFrame::createTitleFrame(){
    QFrame* frame = new QFrame();
    QFormLayout* fl = new QFormLayout();
    fl->addWidget(new QLabel("Rezeptname"));
    fl->addWidget(new QLabel(recipe.getName()));
    fl->addWidget(new QLabel("Kategorie"));
    fl->addWidget(new QLabel(recipe.getCategory()));
    fl->addWidget(new QLabel("Favorit"));
    if (recipe.getFavourite()){
        fl->addWidget(new QLabel("Ja"));
    } else {
        fl->addWidget(new QLabel("Nein"));
    }

    frame->setLayout(fl);
    frame->setMaximumSize(300, 50);
    frame->setMinimumSize(300, 50);
    return frame;
}
