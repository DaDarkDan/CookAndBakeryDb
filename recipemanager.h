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
    RecipeManager(QString directoryPath);

    friend class RecipeCompare;

    vector<Recipe*> findRecipes(const QString& name = "", const QString& category = "",
                               const QString& favourite = "", const vector<QString> ingList = vector<QString>(),
                               const vector<QString> keywList = vector<QString>(), int rating = -1);

    bool saveRecipe(Recipe* recipe);
    IOManager* getIoManager();

    vector<QString> getIngredientList() const;
    vector<Recipe*> getRecipeList() const;
    vector<QString> getKeywordList() const;

    void deleteRecipe(Recipe* recipe);

    void setCurrentSorting(int value);

private:
    IOManager* ioManager;
    vector<QString> ingredientList;
    vector<Recipe*> recipeList;
    vector<QString> keywordList;

    bool isNewIngredient(Ingredient ingredient);
    bool isNewRecipe(Recipe recipe);
    bool isNewKeyword(QString keyword);

    void addAllUniqueIngredientsAndKeywords();

    void sortRecipes();

    int currentSorting;
};

#endif // RECIPEMANAGER_H
