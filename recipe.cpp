#include "recipe.h"
#include "ingredient.h"

#include <sstream>
#include <iomanip>

Recipe::Recipe() {
}

Recipe::~Recipe(){
    delete timeFormat;
    timeFormat = nullptr;
}

bool Recipe::operator==(const Recipe &rRecipe) const{
    if (name == rRecipe.getName()){
        return true;
    }
    return false;
}

QStringList Recipe::categoryList = QStringList() << "ohne Kategorie" << "Torte"
                                                 << "Kuchen" << "Keks"
                                                 << "Muffin" << "Dessert"
                                                 << "Smoothie";

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

QString Recipe::getCreationDate() const {
    return creationDate;
}

void Recipe::setCreationDate(const QString& value){
    if (value == "now"){
        time_t currentTime = std::time(nullptr);
        std::ostringstream oss;
        oss << std::put_time(localtime(&currentTime), timeFormat);
        creationDate = QString::fromStdString(oss.str());
    } else {
        creationDate = value;
    }
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

void Recipe::setFavourite(const QString& value){
    if (value == "true"){
        favourite = true;
    } else if(value == "false"){
        favourite = false;
    }
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

void Recipe::addIngredient(const Ingredient& ing){
    ingredients.push_back(ing);
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

void Recipe::addKeyword(const QString& keyword){
    keywords.push_back(keyword);
}

QPixmap Recipe::getPixmap() const{
    return pixmap;
}

void Recipe::setPixmap(QPixmap value){
    pixmap = value;
}

int Recipe::getRating() const
{
    return rating;
}

void Recipe::setRating(int value)
{
    rating = value;
}

vector<QString> Recipe::getIngredientStrings() const {
    vector<QString> results;
    for (auto i : ingredients){
        results.push_back(i.getName());
    }
    return results;
}

int Recipe::getNumberOfIngredients() const{
    return ingredients.size();
}

int Recipe::getNumberOfKeywords() const{
    return keywords.size();
}
