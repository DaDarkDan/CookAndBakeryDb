#include <vector>
#include <ctime>

#include "QString"
#include "QStringList"
#include "QPixmap"

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

        QPixmap getPixmap() const;
        void setPixmap(QPixmap value);

        int getRating() const;
        void setRating(int value);

        vector<QString> getIngredientStrings() const;

private:
        QString name;
        QString creationDate;
        const char* timeFormat = "%Y%m%d-%H:%M:%S";
        vector<Ingredient> ingredients;
        QString category;
        vector<QString> keywords;
        QString notes;
        bool favourite;
        QPixmap pixmap;
        int rating;
};

#endif // RECIPE_H
