#include "ingredient.h"

Ingredient::Ingredient(){}

string Ingredient::getName() const{
    return name;
}

void Ingredient::setName(const string &value){
    name = value;
}

WeightType Ingredient::getWeightType() const{
    return weightType;
}

void Ingredient::setWeightType(const WeightType &value){
    weightType = value;
}

float Ingredient::getAmount() const{
    return amount;
}

void Ingredient::setAmount(float value){
    amount = value;
}
