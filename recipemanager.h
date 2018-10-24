#include "QString"
#include "QList"

#ifndef RECIPEMANAGER_H
#define RECIPEMANAGER_H

class Ingredient;
class Recipe;
class IOManager;

class RecipeManager
{
public:
    RecipeManager(QString directoryPath);

    friend class RecipeCompare;

    QList<Recipe*> findRecipes(const QString& name = "", const QString& category = "",
                               const QString& favourite = "", const QList<QString> ingList = QList<QString>(),
                               const QList<QString> keywList = QList<QString>(), int rating = -1);

    bool saveRecipe(Recipe* recipe, bool overwriteFlag = false);
    IOManager* getIoManager();

    QList<QString> getIngredientList() const;
    QList<Recipe*> getRecipeList() const;
    QList<QString> getKeywordList() const;

    void deleteRecipe(Recipe* recipe);

    void setCurrentSorting(int value);

    bool isNewRecipe(Recipe recipe);

private:
    IOManager* ioManager;
    QList<QString> ingredientList;
    QList<Recipe*> recipeList;
    QList<QString> keywordList;

    bool isNewIngredient(const Ingredient& ingredient) const;
    bool isNewKeyword(const QString& keyword) const;

    void addAllUniqueIngredientsAndKeywords();

    void sortRecipes();

    QString createId() const;
    int convertIdStringToInt(QString id) const;
    QString convertIdIntToString(int id) const;

    int currentSorting;
};

#endif // RECIPEMANAGER_H
