#include "ingredient.h"

Ingredient::Ingredient(){
    weightTypes.insert(std::pair<WeightType, QString>(WeightType::undefiniert, "unbestimmt"));
    weightTypes.insert(std::pair<WeightType, QString>(WeightType::g, "g"));
    weightTypes.insert(std::pair<WeightType, QString>(WeightType::ml, "ml"));
    weightTypes.insert(std::pair<WeightType, QString>(WeightType::Stueck, "Stück"));
    weightTypes.insert(std::pair<WeightType, QString>(WeightType::EL, "EL"));
    weightTypes.insert(std::pair<WeightType, QString>(WeightType::TL, "TL"));
}
Ingredient::~Ingredient(){}


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

WeightType Ingredient::getWeightType() const{
    return weightType;
}

void Ingredient::setWeightType(const WeightType &value){
    weightType = value;
}

std::map<WeightType, QString> Ingredient::getWeightTypes() const {
    return weightTypes;
}

float Ingredient::getAmount() const{
    return amount;
}

void Ingredient::setAmount(float value){
    amount = value;
}
