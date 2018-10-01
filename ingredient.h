#include "QString"
#include "QStringList"

#ifndef INGREDIENT_H
#define INGREDIENT_H

class Ingredient
{
public:
    Ingredient();
    Ingredient(QString name, QString wt, float amount);
    Ingredient(QString name, QString wt);
    ~Ingredient();


    QString getName() const;
    void setName(const QString &value);

    QString getWeightType() const;
    void setWeightType(const QString& value);

    float getAmount() const;
    void setAmount(float value);

    bool operator==(const Ingredient& rIngredient) const;
    bool operator!=(const Ingredient& rIngredient) const;

    static QStringList weightTypeList;
private:
    QString name;
    QString weightType;
    float amount;

    void initWeightTypes();
};

#endif // INGREDIENT_H
