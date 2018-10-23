#include "recipemanager.h"
#include "ingredient.h"
#include "recipe.h"
#include "iomanager.h"
#include "recipecompare.h"

#include "QDir"
#include "QXmlStreamWriter"

#include <algorithm>

#include "QDebug"

RecipeManager::RecipeManager(QString directoryPath){
    ioManager = new IOManager(directoryPath);
    recipeList = ioManager->loadRecipes();
    currentSorting = 0;
    addAllUniqueIngredientsAndKeywords();
}

void RecipeManager::sortRecipes(){
    switch(currentSorting){
    case 0: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::NAME_ASC));
        break;
    case 1: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::NAME_DESC));
        break;
    case 2: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::DATE_ASC));
        break;
    case 3: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::DATE_DESC));
        break;
    case 4: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::CATEGORY_ASC));
        break;
    case 5: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::CATEGORY_DESC));
        break;
    case 6: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::FAVOURITE));
        break;
    case 7: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::RATING_ASC));
        break;
    case 8: std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::RATING_DESC));
        break;
    default:
        qDebug() << "ERROR in sorting input";
    }
}

void RecipeManager::setCurrentSorting(int value)
{
    currentSorting = value;
}

QList<Recipe*> RecipeManager::findRecipes(const QString& name, const QString& category,
                           const QString& favourite, const QList<QString> ingList,
                           const QList<QString> keywList, int rating){
    sortRecipes();
    //return all recipes if no parameter set
    if (name == "" && category == "egal" && favourite == "egal" && ingList.empty() && keywList.empty() && rating == -1) {
        return recipeList;
    }

    if (category == "" || favourite == ""){
        return QList<Recipe*>();
    }

    QList<Recipe*> foundRecipes;
    for (auto r : recipeList){
        if (!r->getName().toUpper().contains(name.toUpper())){
            continue;
        } else if(r->getCategory().toUpper() != category.toUpper() && category != "egal") {
            continue;
        } else if(r->getFavouriteAsQString().toUpper() != favourite.toUpper() && favourite != "egal"){
            continue;
        } else if(rating != -1 && rating != r->getRating()){
            continue;
        }
        //check if all ingredients found in recipe, if not continue
        bool notFound = false;
        auto recipeIngs = r->getIngredientStrings();
        for (auto ing : ingList){
            if (std::find(recipeIngs.begin(), recipeIngs.end(), ing) == recipeIngs.end()){
                notFound = true;
                break;
            }
        }
        //check if all keywords found in recipe, if not continue
        auto recipeKeyw = r->getKeywords();
        for (auto keyw : keywList){
            if (std::find(recipeKeyw.begin(), recipeKeyw.end(), keyw) == recipeKeyw.end()){
                notFound = true;
                break;
            }
        }
        if (!notFound){
            foundRecipes.push_back(r);
        }
    }

    return foundRecipes;
}

bool RecipeManager::saveRecipe(Recipe* recipe, bool overwriteFlag){
    if (isNewRecipe(*recipe) || overwriteFlag) {
        recipeList.push_back(recipe);
        for (auto i : recipe->getIngredients()){
            if (isNewIngredient(i)){
                ingredientList.push_back(i.getName());
            }
        }
        for (auto k : recipe->getKeywords()){
            if (isNewKeyword(k)){
                keywordList.push_back(k);
            }
        }
        sortRecipes();
        std::sort(ingredientList.begin(), ingredientList.end());
        std::sort(keywordList.begin(), keywordList.end());
        ioManager->saveRecipe(recipe);
        return true;
    }
    return false;
}

bool RecipeManager::isNewRecipe(Recipe recipe) {
    for(auto rec : recipeList){
        if (*rec == recipe) {
            return false;
        }
    }
    return true;
}

bool RecipeManager::isNewKeyword(QString keyword){
    for (auto k : keywordList){
        if (k == keyword){
            return false;
        }
    }
    return true;
}

bool RecipeManager::isNewIngredient(Ingredient ingredient) {
    for(auto ing : ingredientList){
        if (ing == ingredient.getName()) {
            return false;
        }
    }
    return true;
}

IOManager *RecipeManager::getIoManager() {
    return ioManager;
}

QList<Recipe*> RecipeManager::getRecipeList() const{
    return recipeList;
}

QList<QString> RecipeManager::getKeywordList() const{
    return keywordList;
}

void RecipeManager::deleteRecipe(Recipe *recipe){
    for (unsigned int i = 0; i < recipeList.size();i++) {
        if (recipeList.at(i) == recipe){
            recipeList.erase(recipeList.begin()+i);
            QFile file(recipe->getFullPath());
            file.remove();
            delete recipe;
        }
    }
}

QList<QString> RecipeManager::getIngredientList() const{
    return ingredientList;
}

void RecipeManager::addAllUniqueIngredientsAndKeywords(){
    for (auto r : recipeList){
        for (auto i : r->getIngredients()){
            //if ingredient not found in list, add it
            if (std::find(ingredientList.begin(), ingredientList.end(), i.getName()) == ingredientList.end()){
                ingredientList.push_back(i.getName());
            }
        }
        std::sort(ingredientList.begin(), ingredientList.end());
        for (auto k : r->getKeywords()){
            //if keyword not found in list, add it
            if (std::find(keywordList.begin(), keywordList.end(), k) == keywordList.end()){
                keywordList.push_back(k);
            }
        }
        std::sort(keywordList.begin(), keywordList.end());
    }
}


