#include "QString"
#include <map>

#ifndef INGREDIENT_H
#define INGREDIENT_H

enum WeightType {
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
    ~Ingredient();


    QString getName() const;
    void setName(const QString &value);

    WeightType getWeightType() const;
    void setWeightType(const WeightType &value);

    std::map<WeightType, QString> getWeightTypes() const;

    float getAmount() const;
    void setAmount(float value);

    bool operator==(const Ingredient& rIngredient) const;
    bool operator!=(const Ingredient& rIngredient) const;

private:
    QString name;
    std::map<WeightType, QString> weightTypes;
    WeightType weightType;
    float amount;
};

#endif // INGREDIENT_H
