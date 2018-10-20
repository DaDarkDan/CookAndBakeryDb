#ifndef PARAMETERBUTTON_H
#define PARAMETERBUTTON_H

#include "QMouseEvent"
#include "recipe.h"
#include "QPushButton"

class ParameterButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ParameterButton(Recipe* recipe, QWidget *parent = nullptr);

signals:
    void clicked(Recipe* recipe);
public slots:
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Recipe* recipe;
};

#endif // PARAMETERBUTTON_H
