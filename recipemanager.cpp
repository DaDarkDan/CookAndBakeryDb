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
        //TODO add sorting
        ioManager->saveRecipe(recipe);
        return true;
    } else {
        return false;
    }
}

bool RecipeManager::saveIngredient(Ingredient ingredient){
    if (isNewIngredient(ingredient)){
        ingredientList.push_back(ingredient);
        //TODO add sorting
        ioManager->saveIngredients(ingredientList);
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

vector<Ingredient> RecipeManager::getIngredientList(){
    return ingredientList;
}
