#include <string>
#include <vector>
#include <ctime>
#include "QString"

#ifndef RECIPE_H
#define RECIPE_H

using std::vector;

class Ingredient;

/*
  Kategorien
    undefiniert,
    Torte,
    Kuchen,
    Keks,
    Muffin,
    Dessert,
    Smoothie
*/
class Recipe {
    public:
        Recipe();

        ~Recipe();

        QString getName() const;
        void setName(const QString &value);

        vector<Ingredient> getIngredients() const;
        void setIngredients(const vector<Ingredient> &value);

        QString getCategory() const;
        void setCategory(const QString &value);

        vector<QString> getKeywords() const;
        void setKeywords(const vector<QString> &value);

        QString getNotes() const;
        void setNotes(const QString &value);

        bool getFavourite() const;
        void setFavourite(bool value);
        QString getFavouriteAsQString() const;

        bool operator==(const Recipe& rRecipe) const;
        bool operator!=(const Recipe& rRecipe) const;

        QString getCreationDateAsQString() const;

private:
        QString name;
        time_t creationDate;
        vector<Ingredient> ingredients;
        QString category;
        vector<QString> keywords;
        QString notes;
        bool favourite;
};

#endif // RECIPE_H
