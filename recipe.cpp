#include "recipe.h"
#include "ingredient.h"

Recipe::Recipe() {
    creationDate = time(nullptr);
}

Recipe::~Recipe(){}

string Recipe::getNotes() const {
    return notes;
}

void Recipe::setNotes(const string &value){
    notes = value;
}

string Recipe::getName() const{
    return name;
}

void Recipe::setName(const string &value){
    name = value;
}

vector<Ingredient> Recipe::getIngredients() const{
    return ingredients;
}

void Recipe::setIngredients(const vector<Ingredient> &value){
    ingredients = value;
}

Category Recipe::getCategory() const{
    return category;
}

void Recipe::setCategory(const Category &value){
    category = value;
}

vector<string> Recipe::getKeywords() const{
    return keywords;
}

void Recipe::setKeywords(const vector<string> &value){
    keywords = value;
}
