#include "recipemanager.h"
#include "ingredient.h"
#include "recipe.h"
#include "iomanager.h"

#include "QDir"
#include "QXmlStreamWriter"

RecipeManager::RecipeManager(){
    ioManager = new IOManager();
}

void RecipeManager::sortRecipes(){

}

bool RecipeManager::saveRecipe(Recipe recipe){
    if (isNewRecipe(recipe)) {
        recipeList.push_back(recipe);
        for (auto i : recipe.getIngredients()){
            if (isNewIngredient(i)){
                ingredientList.push_back(i);
            }
        }
        for (auto k : recipe.getKeywords()){
            if (isNewKeyword(k)){
                keywordList.push_back(k);
            }
        }
        //TODO add sorting
        ioManager->saveRecipe(recipe);
        return true;
    } else {
        return false;
    }
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
        if (ing == ingredient) {
            return false;
        }
    }
    return true;
}

IOManager *RecipeManager::getIoManager() {
    return ioManager;
}

vector<Recipe> RecipeManager::getRecipeList(){
    return recipeList;
}

vector<QString> RecipeManager::getKeywordList() const{
    return keywordList;
}

vector<Ingredient> RecipeManager::getIngredientList(){
    return ingredientList;
}
