#include <vector>

#include "QString"

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

    vector<Recipe> loadRecipes() const;
    void saveRecipe(Recipe recipe) const;

    vector<Ingredient> loadIngredients() const;
    void saveIngredients(vector<Ingredient> ingredients) const;

    void setDirectoryPath(const QString &value);
    QString getDirectoryPath() const;

private:
    QString directoryPath;
    const QString ingFileName;
};

#endif // IOMANAGER_H
