#include "parameterbutton.h"

ParameterButton::ParameterButton(Recipe* recipe, QWidget *parent) : QPushButton(parent), recipe(recipe){}

void ParameterButton::mouseReleaseEvent(QMouseEvent */*event*/){
    emit clicked(recipe);
}
