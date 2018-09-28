#include <string>
#include <vector>
#include <ctime>

#ifndef RECIPE_H
#define RECIPE_H

using std::string;
using std::vector;

class Ingredient;

enum class Category {
    undefiniert,
    Torte,
    Kuchen,
    Keks,
    Muffin,
    Dessert,
    Smoothie
};

class Recipe {
    public:
        Recipe();

        ~Recipe();

        string getName() const;
        void setName(const string &value);

        vector<Ingredient> getIngredients() const;
        void setIngredients(const vector<Ingredient> &value);

        Category getCategory() const;
        void setCategory(const Category &value);

        vector<string> getKeywords() const;
        void setKeywords(const vector<string> &value);

        string getNotes() const;
        void setNotes(const string &value);
    private:
        string name;
        time_t creationDate;
        vector<Ingredient> ingredients;
        Category category = Category::undefiniert;
        vector<string> keywords;
        string notes;
};

#endif // RECIPE_H
