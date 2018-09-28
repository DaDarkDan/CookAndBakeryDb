#include "recipe.h"
#include "ingredient.h"
#include <string>
#include <sstream>

Recipe::Recipe() {
    creationDate = time(nullptr);
}

Recipe::~Recipe(){}

bool Recipe::operator==(const Recipe &rRecipe) const{
    if (name == rRecipe.getName()){
        return true;
    }
    return false;
}

bool Recipe::operator!=(const Recipe &rRecipe) const{
    if (name == rRecipe.getName()){
        return false;
    }
    return true;
}

// setter & getter

QString Recipe::getNotes() const {
    return notes;
}

QString Recipe::getCreationDateAsQString() const
{
    std::stringstream ss;
    ss << creationDate;
    return QString::fromStdString(ss.str());
}

void Recipe::setNotes(const QString &value){
    notes = value;
}

bool Recipe::getFavourite() const{
    return favourite;
}

void Recipe::setFavourite(bool value){
    favourite = value;
}

QString Recipe::getFavouriteAsQString() const{
    if (favourite){
        return "true";
    }
    return "false";
}

QString Recipe::getName() const{
    return name;
}

void Recipe::setName(const QString &value){
    name = value;
}

vector<Ingredient> Recipe::getIngredients() const{
    return ingredients;
}

void Recipe::setIngredients(const vector<Ingredient> &value){
    ingredients = value;
}

QString Recipe::getCategory() const{
    return category;
}

void Recipe::setCategory(const QString &value){
    category = value;
}

vector<QString> Recipe::getKeywords() const{
    return keywords;
}

void Recipe::setKeywords(const vector<QString> &value){
    keywords = value;
}
