#include "recipemanager.h"
#include "ingredient.h"
#include "recipe.h"
#include "iomanager.h"

#include "QDir"
#include "QXmlStreamWriter"

#include <algorithm>

RecipeManager::RecipeManager(){
    ioManager = new IOManager();
    recipeList = ioManager->loadRecipes();
    addAllUniqueIngredientsAndKeywords();
}

void RecipeManager::sortRecipes(RecipeCompare rc){
    std::sort(recipeList.begin(), recipeList.end(), rc);
}

vector<Recipe> RecipeManager::findRecipes(const QString& name, const QString& category,
                           const QString& favourite, const vector<QString> ingList,
                           const vector<QString> keywList, int rating) const{
    //return all recipes if no parameter set
    if (name == "" && category == "" && favourite == "egal" && ingList.empty() && keywList.empty() && rating == 0) {
        return recipeList;
    }

    vector<Recipe> foundRecipes;
    for (auto r : recipeList){
        //TODO add rating
        if (!r.getName().toUpper().contains(name.toUpper()) || r.getRating() != rating){
            continue;
        } else if(r.getCategory().toUpper() != category.toUpper() && category != "egal") {
            continue;
        } else if(r.getFavouriteAsQString().toUpper() != favourite.toUpper() && favourite != "egal"){
            foundRecipes.push_back(r);
            continue;
        }
        //check if all ingredients found in recipe, if not continue
        //TODO ÜBERARBEITEN: sucht nur sublist in derselben Reihenfolge!!!
        auto recipeIngs = r.getIngredientStrings();
        vector<QString>::iterator ingPos = std::search(recipeIngs.begin(), recipeIngs.end(),
                                                       ingList.begin(), ingList.end());
        if (ingPos == recipeIngs.end()){
            continue;
        }
        //check if all keywords found in recipe, if not continue
        auto keywPos = std::search(r.getKeywords().begin(), r.getKeywords().end(),
                                   keywList.begin(), keywList.end());
        if (keywPos == r.getKeywords().end()){
            continue;
        }
        foundRecipes.push_back(r);
    }
    return foundRecipes;
}

bool RecipeManager::saveRecipe(Recipe recipe){
    if (isNewRecipe(recipe)) {
        recipeList.push_back(recipe);
        for (auto i : recipe.getIngredients()){
            if (isNewIngredient(i)){
                ingredientList.push_back(i.getName());
            }
        }
        for (auto k : recipe.getKeywords()){
            if (isNewKeyword(k)){
                keywordList.push_back(k);
            }
        }
        std::sort(recipeList.begin(), recipeList.end(), RecipeCompare(RecipeCompare::CompareType::NAME_ASC));
        std::sort(ingredientList.begin(), ingredientList.end());
        std::sort(keywordList.begin(), keywordList.end());
        ioManager->saveRecipe(recipe);
        return true;
    }
    return false;
}

bool RecipeManager::isNewRecipe(Recipe recipe) {
    for(auto rec : recipeList){
        if (rec == recipe) {
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

vector<Recipe> RecipeManager::getRecipeList() const{
    return recipeList;
}

vector<QString> RecipeManager::getKeywordList() const{
    return keywordList;
}

vector<QString> RecipeManager::getIngredientList() const{
    return ingredientList;
}

void RecipeManager::addAllUniqueIngredientsAndKeywords(){
    for (auto r : recipeList){
        for (auto i : r.getIngredients()){
            //if ingredient not found in list, add it
            if (std::find(ingredientList.begin(), ingredientList.end(), i.getName()) == ingredientList.end()){
                ingredientList.push_back(i.getName());
            }
        }
        std::sort(ingredientList.begin(), ingredientList.end());
        for (auto k : r.getKeywords()){
            //if keyword not found in list, add it
            if (std::find(keywordList.begin(), keywordList.end(), k) == keywordList.end()){
                keywordList.push_back(k);
            }
        }
        std::sort(keywordList.begin(), keywordList.end());
    }
}


