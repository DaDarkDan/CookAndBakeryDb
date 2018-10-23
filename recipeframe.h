#ifndef RECIPEFRAME_H
#define RECIPEFRAME_H

#include "QLabel"
#include "QFrame"

#include "recipe.h"

class RecipeFrame : public QWidget
{
    Q_OBJECT
public:
    RecipeFrame(Recipe recipe);

private:
    Recipe recipe;

    QFrame* createTitleFrame();
};

#endif // RECIPEFRAME_H
