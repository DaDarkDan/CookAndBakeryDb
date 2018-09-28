#include "recipemanager.h"
#include "ingredient.h"
#include "recipe.h"
#include "QDir"
#include "QXmlStreamWriter"

RecipeManager::RecipeManager(){
}

RecipeManager::~RecipeManager(){}



void RecipeManager::sortRecipes(){

}

bool RecipeManager::isNewIngredient(Ingredient ingredient){
    for(auto ing : ingredientList){
        if (ing == ingredient) {
            return false;
        }
    }
    return true;
}
