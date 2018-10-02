#include <vector>

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
    bool saveIngredient(Ingredient ingredient);
    IOManager* getIoManager();

    vector<Ingredient> getIngredientList();
    vector<Recipe> getRecipeList();

    bool isNewRecipe(Recipe recipe);

private:

    IOManager* ioManager;
    vector<Ingredient> ingredientList;
    vector<Recipe> recipeList;

    bool isNewIngredient(Ingredient ingredient);
};

#endif // RECIPEMANAGER_H
