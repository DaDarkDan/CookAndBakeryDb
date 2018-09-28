#include <string>

#ifndef INGREDIENT_H
#define INGREDIENT_H

using std::string;

enum class WeightType {
    undefiniert,
    g,
    ml,
    Stueck,
    EL,
    TL
};

class Ingredient
{
public:
    Ingredient();

    string getName() const;
    void setName(const string &value);

    WeightType getWeightType() const;
    void setWeightType(const WeightType &value);

    float getAmount() const;
    void setAmount(float value);

private:
    string name;
    WeightType weightType = WeightType::undefiniert;
    float amount;
};

#endif // INGREDIENT_H
