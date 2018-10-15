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
    IOManager(QString directoryPath) : directoryPath(directoryPath) {}

    ~IOManager();

    vector<Recipe> loadRecipes() const;
    void saveRecipe(Recipe recipe) const;

    void setDirectoryPath(const QString &value);
    QString getDirectoryPath() const;

private:
    QString directoryPath;
};

#endif // IOMANAGER_H
