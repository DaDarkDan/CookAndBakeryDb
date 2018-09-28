#include "QString"
#include <vector>

#ifndef IOMANAGER_H
#define IOMANAGER_H

using std::vector;

class Ingredient;
class Recipe;
class QXmlStreamWriter;
class QXmlStreamReader;

class IOManager
{
public:
    IOManager();

    ~IOManager();

    void loadRecipes();
    void saveRecipe(Recipe recipe);

    void loadIngredients();
    void saveIngredient(Ingredient ingredient);

private:
    QXmlStreamWriter* xmlWriter;
    QXmlStreamReader* xmlReader;
    QString directoryPath;

    vector<Recipe> recipeList;
    vector<Ingredient> ingredientList;
};

#endif // IOMANAGER_H
