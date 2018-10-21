#include "recipecompare.h"

bool RecipeCompare::operator()(Recipe* l, Recipe* r) {
    switch(ct){
    case NAME_ASC:
        return l->getName().toUpper() < r->getName().toUpper();
    case NAME_DESC:
        return l->getName().toUpper() > r->getName().toUpper();
    case DATE_ASC:
        return l->getCreationDate() < r->getCreationDate();
    case DATE_DESC:
        return l->getCreationDate() > r->getCreationDate();
    case CATEGORY_ASC:
        return l->getCategory() < r->getCategory();
    case CATEGORY_DESC:
        return l->getCategory() > r->getCategory();
    case FAVOURITE:
        if (l->getFavourite() && r->getFavourite()){
            return l->getName().toUpper() < r->getName().toUpper();
        } else if (l->getFavourite() && !r->getFavourite()) {
            return true;
        } else if (!l->getFavourite() && r->getFavourite()){
            return false;
        } else {
            return l->getName().toUpper() < r->getName().toUpper();
        }
    case RATING_ASC:
        return l->getRating() < r->getRating();
    case RATING_DESC:
        return l->getRating() > r->getRating();
    }

    return false;
}
