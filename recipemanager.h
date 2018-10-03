#include <vector>
#include "QString"

#ifndef RECIPEMANAGER_H
#define RECIPEMANAGER_H

using std::vector;

class Ingredient;
class Recipe;
class IOManager;

class RecipeManager
{
public:
    RecipeManager();

    void sortRecipes();

    bool saveRecipe(Recipe recipe);
    IOManager* getIoManager();

    vector<Ingredient> getIngredientList();
    vector<Recipe> getRecipeList();
    vector<QString> getKeywordList() const;

private:
    IOManager* ioManager;
    vector<Ingredient> ingredientList;
    vector<Recipe> recipeList;
    vector<QString> keywordList;

    bool isNewIngredient(Ingredient ingredient);
    bool isNewRecipe(Recipe recipe);
    bool isNewKeyword(QString keyword);
};

#endif // RECIPEMANAGER_H
