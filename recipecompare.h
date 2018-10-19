#include "recipe.h"

#ifndef RECIPECOMPARE_H
#define RECIPECOMPARE_H

class RecipeCompare
{
public:
    enum CompareType {
        NAME_ASC = 0, NAME_DESC,
        DATE_ASC, DATE_DESC,
        CATEGORY_ASC, CATEGORY_DESC,
        FAVOURITE,
        RATING_ASC,  RATING_DESC
    };

    RecipeCompare(CompareType ct) : ct(ct) {}
    bool operator()(Recipe* l, Recipe* r);

private:
    CompareType ct;
};

#endif // RECIPECOMPARE_H
