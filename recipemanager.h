#include <vector>
#include <string>

#ifndef RECIPEMANAGER_H
#define RECIPEMANAGER_H

using std::vector;

class Ingredient;
class Recipe;
class IOManager;

class RecipeManager
{
public:
    void sortRecipes();

    static bool saveRecipe(Recipe recipe);
    static bool saveIngredient(Ingredient ingredient);
    static IOManager* getIoManager();

    static vector<Ingredient> getIngredientList();
    static vector<Recipe> getRecipeList();

    static bool isNewRecipe(Recipe recipe);

private:
    RecipeManager();

    static IOManager* ioManager;
    static vector<Ingredient> ingredientList;
    static vector<Recipe> recipeList;

    static bool isNewIngredient(Ingredient ingredient);
};

#endif // RECIPEMANAGER_H
