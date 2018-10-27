#include <vector>
#include <ctime>

#include "QString"
#include "QStringList"
#include "QPixmap"
#include "QMap"

#include "pathpixmap.h"

#ifndef RECIPE_H
#define RECIPE_H

using std::vector;

class Ingredient;
class QImage;

class Recipe {
    public:
        Recipe();

        ~Recipe();

        friend class RecipeCompare;

        QString getName() const;
        void setName(const QString &value);

        vector<Ingredient> getIngredients() const;
        void setIngredients(const vector<Ingredient> &value);
        void addIngredient(const Ingredient& ing);

        QString getCategory() const;
        void setCategory(const QString &value);

        vector<QString> getKeywords() const;
        void setKeywords(const vector<QString> &value);
        void addKeyword(const QString& keyword);

        QString getNotes() const;
        void setNotes(const QString &value);

        bool getFavourite() const;
        void setFavourite(bool value);
        QString getFavouriteAsQString() const;
        void setFavourite(const QString& value);

        bool operator==(const Recipe& rRecipe) const;
        bool operator!=(const Recipe& rRecipe) const;

        QString getCreationDate() const;
        void setCreationDate(const QString& value = "now");

        static QStringList categoryList;

        int getRating() const;
        void setRating(int value);

        vector<QString> getIngredientStrings() const;

        int getNumberOfIngredients() const;

        int getNumberOfKeywords() const;

        QString getFullPath() const;
        void setFullPath(const QString &value);

        QList<PathPixmap> getPixmapList() const;
        void setPixmapList(const QList<PathPixmap> &value);
        void addPixmap(const PathPixmap& pixmap);

        float getProcessTime() const;
        void setProcessTime(float value);

        QString getId() const;
        void setId(QString value);

        QList<QString> getImgFileDeleteList() const;
        void setImgFileDeleteList(const QList<QString> &value);

private:
        QString id;
        QString name;
        QString fullPath;
        QString creationDate;
        const char* timeFormat = "%Y%m%d-%H:%M:%S";
        vector<Ingredient> ingredients;
        int numberOfIngredients;
        QString category;
        vector<QString> keywords;
        int numberOfKeywords;
        QString notes;
        bool favourite;
        QList<PathPixmap> pixmapList;
        QList<QString> imgFileDeleteList;
        int rating;
        float processTime;
};

#endif // RECIPE_H
