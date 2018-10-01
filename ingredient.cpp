#include "ingredient.h"

Ingredient::Ingredient(){
}

Ingredient::Ingredient(QString name, QString wt) : name(name), weightType(wt){
}

Ingredient::Ingredient(QString name, QString wt, float amount) : name(name), weightType(wt), amount(amount){
}

Ingredient::~Ingredient(){}

QStringList Ingredient::weightTypeList = QStringList() << "Gramm" << "Milliliter" << "Stück" << "EL" << "TL";

bool Ingredient::operator==(const Ingredient &rIngredient) const{
    if (name == rIngredient.getName()){
        return true;
    }
    return false;
}

bool Ingredient::operator!=(const Ingredient& rIngredient) const{
    if (name == rIngredient.getName()){
        return false;
    }
    return true;
}

//setter & getter

QString Ingredient::getName() const{
    return name;
}

void Ingredient::setName(const QString &value){
    name = value;
}

QString Ingredient::getWeightType() const{
    return weightType;
}

void Ingredient::setWeightType(const QString &value){
    weightType = value;
}

float Ingredient::getAmount() const{
    return amount;
}

void Ingredient::setAmount(float value){
    amount = value;
}
