#include "QString"
#include "QXmlStreamReader"

#ifndef IOMANAGER_H
#define IOMANAGER_H

class Ingredient;
class Recipe;
class QXmlStreamWriter;
class QXmlStreamReader;
class PathPixmap;

class IOManager
{
public:
    IOManager(QString directoryPath) : directoryPath(directoryPath) {}

    ~IOManager();

    QList<Recipe*> loadRecipes();
    void saveRecipe(Recipe* recipe) const;

    void setDirectoryPath(const QString &value);
    QString getDirectoryPath() const;

private:
    QString directoryPath;

    Recipe* parseRecipe(QXmlStreamReader* xmlReader);
    PathPixmap* parsePixmap(QString path);
};

#endif // IOMANAGER_H
