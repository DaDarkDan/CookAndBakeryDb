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
    RecipeManager();
    ~RecipeManager();

    void sortRecipes();

private:
    IOManager* ioManager;
    vector<Ingredient> ingredientList;
    vector<Recipe> recipeList;

    bool isNewIngredient(Ingredient ingredient);
};

#endif // RECIPEMANAGER_H
