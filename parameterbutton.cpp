#include "parameterbutton.h"

ParameterButton::ParameterButton(Recipe* recipe, QWidget *parent) : QPushButton(parent), recipe(recipe){}

void ParameterButton::mousePressEvent(QMouseEvent */*event*/){
    emit clicked(recipe);
}
