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
    if (name == "" && category == "egal" && favourite == "egal" && ingList.empty() && keywList.empty() && rating == -1) {
        return recipeList;
    }
    //
    if (category == "" || favourite == ""){
        return vector<Recipe>();
    }

    vector<Recipe> foundRecipes;
    for (auto r : recipeList){
        if (!r.getName().toUpper().contains(name.toUpper())){
            continue;
        } else if(r.getCategory().toUpper() != category.toUpper() && category != "egal") {
            continue;
        } else if(r.getFavouriteAsQString().toUpper() != favourite.toUpper() && favourite != "egal"){
            continue;
        } else if(r.getRating() == 0 || (r.getRating() != 0 && rating != -1 && r.getRating() != rating)){
            continue;
        }
        //check if all ingredients found in recipe, if not continue
        bool notFound = false;
        auto recipeIngs = r.getIngredientStrings();
        for (auto ing : ingList){
            if (std::find(recipeIngs.begin(), recipeIngs.end(), ing) == recipeIngs.end()){
                notFound = true;
                break;
            }
        }
        //check if all keywords found in recipe, if not continue
        auto recipeKeyw = r.getKeywords();
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
        recipeList = ioManager->loadRecipes();
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


